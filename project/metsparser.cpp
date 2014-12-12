#include "metsparser.h"
#include <boost/algorithm/string.hpp>

metsParser::metsParser(std::string &mets_fname,errorHandler *h,datafactory *df):StateParserCH(ctx,_root){
	ctx.hError = h;	
	ctx.metsfile = mets_fname;
	ctx.currentstate = metsparserContext::root;
	ctx.current = 0;	
	ctx.dfMets = df;
}


#define CTX (*((metsparserContext*)ctx))


class StateParserMetsState : public StateParserMetsRootState{
public:
	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){
		const char *s = getAttributeValue("TYPE", atts);
		StringItem papertype;
		papertype.value = (s ? s : "");
		CTX.dfMets->set<StringItem>("METS_PAPERTYPE", papertype);
		//cerr << "StateParserMetsState :: startElement" << name << "papertype:" << papertype.value << endl;
	};
};

class StateParserRootamdSecState : public StateParserMetsRootState{
public:

	virtual StateParserState* getNext(const char* const name);
};

class StateParseramdSecState : public StateParserRootamdSecState{
	virtual void startElement (const char* const name, const xercesc::Attributes &atts );
	virtual void endElement (const char* const name);
};

class StateParserScanResolution : public StateParserRootamdSecState{
protected:
	std::string cData;
public:
	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){
		//cerr << "StateParserScanResolution:" << name << "   AMID:" << CTX.amdsec.amdSecId << endl;
		cData.clear();
	};

	virtual void characters (const char* const s, const int len){
		cData += xml2str(s,len);
	};

	virtual void endElement (const char* const name){
		boost::algorithm::trim(cData);
		CTX.amdsec.dpi = atoi(cData.c_str());
	};

};

class StateParserSourceDataResolution : public StateParserScanResolution{
public:
	virtual void endElement (const char* const name){
		boost::algorithm::trim(cData);
		CTX.amdsec.sourceData = cData;
	};
};


void StateParseramdSecState::startElement (const char* const name, const xercesc::Attributes &atts ){
	const char *val = getAttributeValue("ID", atts);
	if (val!=0)
	{
		CTX.amdsec.amdSecId =val;
	}
	
};

void StateParseramdSecState::endElement (const char* const name){
	CTX.dfMets->set(CTX.amdsec.amdSecId,CTX.amdsec);
};

StateParserState* StateParserRootamdSecState::getNext(const char* const name){
	static std::map<string,StateParserState*> map;

	static StateParserState* root = new StateParserRootamdSecState();
	StateParserState* ret=root;
	
	static struct _onlyOnes {
		_onlyOnes(std::map<string,StateParserState*>& map){
			map["SourceData"]=	new StateParserSourceDataResolution();
			map["XphysScanResolution"]=	new StateParserScanResolution();
		}
	} onlyOnes (map);

	std::map<string,StateParserState*>::iterator it = map.find(name);
	if ( it != map.end()) ret = (*it).second;
	return ret;
};




class StateParserdmdSecState : public StateParserMetsRootState{
public:
	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){
		CTX.addStringData.clear();
		const char *val = getAttributeValue("ID", atts);
		if (val != 0) 
		{		
			CTX.idItem = val;						
		}
	};

	virtual void endElement (const char* const name){
		CTX.dfMets->set(CTX.idItem,CTX.dmdSecStruct);
	};
};

class StateParsermodState : public StateParserMetsRootState{
public:
	virtual void characters (const char* const s, const int len){
		CTX.addStringData += xml2str(s,len);
	}
	virtual void endElement (const char* const name){
		std::string idkeymap = "MODS:" + std::string(name);
		// trim whitespace, tabs, newlines from character Data
		boost::algorithm::trim(CTX.addStringData);

		if( CTX.dmdSecStruct.mapAddStringData.find(idkeymap) == CTX.dmdSecStruct.mapAddStringData.end())
		{
			boost::algorithm::trim(CTX.addStringData);
			CTX.dmdSecStruct.mapAddStringData[idkeymap] = CTX.addStringData;
			CTX.addStringData.clear();
		}
		else
		{			
			CTX.dmdSecStruct.mapAddStringData[idkeymap].append(" " +CTX.addStringData);				
			CTX.addStringData.clear();
		}	
	};

