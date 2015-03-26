#include "titletocheck.h"
#include <sstream>
#include <string>
#include <iostream>

//! check if the titles has to be check or not
titletocheck::titletocheck(datafactory *df,errorHandler *hError,metsparserContext& CTX,database& db)
{

	datafactory_set<Article> dfArticle= df->get_set<Article>();
	
	for (datafactory_set<Article>::iterator it = dfArticle.begin(); it != dfArticle.end(); ++it)
	{	
		it->check = false;
		for(size_t i=0;i < 	it->vectArticle.size();i++)
		{
			if ( db.isEntityToTitleCorrectionLink(CTX.papertype,it->type,it->vectArticle[i].type)  )
			{
				it->check = true;
				break;
			}
		}
	}
}
