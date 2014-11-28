#ifndef DATAFACTORY_INC_
#define DATAFACTORY_INC_

///////////////////////////////////////////////////////////////
// datafactory_iterator
///////////////////////////////////////////////////////////////


template <typename T>
datafactory_iterator<T> &datafactory_iterator<T>::operator++() {
	if (!is_null) {
		++it;
	}
	return *this;
}

template <typename T>
datafactory_iterator<T> datafactory_iterator<T>::operator++(int) {
	if (!is_null) {
		datafactory_iterator tmp = *this;
		++it;
		return tmp;
	} else {
		return *this;
	}
}

template <typename T>
const T &datafactory_iterator<T>::operator*()
{
	return *(dynamic_cast<T *>(it->second));
}

template <typename T>
T * datafactory_iterator<T>::operator->()
{
	return dynamic_cast<T *>(it->second);
}

template <typename T>
const std::string &datafactory_iterator<T>::key()
{
	if (is_null) {
		assert("Dereferencing invalid iterator" == 0);
	}
	return it->first;
}

template <typename T>
bool datafactory_iterator<T>::operator==(const datafactory_iterator<T> &b) const
{
	return ((is_null && b.is_null) || 
		(!is_null && !b.is_null && it == b.it));
}

template <typename T>
bool datafactory_iterator<T>::operator!=(const datafactory_iterator<T> &b) const
{
	return !operator==(b);
}

///////////////////////////////////////////////////////////////
// datafactory_set
///////////////////////////////////////////////////////////////

template <typename T>
typename datafactory_set<T>::iterator datafactory_set<T>::begin() const
{
	iterator it;
	if (m) {
		it.is_null = false;
		it.it = m->begin();
	}
	return it;
}

template <typename T>
typename datafactory_set<T>::iterator datafactory_set<T>::end() const
{
	iterator it;
	if (m) {
		it.is_null = false;
		it.it = m->end();
	}
	return it;
}

template <typename T>
typename datafactory_set<T>::size_type datafactory_set<T>::size() const
{
	if (m) {
		return m->size();
	} else {
		return 0;
	}
}

template <typename T>
bool datafactory_set<T>::empty() const
{
	if (m) {
		return m->empty();
	} else {
		return true;
	}
}

template <typename T>
std::pair<typename datafactory_set<T>::iterator, bool> datafactory_set<T>::insert(const std::string &ID, const T &src)
{
	if (m) {
		maptype::iterator it = m->find(ID);
		if (it != m->end()) {
			// Already in there, overwrite with new
			delete it->second;
			T *p = new T;
			*p = src;
			it->second = p;
			iterator ita;
			ita.is_null = false;
			ita.it = it;
			return std::make_pair(ita, true);
		} else {
			T *p = new T;
			*p = src;
			std::pair<maptype::iterator, bool> res = m->insert(std::make_pair(ID, p));
			iterator ita;
			ita.is_null = false;
			ita.it = res.first;
			return std::make_pair(ita, false);
		}
	} else {
		return std::make_pair(iterator(), false);
	}
}

template <typename T>
void datafactory_set<T>::erase(typename datafactory_set<T>::iterator pos)
{
	if (!pos.is_null && m) {
		typename datafactory_set<T>::maptype::iterator it = m->find(pos.it);
		if (it != m->end()) {
			delete it->second;
			it->second = 0;
			m->erase(it);
		}
	}
}

template <typename T>
typename datafactory_set<T>::size_type datafactory_set<T>::erase(const std::string &ID)
{
	if (m) {
		typename datafactory_set<T>::maptype::iterator it = m->find(ID);
		if (it != m->end()) {
			delete it->second;
			it->second = 0;
			m->erase(it);
			return 1;
		}		
	}
	return 0;
}

///////////////////////////////////////////////////////////////
// datafactory
///////////////////////////////////////////////////////////////

template <typename T>
T *datafactory::get(const std::string &ID)
{
	rep_type::iterator it = item.find(T::DATAITEM_ID);
	if (it != item.end()) {
		std::map<std::string, dataitem *>::const_iterator ita = it->second.find(ID);
		if (ita != it->second.end()) {
			return dynamic_cast<T *>(ita->second);
		}
	}
	return 0;
}

template <typename T>
T *datafactory::get()
{
	return get<T>("");
}

template <typename T>
bool datafactory::set(const std::string &ID, const T &src)
{
	T *p = new T;
	*p = src;
	item[T::DATAITEM_ID][ID] = p;
	return true;
}

template <typename T>
bool datafactory::set(const T &src)
{
	return set("", src);
}

template <typename T>
datafactory_set<T> datafactory::get_set()
{
	datafactory_set<T> m;
	rep_type::iterator it = item.find(T::DATAITEM_ID);
	if (it != item.end()) {
		m.m = &it->second;
	} else {
		m.m = 0;
	}
	return m;
}

template <typename T>
size_t datafactory::size()
{
	datafactory::rep_type::iterator it = item.find(T::DATAITEM_ID);
	if (it != item.end()) {
		return it->second.size();
	}
	return 0;
}

#endif // DATAFACTORY_INC_