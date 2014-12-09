#include "titletocheck.h"
#include <sstream>
#include <string>
#include <iostream>

//! check if the titles has to be check or not
titletocheck::titletocheck(datafactory *df,errorHandler *hError,std::string &fname)
{
	dfverifiers = df;
	datafactory_set<Article> dfArticle= dfverifiers->get_set<Article>();
	
	for (datafactory_set<Article>::iterator it = dfArticle.begin(); it != dfArticle.end(); ++it)
	{	
		it->check = false;
		for(size_t i=0;i < 	it->vectArticle.size();i++)
		{
			if (it->vectArticle[i].type == "HEADING" || it->vectArticle[i].type == "CAPTION")
			{
				it->check = true;
				break;
			}
		}
	}
}
