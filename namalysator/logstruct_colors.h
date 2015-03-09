#ifndef LOGSTRUCT_COLORS_H_
#define LOGSTRUCT_COLORS_H_

#include <map>
#include <string>
#include <QColor>

class logstruct_colors
{
	// The data is held in a map which maps the element in the logical structure (e.g. ARTICLE) to a color
	typedef std::map<std::string, QColor>					m_rep_type;
	typedef std::map<std::string, QColor>::const_iterator	m_const_it;
	std::map<std::string, QColor>	m_colors;
	// The schema for the logical structure (e.g. "Newspaper" or "Serial")
	std::string						m_schema;
	QColor							m_default_color;
public:
	// returns the color used by a div type (e.g. ARTICLE)
	const QColor &get_color(const std::string &divtype) const;
	// returns true if this type of element exists in the internal map
	bool is_color_set(const std::string &divtype) const;
	logstruct_colors();
	//logstruct_colors(const std::string &schema);
	//void set_schema(const std::string &schema);
	void set_colorTable(const std::map<std::string, QColor> & colorTable);
	void dump_html(const std::string &fname);

private:
	//void set_defaults(const std::string &schema);
};

#endif // LOGSTRUCT_COLORS_H_