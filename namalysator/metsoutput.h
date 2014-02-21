#ifndef METSOUTPUT_H_
#define METSOUTPUT_H_


#include <set>
#include <string>
#include "odswriter.h"
#include "structgui.h"

class headcutter
{
	odswriter	ow;
	int			sequence_number;
public:
	bool open_document(const std::string &fname);
	//void cut_headings(bool only_level1, int permille, const std::string &metsfile);
	void cut_headings(std::string currentTiff,std::string currentAlto,Block block,std::string title);
	void close_document();
};

// void cut_headings( bool only_level1, const std::string &filename, const std::string &prefix, int permille, const std::string &metsfile);
// bool ismets(const std::string &fname);

#endif
