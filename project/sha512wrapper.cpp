#include "sha512.h"
#include "sha512wrapper.h"
#include <iostream>


std::string sha512wrapper::getHashFromFile(std::string filename){
	FILE *file;
  	sha2 sha;

	//std::cerr << "sizeof 4 " << sizeof (sha_word32) << " sizeof 1 " << sizeof ( sha_byte ) << " sizeof 8 " << sizeof(sha_word64)
	//	<< std::endl;
  
	int len;
  	unsigned char buffer[1024];

	sha.Init(sha2::enuSHA512);

  	if ((file = fopen (filename.c_str(), "rb")) == NULL)
	{
		return "-1";
	}
 	
	//read the filecontent
	while ( (len = fread (buffer, 1, 64, file)) )
   	{
		sha.Update(buffer,len);
	}

	/*
	generate hash, close the file and return the
	hash as std::string
	*/
	sha.End();
	
	//std::cerr << "SHA512:afterfinal:" <<  filename << std::endl;
 	fclose (file);
	return sha.HexHash();
}
