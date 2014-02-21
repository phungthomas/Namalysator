#ifndef ODSWRITER_H_
#define ODSWRITER_H_

#include <string>
#include "zipcreator.h"
#include <vector>
#include <map>

class odswriter
{
	std::vector<std::string>	pictures;
	std::string					mainfile;
	std::string					header;
	int							picCounter;
	int							row_style_counter;
	std::map<int, int>			row_heights; // Maps row height to style number
	zip_creator zc;
	int get_row_style_for_height(int height);
	std::string to_xml(const std::string &src);
	bool is_numeric(const std::string &s);
public:
	bool open_document(const std::string &fname);
	void open_sheet(const std::string &name);
	// Opens a new row, the height given is in 1000th of a cm
	void open_row(int row_height = 0);
	void add_text(const std::string &text);
	void add_text_or_number(const std::string &text);
	void add_number(double d);
	void add_picture(const std::string &filename);
	void add_picture_link(const std::string &filename, float cmWidth, float cmHeight);
	void store_picture(const std::string &filename, const std::vector<char> &data);
	void close_row();
	void close_sheet();
	bool close_document();
};


#endif // ODSWRITER_H_
