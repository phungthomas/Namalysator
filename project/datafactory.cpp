#include "datafactory.h"
#include <iostream>

datafactory::~datafactory()
{
	for (rep_type::iterator it = item.begin(); it != item.end(); ++it) {
		for (std::map<std::string, dataitem *>::iterator ita = it->second.begin(); ita != it->second.end(); ++ita) {
			delete ita->second;
			ita->second = 0;			
		}
	}
}