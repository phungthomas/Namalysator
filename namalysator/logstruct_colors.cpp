#include "logstruct_colors.h"
#include <stdio.h>

logstruct_colors::logstruct_colors()
{
	m_schema = "";
	m_default_color = QColor(200, 200, 0);
}

logstruct_colors::logstruct_colors(const std::string &schema)
{
	set_defaults(schema);
	m_default_color = QColor(200, 200, 0);
}

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

void logstruct_colors::set_schema(const std::string &schema)
{
	m_colors.clear();
	set_defaults(schema);
}

void logstruct_colors::set_defaults(const std::string &schema)
{
	m_schema = schema;
	if (m_schema == "Newspaper") {
		m_colors.insert(std::make_pair("ARTICLE", QColor(100,255,100)));
		m_colors.insert(std::make_pair("SECTION", QColor(255,100,100)));
		m_colors.insert(std::make_pair("ADVERTISEMENT", QColor(255,255,100)));
		m_colors.insert(std::make_pair("SUPPLEMENT", QColor(0,0,255)));
		m_colors.insert(std::make_pair("ADVERTISEMENT_SECTION", QColor(255,100,100)));
		m_colors.insert(std::make_pair("WEATHER", QColor(100,255,100)));
		m_colors.insert(std::make_pair("DEATH_NOTICE", QColor(0,255,0)));
		m_colors.insert(std::make_pair("DEATH_NOTICE_SECTION", QColor(255,100,100)));
		m_colors.insert(std::make_pair("SHIPPING", QColor(0,255,0)));
		m_colors.insert(std::make_pair("ILLUSTRATION", QColor(100,100,255)));
		// Extended version with TITLE_SECTION as well
		m_colors.insert(std::make_pair("HEADLINE", QColor(200,100,0)));
		m_colors.insert(std::make_pair("MOTTO", QColor(200,0,100)));
		m_colors.insert(std::make_pair("PUBLISHING_STMT", QColor(0,200,100)));
		m_colors.insert(std::make_pair("TEXTBLOCK", QColor(220,255,220)));
		// More extended with tables too
		m_colors.insert(std::make_pair("TABLE", QColor(150,0,0)));
	} else if (m_schema == "Serial") {
		m_colors.insert(std::make_pair("CHAPTER", QColor(0,255,0)));
		m_colors.insert(std::make_pair("ILLUSTRATION", QColor(255, 100, 200)));
		m_colors.insert(std::make_pair("MAP", QColor(0,150,0)));
		m_colors.insert(std::make_pair("TABLE", QColor(150,0,0)));
		m_colors.insert(std::make_pair("CHART_DIAGRAM", QColor(170,200,255)));
		m_colors.insert(std::make_pair("SUPPLEMENT", QColor(255,0,0)));
		m_colors.insert(std::make_pair("ADVERTISEMENT", QColor(255,255,100)));
		m_colors.insert(std::make_pair("APPENDIX", QColor(255,255,0)));
		m_colors.insert(std::make_pair("ABSTRACT", QColor(120,120,0)));
		m_colors.insert(std::make_pair("FOOTNOTE", QColor(200,255,200)));
		m_colors.insert(std::make_pair("MAP_GROUP", QColor(0,0,170)));
		m_colors.insert(std::make_pair("TABLE_GROUP", QColor(0,0,170)));
		m_colors.insert(std::make_pair("CHART_DIAGRAM_GROUP", QColor(0,0,170)));
		m_colors.insert(std::make_pair("ILLUSTRATION_GROUP", QColor(0,0,170)));
		m_colors.insert(std::make_pair("LIST", QColor(200,100,255)));
		m_colors.insert(std::make_pair("BIBLIOGRAPHY", QColor(0,150,70)));
		m_colors.insert(std::make_pair("TABLE_OF_CONTENTS", QColor(170,170,100)));
		m_colors.insert(std::make_pair("INDEX", QColor(0,170,170)));
		m_colors.insert(std::make_pair("AUTHOR", QColor(233,150,122)));
		m_colors.insert(std::make_pair("TITLE_OF_WORK", QColor(200,0,150)));
		m_colors.insert(std::make_pair("CREATOR_OF_WORK", QColor(200,0,0)));
		m_colors.insert(std::make_pair("PUBLISHING_STMT", QColor(0,200,100)));
		m_colors.insert(std::make_pair("STATEMENT", QColor(150,150,150)));
		m_colors.insert(std::make_pair("PAGE_NUMBER", QColor(255,122,122)));
	} else if (m_schema == "Monograph") {
		m_colors.insert(std::make_pair("FRONT", QColor(255,0,0)));
		m_colors.insert(std::make_pair("MAIN", QColor(0,0,255)));
		m_colors.insert(std::make_pair("BACK", QColor(127,127,127)));
		m_colors.insert(std::make_pair("CHAPTER", QColor(0,255,0)));
		m_colors.insert(std::make_pair("ILLUSTRATION", QColor(255, 100, 200)));
	}
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