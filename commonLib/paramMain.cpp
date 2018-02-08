#include "paramMain.h"

#include<iostream>
#include<cstdio>
#include<ctype.h>
#include<cstdlib>


contextParam::contextParam(){
	option_index = 1;
	configFile="config.xml";
};


// TODO: link with gnu solution for getopt
//
int contextParam::getopt(int argc, char** argv,char* option){

  if (option_index >= argc) return -1;

  char* tmp = argv[option_index];
  
  char ret;

  if ( tmp[0] == '-' ){ // START OPTION
  
	  ret = optopt = tmp[1];

	  if ( optopt == 0 ) {
		  ret='?';
		  goto end;
	  }

	  bool found = false;
	  for ( char* tmpOption =  option; *tmpOption !=0 ; tmpOption++){
		  if (*tmpOption == optopt ) {// Found
			  found = true;
			  tmpOption++;
			  if ( *tmpOption == ':' ){

				  if (tmp[2] == 0 ){
					  option_index ++;
					  if (option_index >= argc){
						 ret='?';
						 goto end;
					  }
					  optarg = argv[option_index];
				  }else{
					  
					  optarg = tmp+2;
				  }
			  
			  }
		  }

	  }

	  if (!found){
		  ret='?';
		  goto end;
	  }


  }
end:
  option_index++;
  return ret;

}

int contextParam::analyse(int argc, char** argv){

  int c;


  if (argc == 0){
	  configFile = "config.xml";
	  return 0;
  }

  while ((c = getopt (argc, argv, "c:")) != -1)
    switch (c)
      {
      case 'c':
		  configFile = strdup(optarg);
        break;
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
		fprintf (stderr, "usage: %s -c config.xml\n", argv[0]);
        return -1;
      default:
		fprintf (stderr, "usage: %s -c config.xml\n", argv[0]);
        return -1;
      }
	return 0;
}
