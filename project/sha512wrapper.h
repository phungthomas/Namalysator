// wrapper around sha 512 function 
//

#ifndef SHA512_WRAPPER_H
#define SHA512_WRAPPER_H

#include <string>


class sha512wrapper{
public:

	std::string getHashFromFile(std::string filename);

};


#endif