#include "exportDataHelper.h"
#include "structgui.h"

#include "metsoutput.h"
#include "metsparser.h"
#include "altoparser.h"



void exportDataHelper::exportData(std::string filenameToCreate){
	
	db.setDataBaseName(BatchDetail::getBatchDetail().database); 

	headcutter *hc = 0;
	hc = new headcutter;
	hc->open_document(filenameToCreate);
	std::string currentAlto="";
	std::string currentTif="";
	std::vector<Title> vTitle = db.getvTitle(BatchDetail::getBatchDetail().idTestSet);


	for (size_t ij = 0;ij < vTitle.size(); ij++)
    {	
		// prepare for a new METS file
		// Clear the list of DIVs with a DMDID
		vectItem.clear();
		const Title &t = vTitle[ij];	
		const MetsFile &mets = vTitle[ij].mets;
		std::string pathMets =  BatchDetail::getBatchDetail().path + mets.path + "/" + mets.fileName;
		Item itemtree;
		Item *treeContents;

		metsParser p(pathMets, &itemtree);
		ParseDocument(pathMets.c_str(),&p);
		treeContents = p.getItem();
		
		std::map<int,LinkedFiles> mapAltoPath;
		std::map<int,LinkedFiles> mapTiffPath;
		mapTiffPath = mets.mapLinked.find("IMGGRP")->second;
		mapAltoPath = mets.mapLinked.find("ALTOGRP")->second;
		
		findArticle(treeContents,mets.docType);		
	    std::map<std::string,altoblock> mapAlto;

		for(std::map<int,LinkedFiles>::iterator it = mapAltoPath.begin(); it != mapAltoPath.end(); it++)
		{
			int dpi = mapTiffPath[it->first].dpi;
			std::string path = BatchDetail::getBatchDetail().path +"/"+ t.mets.path + it->second.fileName;
			altoparser ap(path,it->second, &mapAlto, dpi);	
			if (ParseDocument(path.c_str(),&ap)!=0)
			{
					// print error				
			}
			else
			{
					mapAlto[it->second.fileId] = ap.getAltoBlock();
			}
		}
		createArticle();		
		std::string path;
		Article a = mapArticleWithIdDiv.find(vTitle[ij].article.div)->second;
		bool found = false;	
		for (size_t i =0;i < a.vectArticle.size();i++)
		{
			if ((a.vectArticle[i].type == "HEADING") ||(a.vectArticle[i].type == "CAPTION") )
			{
				for (std::map<int,LinkedFiles>::iterator it = mapAltoPath.begin(); it != mapAltoPath.end(); it++)
				{
					if (it->second.fileId == a.vectArticle[i].alto)
					{
						currentTif = mapTiffPath.find(it->first)->second.fileName;
						currentAlto = it->second.fileId;
						path = BatchDetail::getBatchDetail().path + mets.path + currentTif;
						found = true;
						break;
					}
				}
				altoblock at = mapAlto[a.vectArticle[i].alto];					
				at.mapalto.find(a.vectArticle[i].block);
				if (at.mapalto.find(a.vectArticle[i].block) != at.mapalto.end())
					{
						Block block = at.mapalto[a.vectArticle[i].block];						
						hc->cut_headings(path,currentAlto,block,a.title);					
					}	
			
				i= a.vectArticle.size();
			}		
		}	
	}	
	hc->close_document();
}

void exportDataHelper::findArticle(Item *item,std::string docType){
	for (size_t i=0; i< item->children.size();i++)
	{		
		Item *currentItem = &item->children[i];
		if(db.isEntityToTitleCorrection ( docType, currentItem->type ) )
		{	
			vectItem.push_back(currentItem);
		}
		findArticle(currentItem,docType);
	}

}

void exportDataHelper::createArticle(){	
	mapArticle.clear();
	mapArticleWithIdDiv.clear();
	int count =1;
	for (size_t i=0; i< vectItem.size(); i++)
	{	
		Article article;
		findBlockToArticle(vectItem[i], article.vectArticle);
		article.type = vectItem[i]->type;
		article.id = vectItem[i]->dmdId;
		article.title = vectItem[i]->label;		
		article.div = vectItem[i]->id;		
		mapArticle[vectItem[i]->counter] = article;
		mapArticleWithIdDiv[article.div] =article;
		count++;
	}
}


// Adds all blocks that are children of the given item to the array "output"
void exportDataHelper::findBlockToArticle(Item *item, std::vector<typeBlock> &output)
{
	for (size_t i=0; i< item->children.size();i++)
	{		
		Item *currentItem = &item->children[i];	
		if(currentItem->vectTypeBlock.size() >0)
		{
			for(size_t j=0;j< currentItem->vectTypeBlock.size();j++)
			{
				output.push_back(currentItem->vectTypeBlock[j]);
			}
		}
		findBlockToArticle(currentItem, output);			
	}
}