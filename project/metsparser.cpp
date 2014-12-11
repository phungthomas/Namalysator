#include "metsparser.h"


metsParser::metsParser(std::string &mets_fname,errorHandler *h,datafactory *df):StateParserCH(ctx,_root){
	ctx.hError = h;	
	ctx.metsfile = mets_fname;
	ctx.currentstate = metsparserContext::root;
	ctx.current = 0;	
	ctx.dfMets = df;
}

void metsParser::XMLstartElement(const char *name, const char **atts)
{		
	//cout << "metsParser::XMLstartElement" << name << endl;
	if (ctx.currentstate == metsparserContext::root)
	{
		if (strcmp(name, "mets") == 0) {
			const char *s = get_named_attr("TYPE", atts);
			StringItem papertype;
			papertype.value = (s ? s : "");
			ctx.dfMets->set<StringItem>("METS_PAPERTYPE", papertype);
		} else if (strcmp(name,"dmdSec") == 0)
		{			
			ctx.current = new dmdsecparser(ctx.dfMets, expat_parser,ctx.metsfile,ctx.hError);	
			ctx.currentstate = metsparserContext::delegated;	
			ctx.current->initialize(name,atts);			
		}
		else if (strcmp(name,"amdSec") == 0)
		{							
			ctx.current = new amdsecparser(ctx.dfMets, expat_parser,ctx.metsfile,ctx.hError);	
			ctx.currentstate = metsparserContext::delegated;	
			ctx.current->initialize(name,atts);			
		} 
		else if (strcmp(name,"fileSec") == 0)
		{			
			ctx.current = new filegroupparser(ctx.dfMets, expat_parser,ctx.metsfile,ctx.hError);						
			ctx.currentstate = metsparserContext::delegated;
			ctx.current->initialize(name,atts);						
		} 
		else if (strcmp(name,"structMap") == 0)
		{								
			std::string val = get_named_attr("TYPE", atts);
			if (val.find("LOGICAL")!=string::npos)
			{	
				ctx.current = new structmapparser(ctx.dfMets, expat_parser,ctx.metsfile,ctx.hError);						
				ctx.currentstate = metsparserContext::delegated;					
				ctx.current->initialize(name,atts);	
			}
		}
	}	
	else
	{			
		ctx.current->startElement(name,atts);			
	}
}

void metsParser::XMLendElement(const char *name)
{
	//cout << "metsParser::XMLendElement" << name << endl;
	if (ctx.currentstate == metsparserContext::root)
	{
	}
	else
	{
		if (ctx.current->endElement(name)==false)
		{				
			delete ctx.current;
			ctx.current =0;
			ctx.currentstate =metsparserContext::root;			
		}
	}
}

void metsParser::XMLcharacterData(const char *s, int len)
{
	//cout << "metsParser::XMLcharacterData" << s << endl;
	if (ctx.currentstate == metsparserContext::delegated)
	{			
		ctx.current->characterData(s,len);
	}
}


#define CTX (*((altoparserContext*)ctx))


StateParserState* StateParserMetsRootState::getNext(const char* const name){
	
	static std::map<string,StateParserState*> map;
	static StateParserState* root=this;

	StateParserState* ret=root;
	
	static struct _onlyOnes {
		_onlyOnes(std::map<string,StateParserState*>& map){
			map["alto"]=	new StateParserMetsRootState();
			map["MeasurementUnit"]=	new StateParserMetsRootState();
			map["PrintSpace"]=	new StateParserMetsRootState();
			map["TextBlock"]=
			map["Illustration"]=
			map["ComposedBlock"]=	new StateParserMetsRootState();
		}
	} onlyOnes (map);

	std::map<string,StateParserState*>::iterator it = map.find(name);
	if ( it != map.end()) ret = (*it).second;

	return ret;
}
