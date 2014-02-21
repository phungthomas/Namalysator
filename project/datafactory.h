#ifndef DATAFACTORY_H_
#define DATAFACTORY_H_

#include <map>
#include <string>
#include <cassert>
#include "dataitem.h"

template <typename T>
class datafactory_set;

template <typename T>
class datafactory_iterator
{
	std::map<std::string, dataitem *>::const_iterator it;
	bool is_null;
public:
	datafactory_iterator() : is_null(true) {}
	datafactory_iterator &operator++();
	datafactory_iterator operator++(int);
	const T &operator*();
	T * operator->();
	const std::string &key();
	bool operator==(const datafactory_iterator<T> &b) const;
	bool operator!=(const datafactory_iterator<T> &b) const;

	template <typename T>
	friend class datafactory_set;
};

template <typename T>
class datafactory_set
{
	typedef std::map<std::string, dataitem *> maptype;
	maptype *m;
public:
	typedef typename datafactory_iterator<T>	iterator;
	typedef typename T							value_type;
	typedef size_t								size_type;

	iterator begin() const;
	iterator end() const;
	size_type size() const;
	bool empty() const;
	std::pair<iterator, bool> insert(const std::string &ID, const T &src);
	void erase(iterator pos);
	size_type erase(const std::string &ID);

	friend class datafactory;
};

//! data structure where we store temporarily elements from the Mets and Alto files in memory.
class datafactory
{
	typedef std::map<size_t, std::map<std::string, dataitem *> > rep_type;
	rep_type item;
public:
	template <typename T>
	T *get(const std::string &ID);

	template <typename T>
	T *get();

	template <typename T>
	bool set(const std::string &ID, const T &src);

	template <typename T>
	bool set(const T &src);

	template <typename T>
	datafactory_set<T> get_set();

	template <typename T>
	size_t size();

	~datafactory();
};

#include "datafactory_templates.cpp"

#endif // DATAFACTORY_H_