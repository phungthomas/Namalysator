#ifndef XMLPARSER_H_
#define XMLPARSER_H_
#include <vector>
#include <string>
#include <expat.h>

// #define VERBOSE_ERROR

class xmlparser
{
protected:
	XML_Parser expat_parser;
public:
	xmlparser() : expat_parser(0) {}
	virtual void startElement(const char *name, const char **atts) = 0;
	virtual void endElement(const char *name) = 0;
	virtual void characterData(const char *s, int len) = 0;
	virtual ~xmlparser() {}

	friend int ParseDocument(const char *fname, xmlparser *parser);
};

template <typename Base>
class xmlparser_with_stack : 
	public xmlparser
{
protected:
	std::vector<std::string> tag_stack;
public:
	virtual void startElement(const char *name, const char **atts);
	virtual void endElement(const char *name);
	virtual void characterData(const char *s, int len);
	
	// helper functions
	const char *get_named_attr(const char *name, const char **atts);
};


extern char empty_string[1];
int ParseDocument(const char *fname, xmlparser *parser);

/*************************************************/
/* xmlparser_with_stack */

template <typename Base>
void xmlparser_with_stack<Base>::startElement(const char *name, const char **atts)
{
	tag_stack.push_back(name);
	Base *p = static_cast<Base *>(this);
	p->XMLstartElement(name, atts);
}

template <typename Base>
void xmlparser_with_stack<Base>::endElement(const char *name)
{
#ifdef VERBOSE_ERROR
	if (!tag_stack.empty() && tag_stack.back() == name) {
		tag_stack.pop_back();
	} else {
		if (tag_stack.empty()) {
			fprintf(stderr, "closing %s, but none are open", name);
		} else {
			fprintf(stderr, "closing %s but should be closing %s\n", name, tag_stack.back().c_str());
		}
	}
#else
	tag_stack.pop_back();
#endif
	Base *p = static_cast<Base *>(this);
	p->XMLendElement(name);
}

template <typename Base>
void xmlparser_with_stack<Base>::characterData(const char *s, int len)
{
	Base *p = static_cast<Base *>(this);
	p->XMLcharacterData(s, len);
}

template <typename Base>
const char *xmlparser_with_stack<Base>::get_named_attr(const char *name, const char **atts)
{
	const char *val = 0;
	if (!atts) {
		return 0;
	}
	while (*atts) {
		if (strcmp(*atts, name) == 0) {
			++atts;
			if (*atts) {
				val = *atts;
			}
			return val;
		} else {
			++atts;
			++atts;
		}
	}
	return val;
}

#endif // XMLPARSER_H_
