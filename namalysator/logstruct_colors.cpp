#include "logstruct_colors.h"
#include <stdio.h>

logstruct_colors::logstruct_colors()
{
	m_schema = "";
	m_default_color = QColor(200, 200, 0);
}

/*
logstruct_colors::logstruct_colors()
{
	//set_defaults(schema);
	m_default_color = QColor(200, 200, 0);
}
*/


const QColor &logstruct_colors::get_color(const std::string &divtype) const
{
	m_const_it it;
	if ((it = m_colors.find(divtype)) != m_colors.end()) {
		return it->second;
	} else {
		return m_default_color;
	}
}

bool logstruct_colors::is_color_set(const std::string &divtype) const
{
	return  (m_colors.find(divtype) != m_colors.end());
}

/*
void logstruct_colors::set_schema(const std::string &schema)
{
	m_colors.clear();
}
*/


void logstruct_colors::set_colorTable(const std::map<std::string, QColor> & colorTable)
{
	m_colors.clear();
	m_colors = colorTable;
}


void logstruct_colors::dump_html(const std::string &fname)
{
	FILE *fp = fopen(fname.c_str(), "w");
	fprintf(fp, "<html><head><title>Colors for %s</title></head>\n<body>", m_schema.c_str());
	fprintf(fp, "<table border=\"1\" cellpadding=\"3\" cellspacing=\"0\">\n");
	fprintf(fp, "<tr><td><b>Element</b></td><td><b>Color</b></td></tr>\n");
	for (m_const_it it = m_colors.begin(); it != m_colors.end(); it++) {
		fprintf(fp, "<tr><td>%s</td><td bgcolor=\"%s\">&nbsp;</td></tr>\n", it->first.c_str(), qPrintable(it->second.name()));
	}
	fprintf(fp, "</table></body></html>");
	fclose(fp);
}