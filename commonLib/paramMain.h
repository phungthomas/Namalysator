#ifndef _PARAMMAIN_H
#define _PARAMMAIN_H

// Manage the parameter in line

class contextParam{

private:
	int option_index;
	char optopt;
	char* optarg;
	int getopt(int argc, char** argv,char* option);

public:
	contextParam();
	char* configFile;
	int analyse(int argc, char** argv);
};

#endif