	virtual StateParserState* getNext(const char* const name){
		return this;
	};
};

class StateParserRootfileSec : public StateParserMetsRootState{
public:
	virtual StateParserState* getNext(const char* const name);
};


class StateParserFlocat : public StateParserRootfileSec{
public :
	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){
		const char	*val5 = getAttributeValue("xlink:href", atts);
		CTX.f.ref ="";
		if (val5 != 0) 
		{
			std::string my_id = val5;
			//remove file://./
			my_id = my_id.substr(8,my_id.size());
			CTX.f.ref = my_id;				
			CTX.file_group.vect.push_back(CTX.f);						
		}
	};
};

class StateParserfile : public StateParserRootfileSec{
public :
	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){
		const char *val = getAttributeValue("ID", atts);
		CTX.f.id ="";
		if (val != 0) 
		{				
			CTX.f.id = val;					
		}			
		const char *val2 = getAttributeValue("GROUPID", atts);		  
		CTX.f.groupId ="";
		if (val2 != 0) 
		{				
			CTX.f.groupId = val2;		
		}
		else
		{
			CTX.hError->getError(cat_missingGroupId,"METS","FILESEC","GROUPID missing",CTX.metsfile,getAttributeValue("CHECKSUM", atts));
		}
		const char *val3 = getAttributeValue("CHECKSUM", atts);			
		CTX.f.checksum ="";
		if (val3 != 0) 
		{				
			CTX.f.checksum = val3;					
		}
		const char *val4 = getAttributeValue("SIZE", atts);			
		CTX.f.size =0;
		if (val4 != 0) 
		{				
			CTX.f.size = atoi(val4);					
		}
		const char *val5 = getAttributeValue("ADMID", atts);	
		CTX.f.admid ="";
		if (val5 != 0) 
		{				
			CTX.f.admid = val5;					
		}			
		const char *val6 = getAttributeValue("SEQ", atts);	
		CTX.f.seq =0;
		if (val6 != 0) 
		{				
			CTX.f.seq = atoi(val6);					
		}

	};
};

class StateParserfileGrp : public StateParserRootfileSec{
public :
	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){	
		const char *val = getAttributeValue("ID", atts);	
		CTX.idGroup = "";
		if (val != 0) 
		{
			CTX.idGroup = val;						
		}	
	};
	virtual void endElement (const char* const name){
		CTX.dfMets->set(CTX.idGroup,CTX.file_group);
		CTX.file_group.vect.clear(); 
	};
};

class StateParserfileSec : public StateParserRootfileSec{
};


StateParserState* StateParserRootfileSec::getNext(const char *const name){
	static std::map<string,StateParserState*> map;
	static StateParserState* root=this;

	StateParserState* ret=root;
	
	static struct _onlyOnes {
		_onlyOnes(std::map<string,StateParserState*>& map){
			map["fileGrp"]=	new StateParserfileGrp(); 
			map["FLocat"]=	new StateParserFlocat();
			map["file"]=	new StateParserfile();
		}
	} onlyOnes (map);

	std::map<string,StateParserState*>::iterator it = map.find(name);
	if ( it != map.end()) ret = (*it).second;

	return ret;
}

class SateParserstructMapRoot : public StateParserMetsRootState{
public:
	virtual StateParserState* getNext(const char* const name);
};

class SateParserstructMap : public SateParserstructMapRoot{
private:
	bool LOGICAL;
public:

	virtual void startElement (const char* const name, const xercesc::Attributes &atts );
	virtual void endElement (const char* const name);
};

