#include "odswriter.h"
#include "zipcreator.h"
#include "odstemplate.h"

int odswriter::get_row_style_for_height(int height)
{
	std::map<int, int>::iterator it;
	if ((it = row_heights.find(height)) != row_heights.end()) {
		return it->second;
	} else {
		row_heights[height] = row_style_counter;
		// Add a new row style to the header
		char *szTmp = new char[strlen(ods_content_row_style) + 20];
		sprintf(szTmp, ods_content_row_style, row_style_counter, height / 1000.0);
		header += szTmp;
		delete [] szTmp;
		++row_style_counter;
		return row_style_counter - 1;
	}
}

bool odswriter::is_numeric(const std::string &s)
{
	const char *c = s.c_str();
	bool dotfound = false;
	while (*c) {
		if (*c < '0' || *c > '9') {
			if (*c == '.' && !dotfound) {
				dotfound = true;
			} else {
				return false;
			}
		}
		++c;
	}
	return c != s.c_str(); // empty strings are not numeric
}

std::string odswriter::to_xml(const std::string &src)
{
	std::string res;
	size_t i, last = 0;
	for (i = 0; i < src.length(); ++i) {
		if (src[i] == '&') {
			res += src.substr(last, i - last) + "&amp;";
			last = i + 1;
		} else if (src[i] == '<') {
			res += src.substr(last, i - last) + "&lt;";
			last = i + 1;
		} else if (src[i] == '>') {
			res += src.substr(last, i - last) + "&gt;";
			last = i + 1;
		} else if (src[i] == '"') {
			res += src.substr(last, i - last) + "&quot;";
			last = i + 1;
		}
	}
	if (last) {
		return res + src.substr(last);
	} else {
		return src;
	}
}

bool odswriter::open_document(const std::string &fname)
{
	zc.reset();
	if (!zc.open_zip(fname)) {
		return false;
	}
	zc.add_directory("META-INF/");
	zc.add_directory("Pictures/");
	zc.add_memfile("mimetype", ods_mimetype);
	zc.add_memfile("meta.xml", ods_meta);
	pictures.clear();
	header = ods_content_1;
	mainfile = "";
	picCounter = 1;
	row_heights.clear();
	row_style_counter = 2;
	return true;
}

void odswriter::open_sheet(const std::string &name)
{
	char *szTmp = new char[name.length() + strlen(ods_content_sheet_open) + 1];
	sprintf(szTmp, ods_content_sheet_open, name.c_str());
	mainfile += szTmp;
	delete [] szTmp;
}

void odswriter::open_row(int row_height)
{
	if (row_height != 0) {
		char *szTmp = new char[strlen(ods_content_row_open_style) + 20];
		int style = get_row_style_for_height(row_height);
		sprintf(szTmp, ods_content_row_open_style, style);
		mainfile += szTmp;
		delete [] szTmp;
	} else {
		mainfile += ods_content_row_open;
	}
}

void odswriter::add_text(const std::string &text)
{
	std::string tmp = to_xml(text);
	char *szTmp = new char[tmp.length() + strlen(ods_content_cell_text) + 1];
	sprintf(szTmp, ods_content_cell_text, tmp.c_str());
	mainfile += szTmp;
	delete [] szTmp;
}

void odswriter::add_text_with_link(const std::string &text, const std::string &link)
{
	std::string tmp = to_xml(text);
	char *szTmp = new char[tmp.length() + link.length() + strlen(ods_content_cell_text_with_link) + 1];
	sprintf(szTmp, ods_content_cell_text_with_link, link.c_str(), tmp.c_str());
	mainfile += szTmp;
	delete [] szTmp;
}

void odswriter::add_number(double d)
{
	char *szTmp = new char[80 + strlen(ods_content_cell_number) + 1];
	sprintf(szTmp, ods_content_cell_number, d, d);
	mainfile += szTmp;
	delete [] szTmp;
}

void odswriter::add_text_or_number(const std::string &text)
{
	if (is_numeric(text)) {
		add_number(atoi(text.c_str()));
	} else {
		add_text(text);
	}
}

void odswriter::add_picture(const std::string &filename)
{
	add_text(filename);
}

void odswriter::add_picture_link(const std::string &filename, float cmWidth, float cmHeight)
{
	char *szTmp = new char[filename.length() + strlen(ods_content_cell_image) + 60];
	sprintf(szTmp, ods_content_cell_image, picCounter, cmWidth, cmHeight, filename.c_str());
	++picCounter;
	mainfile += szTmp;
	delete [] szTmp;
	pictures.push_back(filename);
}

void odswriter::store_picture(const std::string &filename, const std::vector<char> &data)
{
	zc.add_memfile("Pictures/" + filename, std::string(&data[0], data.size()));
}

void odswriter::close_row()
{
	mainfile += ods_content_row_close;
}

void odswriter::close_sheet()
{
	mainfile += ods_content_sheet_close;
}

bool odswriter::close_document()
{
	mainfile = header + ods_content_2 + mainfile + ods_content_3;
	zc.add_memfile("content.xml", mainfile);
	std::string manifest = ods_manifest_1;
	std::vector<char> tmp;
	size_t len = strlen(ods_manifest_pic);
	for (std::vector<std::string>::const_iterator it = pictures.begin(); it != pictures.end(); ++it) {
		tmp.resize(len + it->length() + 1);
		sprintf(&tmp[0], ods_manifest_pic, it->c_str());
		manifest += &tmp[0];
	}
	manifest += ods_manifest_2;
	zc.add_memfile("META-INF/manifest.xml", manifest);
	zc.close();
	return true;
}



