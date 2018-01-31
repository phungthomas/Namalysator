#include "dataaggregator.h"
#include "datafactory.h"
#include <iostream>
#include <sstream>
#include "../common_files/utilities.h"

	
dataaggregator::dataaggregator(datafactory *df,std::string fname, database& _db,std::string _typeDocument):db(_db),typeDocument(_typeDocument){
	dfTemp = df;
	currentItem =0;
	fileName = fname;
	vectTypeBlock.clear();
	transform();	
}

void dataaggregator::findArticle(Item *item)
{
	for (size_t i=0; i< item->children.size();i++)
	{		
		currentItem = &item->children[i];

		if( db.isEntityToTitleCorrection(this->typeDocument,currentItem->type) )
		{	
			if ( currentItem ->label.size() > 0 ) vectItem.push_back(currentItem); // Interest only if there is a label
		}
		findArticle(currentItem);				
	}
}

void dataaggregator::findBlockToArticle(Item *item)
{
	for (size_t i=0; i< item->children.size();i++)
	{		
		currentItem = &item->children[i];	

			for(size_t j=0;j< currentItem->vectTypeBlock.size();j++)
			{
				vectTypeBlock.push_back(currentItem->vectTypeBlock[j]);
			}
		
		findBlockToArticle(currentItem);			
	}
}

//extract all articles from an issue
void dataaggregator::createArticleFactory()
{	
	Item *item = 0;
	item = dfTemp->get<Item>("Item");	
	findArticle(item);	
	
	for (size_t i=0; i< vectItem.size(); i++)
	{	
		findBlockToArticle(vectItem[i]);
		Article article;
		article.type = vectItem[i]->type;
		article.id = vectItem[i]->dmdId;
		article.title = vectItem[i]->label;		
		article.vectArticle = vectTypeBlock;
		article.div = vectItem[i]->id;	
		article.parentType = vectItem[i]->parent->type;
		article.parentDmdId = vectItem[i]->parent->dmdId;		
		article.check =1; // will be set by titlecheck				
		vectTypeBlock.clear();
		dfTemp->set(article.id,article);			
	}	
}
void dataaggregator::findDiv(Item *item)
{
	for (size_t i=0; i< item->children.size();i++)
	{		
		currentItem = &item->children[i];	
		divType.vectDivType.push_back(std::make_pair(currentItem->id,currentItem->type));
		findDiv(currentItem);			
	}
}

//extract all divs from an issue
void dataaggregator::createFactoryDivType()
{	
	Item *item = 0;
	item = dfTemp->get<Item>("Item");	
	findDiv(item);	
	dfTemp->set("Div",divType);
}

void dataaggregator::transform()
{
	createArticleFactory();
	//createFactoryDivType();	
	createIssue();	
}


void dataaggregator::createIssue()
{
	std::string ausgabe;	
	std::vector<std::string> vAusgabe;
	vAusgabe.push_back("Morgenausgabe");
	vAusgabe.push_back("Erstes Blatt");
	vAusgabe.push_back("Morgenblatt");
	vAusgabe.push_back("Abendausgabe");
	vAusgabe.push_back("Zweites Blatt");
	vAusgabe.push_back("Abendblatt");
	Mets mets;
	mets.fileName = fileName;
	File_Group *fg  = dfTemp->get<File_Group>("ALTOGRP");
	mets.pages = fg->vect.size();
	mets.papertype = dfTemp->get<StringItem>("METS_PAPERTYPE")->value;
	datafactory_set<dmdsec> dfissue = dfTemp->get_set<dmdsec>();
	for (datafactory_set<dmdsec>::iterator it = dfissue.begin(); it != dfissue.end(); ++it)
	{
		if (it.key().find("MODSMD_PRINT")!=string::npos)
		{
			for (std::map<std::string,std::string>::iterator it2 = it->mapAddStringData.begin();it2!= it->mapAddStringData.end(); it2++)
			{
				std::string state = it2->first;
				if (state =="MODS:title")
				{
					mets.title = it2->second;									
				}
				else if (state =="MODS:partNumber")
				{
					mets.issueNumber = it2->second;
 					mets.vectIssueNumber = getIssueNumber(it2->second);
					for ( size_t i =0; i< vAusgabe.size();i++)
					{
						if (mets.issueNumber.find(vAusgabe[i]) != std::string::npos)
						{
							mets.ausgabe = vAusgabe[i];
							break;
						}
					}		
				}
				else if (state =="MODS:dateIssued")
				{	
					mets.date = it2->second;									
				}				
			}
		}
		else if(it.key().find("MODSMD_SUPPLEMENT")!=string::npos)
		{
			for (std::map<std::string,std::string>::iterator it2 = it->mapAddStringData.begin();it2!= it->mapAddStringData.end(); it2++)
			{	
				std::string state = it2->first;
				if (state == "MODS:title")
				{				
					mets.supplements.push_back(it2->second);
				}		
			}
		}
	}
	dfTemp->set("METS",mets);			
}