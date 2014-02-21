#ifndef ZIPCREATOR_H_
#define ZIPCREATOR_H_

#include <string>
#include <vector>
#include "minizip/zip.h"

class zip_creator
{
    zipFile zf;
	std::vector<unsigned char> buf;
public:
	void reset();
	bool open_zip(const std::string &name);
	bool add_file(const std::string &file_inzip, const std::string &filename);
	bool add_directory(const std::string &name);
	bool add_memfile(const std::string &file_inzip, const std::string &data);
	bool close();
};

#endif // ZIPCREATOR_H_