class SateParserstructMapDiv : public SateParserstructMapRoot{
public:

	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){
		//cerr << "SateParserstructDiv :: startElement" << name << endl;
		const char *val1 = getAttributeValue("ID", atts);
		const char *val2 = getAttributeValue("TYPE", atts);
		const char *val3 = getAttributeValue("LABEL", atts);
		const char *val4 = getAttributeValue("DMDID", atts);
	
		if (CTX.currentItem ==0)
		{		
			CTX.rootItem = new Item;
			CTX.rootItem->id = (val1 ? val1 : "");
			CTX.rootItem->label = (val3 ? val3 : "");
			CTX.rootItem->type = (val2 ? val2 : "");
			CTX.rootItem->dmdId = (val4 ? val4 : "");			
			CTX.currentItem = CTX.rootItem;
		}
		else
		{	
			Item c;				
			c.id = (val1 ? val1 : "");
			c.label = (val3 ? val3 : "");
			c.type = (val2 ? val2 : "");
			c.dmdId = (val4 ? val4 : "");
			c.parent = CTX.currentItem; 
			CTX.currentItem->children[CTX.currentItem->children.size()] = c;
			CTX.currentItem = &CTX.currentItem->children[CTX.currentItem->children.size()-1];			
		};
	};	
	
	virtual void endElement (const char* const name){
		CTX.currentItem = CTX.currentItem->parent;	
	};
};

class SateParserstructMapArea : public SateParserstructMapRoot{
public:
	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){
		//cerr << "SateParserstructMapArea :: startElement" << name << endl;
		const char *val1 = getAttributeValue("FILEID", atts);
		const char *val2 = getAttributeValue("BEGIN", atts);
		if (val1 && val2) 
		{
			CTX.typeblock.block = val2;
			CTX.typeblock.alto = val1;	
			CTX.typeblock.type = CTX.currentItem->parent->type;
			CTX.currentItem->vectTypeBlock.push_back(CTX.typeblock);			
		}
	
	};
};

void SateParserstructMap::startElement (const char* const name, const xercesc::Attributes &atts ){
	//cerr << "SateParserstructMap :: startElement" << name << endl;
	CTX.currentItem =0;
    CTX.rootItem =0;
									
	std::string val = getAttributeValue("TYPE", atts);
	if (val.find("LOGICAL")!=string::npos){	
		LOGICAL = true;
	}else{
		LOGICAL = false;
	}
		
};
	
void SateParserstructMap::endElement (const char* const name){
	if ( LOGICAL ) {
		Item t;
		t.id = CTX.rootItem->id;
		t.children = CTX.rootItem->children;
		t.dmdId =CTX.rootItem->dmdId;
		t.label =CTX.rootItem->label;
		t.parent =CTX.rootItem->parent;
		t.type =CTX.rootItem->type;
		t.vectTypeBlock =CTX.rootItem->vectTypeBlock;
		CTX.dfMets->set("Item",t);
	};
};

StateParserState* SateParserstructMapRoot::getNext(const char* const name){

	static std::map<string,StateParserState*> map;
	static StateParserState* root=new SateParserstructMapRoot() ;

	StateParserState* ret=root;
	
	static struct _onlyOnes {
		_onlyOnes(std::map<string,StateParserState*>& map){
			map["structMap"]=	new SateParserstructMap();
			map["div"]=	new SateParserstructMapDiv();
			map["area"]= new SateParserstructMapArea();
		}
	} onlyOnes (map);

	std::map<string,StateParserState*>::iterator it = map.find(name);
	if ( it != map.end()) ret = (*it).second;

	return ret;
}



StateParserState* StateParserMetsRootState::getNext(const char* const name){
	
	static std::map<string,StateParserState*> map;
	static StateParserState* root=new StateParserMetsRootState();

	StateParserState* ret=root;
	
	static struct _onlyOnes {
		_onlyOnes(std::map<string,StateParserState*>& map){
			map["mets"]=	new StateParserMetsState();
			// structmap 
			map["structMap"]=	new SateParserstructMap(); // sub state machine
			// file -> has his sub state
			map["fileSec"]=	new StateParserfileSec();
			// dmdSec
			map["dmdSec"]=	new StateParserdmdSecState();
			map["mods"]=	new StateParsermodState();
            // amd -> has his sub state
			map["amdSec"]=	new StateParseramdSecState();


		}
	} onlyOnes (map);

	std::map<string,StateParserState*>::iterator it = map.find(name);
	if ( it != map.end()) ret = (*it).second;

	return ret;
}
