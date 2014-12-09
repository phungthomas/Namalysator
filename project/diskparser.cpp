#include "diskparser.h"

#include <iostream>

DiskParser::DiskParser(errorHandler *h)
{
	hError = h;
}

bool DiskParser::isMets(const std::string &fName)
{
	// Extension has to be .xml
	if (fName.length() < 4) {
		return false;
	}
	if (fName.substr(fName.length() - 4) != ".xml") {
		return false;
	}	
	FILE *fp ;
	fopen_s(&fp,fName.c_str(), "r");
	char buf[100];

	int nread = fread(buf, 1, 100, fp);
	fclose(fp);
	// The file should begin with <?xml and the second line should begin with <mets
	if (nread < 100) {
		return false;
	}
	// If the file begins with the UTF-8 Byte Order Mark, it's OK
	const char utf8bom[] = {0xEF, 0xBB, 0xBF};
	int i = 0;
	if (strncmp(buf, utf8bom, 3) == 0) {
		i = 3;
	}
	if (strncmp(buf + i, "<?xml", 5) != 0) {
		return false;
	}
	while (i < 100 && buf[i] != '\n') {
		++i;
	}
	++i;
	if (strncmp(buf + i, "<mets", 5) != 0) {
		return false;
	}
	return true;
}

void DiskParser::parseDirectory( fs::path full_path)
{
	fs::directory_iterator end_iter;
	for ( fs::directory_iterator dir_itr( full_path ); dir_itr != end_iter;++dir_itr )
	{			
		try
		{
			if ( fs::is_directory(dir_itr->status() ) ) 
			{		
				 parseDirectory(dir_itr->path());
			}	
			else if ( fs::is_regular_file( dir_itr->status() ) )   
			{
				if (isMets(dir_itr->path().file_string()))
				{			
					std::pair<std::string, std::string> p;
					p.first = dir_itr->path().filename();
					p.second = full_path.file_string();
					vectMets.push_back(p);
				}			
			}		
		}
		catch (const std::exception)
		{	
			hError->getError(cat_metsFile,"METS","METS", "Not a METS file" ,dir_itr->path().filename(),"");			
		}	
	}
}

std::vector<std::pair<std::string, std::string>> DiskParser::parseDisk(std::string &path)
{
	fs::path full_path(path);
	parseDirectory(full_path);
	return vectMets;
}

	