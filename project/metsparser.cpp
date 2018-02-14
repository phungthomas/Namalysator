#include "metsparser.h"
#include <boost/algorithm/string.hpp>
#include "../common_files/xmltostr.h"


metsParser::metsParser(std::string &mets_fname,std::string &mets_path,errorHandler *h,datafactory *df):StateParserCH(ctx,_root){
	ctx.hError = h;	
	ctx.currentMetsFile = mets_fname;	
	ctx.currentMetsPath = mets_path;
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
		CTX.papertype = papertype.value;
	
		CTX.inventory.setActif(true);
//		if ( papertype.value.compare("Monograph")==0 ) CTX.inventory.setActif(true);
//		else CTX.inventory.setActif(false);
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

class StateEmptyCheck : public StateParserScanResolution{
public:
	virtual void endElement (const char* const name){
		boost::algorithm::trim(cData);
		if ( cData.length() == 0 ) {
			CTX.MixContainer[std::string(name)]=cData;
		}
		CTX.mandatoryField.erase(name);
	};
};


void StateParseramdSecState::startElement (const char* const name, const xercesc::Attributes &atts ){
	const char *val = getAttributeValue("ID", atts);
	if (val!=0)
	{
		CTX.amdsec.amdSecId =val;
	}
	if ( CTX.flagMix ){
		CTX.mandatoryField.insert("scannerManufacturer");
		CTX.mandatoryField.insert("scannerModelName");
		CTX.mandatoryField.insert("scannerModelSerialNo");
		CTX.mandatoryField.insert("scanningSoftwareName");
		CTX.mandatoryField.insert("scanningSoftwareVersionNo");
		CTX.mandatoryField.insert("dateTimeCreated");
		CTX.mandatoryField.insert("imageProducer");
		CTX.mandatoryField.insert("captureDevice");
		CTX.mandatoryField.insert("orientation");
		CTX.mandatoryField.insert("sourceIDType");
		CTX.mandatoryField.insert("sourceType");
		CTX.mandatoryField.insert("formatVersion");
		CTX.mandatoryField.insert("objectIdentifierValue");
		CTX.mandatoryField.insert("imageWidth");
		CTX.mandatoryField.insert("imageHeight");
	}
	
};

void StateParseramdSecState::endElement (const char* const name){
	CTX.dfMets->set(CTX.amdsec.amdSecId,CTX.amdsec);

	if ( CTX.flagMix ){
		if ( CTX.mandatoryField.size() != 0 ){
			for ( std::set<std::string>::iterator it = CTX.mandatoryField.begin(); it != CTX.mandatoryField.end(); it ++ ) {
				std::string ret = *it;
				CTX.MixContainerNotDefine[ret]="";
			}
		}
	}

};

StateParserState* StateParserRootamdSecState::getNext(const char* const name){
	static std::map<string,StateParserState*> map;

	static StateParserState* root = new StateParserRootamdSecState();
	StateParserState* ret=root;
	
	static struct _onlyOnes {
		_onlyOnes(std::map<string,StateParserState*>& map,bool flagMix){
			map["sourceData"]=	new StateParserSourceDataResolution();
			map["xOpticalResolution"]=	new StateParserScanResolution();
			if ( flagMix ) {
				map["scannerManufacturer"]=new StateEmptyCheck();
				map["scannerModelName"]=new StateEmptyCheck();
				map["scannerModelSerialNo"]=new StateEmptyCheck();
				map["scanningSoftwareName"]=new StateEmptyCheck();
				map["scanningSoftwareVersionNo"]=new StateEmptyCheck();
				map["dateTimeCreated"]=new StateEmptyCheck();
				map["imageProducer"]=new StateEmptyCheck();
				map["captureDevice"]=new StateEmptyCheck();
				map["orientation"]=new StateEmptyCheck();
				map["sourceIDType"]=new StateEmptyCheck();
				map["sourceType"]=new StateEmptyCheck();
				map["formatVersion"]=new StateEmptyCheck();
				map["objectIdentifierValue"]=new StateEmptyCheck();
				map["imageWidth"]=new StateEmptyCheck();
				map["imageHeight"]=new StateEmptyCheck();
			};
		}
	} onlyOnes (map,CTX.flagMix ); // take care CTX.flagMix: a side effect base on the fact that config.xml is read only ones ( no change on the fly like the map is static ) 

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
			CTX.inventory.setCurrentInventory(val);
		}
	};

	virtual void endElement (const char* const name){
		CTX.dfMets->set(CTX.idItem,CTX.dmdSecStruct);
		CTX.dmdSecStruct.mapAddStringData.clear();
		CTX.inventory.setCurrentInventory("DUMMY");
	};
};

class StateParsermodState : public StateParserMetsRootState{
private :
public:

	virtual void characters (const char* const s, const int len){
		CTX.addStringData += xml2str(s,len);
	}
	virtual void endElement (const char* const name){
		std::string _name (name);
		std::string idkeymap = "MODS:" + _name;
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

	virtual StateParserState* getNext(const char* const name);

};

class StateTitleState : public StateParserMetsRootState{
private :
	std::string value;
public:

	StateTitleState(std::string _value):value(_value){};

	virtual void characters (const char* const s, const int len){
		CTX.addStringData += xml2str(s,len);
	}

	virtual void endElement (const char* const name){
		CTX.addStringData += value;
	};

	
};

class StateDoNothingState : public StateParserMetsRootState{
public:
};

class StateParsermodStateInventory:public StateParsermodState{
protected:
	std::string value;
public:
	StateParsermodStateInventory(std::string _value):value(_value){};

	virtual void endElement (const char* const name){
		CTX.inventory.setCurrentInventoryValue(value,CTX.addStringData);
		StateParsermodState::endElement(name);
	};
};

class StateParsermodStateTitleInfoInventory:public StateParsermodState{

public:
	StateParsermodStateTitleInfoInventory(){};

	StateParserState* getNext(const char* const name){
	static std::map<string,StateParserMetsRootState*> map;
	static StateParserState* root=this;

	StateParserState* ret=root;
	
	static struct _onlyOnes {
		_onlyOnes(std::map<string,StateParserMetsRootState*>& map){
			//static int i = 0;
			//std::cerr << "Only Ones :"<< ++i << std::endl;
			map["title"]= new StateParsermodStateInventory("title");
			map["nonSort"]= new StateTitleState(" ");
			map["partNumber"]= new StateParsermodStateInventory("partNumber");
		}
	} onlyOnes (map);

	if (CTX.inventory.isActif()){
		std::map<string,StateParserMetsRootState*>::iterator it = map.find(name);
		if ( it != map.end()) ret = (*it).second;
	};

	return ret;


};

};

class StateParsermodStateInventory2:public StateParsermodStateInventory{
private:
	std::string value2;

public:
	StateParsermodStateInventory2(std::string value,std::string value2):StateParsermodStateInventory(value){
		this->value2=value2;
	};

	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){
		CTX.addStringData.clear();
		const char *val = getAttributeValue("displayLabel", atts);

		if (val != 0 && strcmp(val, "manufacturer")==0) 
		{		
			this->value = value2;
		}
	};

	StateParserState* getNext(const char* const name){
		static std::map<string,StateParserMetsRootState*> map;
		static StateParserState* root=new StateDoNothingState();;

		StateParserState* ret=root;
		
		static struct _onlyOnes {
			_onlyOnes(std::map<string,StateParserMetsRootState*>& map){
				//static int i = 0;
				//std::cerr << "Only Ones :"<< ++i << std::endl;
				
				map["publisher"]= new StateTitleState("");
			}
		} onlyOnes (map);

		if (CTX.inventory.isActif()){
			std::map<string,StateParserMetsRootState*>::iterator it = map.find(name);
			if ( it != map.end()) ret = (*it).second;
		};

		return ret;


	};

};

class StateParsermodStateInventoryMarc:public StateParsermodState{
private:
	std::string value;
public:
	StateParsermodStateInventoryMarc(std::string _value):value(_value){};

	virtual void endElement (const char* const name){
		CTX.inventory.setCurrentInventoryValue(value,CTX.addStringData);
		CTX.addStringData.clear();
	};
};


StateParserState* StateParsermodState::getNext(const char* const name){
	static std::map<string,StateParsermodState*> map;
	static StateParserState* root=this;

	StateParserState* ret=root;
	
	static struct _onlyOnes {
		_onlyOnes(std::map<string,StateParsermodState*>& map){
			//static int i = 0;
			//std::cerr << "Only Ones :"<< ++i << std::endl;
			map["recordIdentifier"]= new StateParsermodStateInventory("recordIdentifier");
			map["titleInfo"]=		new StateParsermodStateTitleInfoInventory();
			map["identifier"]=	new StateParsermodStateInventory("identifier");
			map["originalInfo"]=	new StateParsermodStateInventory2("publisher","printer");
			map["languageTerm"]=new StateParsermodStateInventory("languageTerm");
			map["dateIssued"]=	new StateParsermodStateInventory("dateIssued");
			map["author"]=	new StateParsermodStateInventory("author");
		}
	} onlyOnes (map);

	if (CTX.inventory.isActif()){
		std::map<string,StateParsermodState*>::iterator it = map.find(name);
		if ( it != map.end()) ret = (*it).second;
	};

	return ret;


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

			if ( std::strspn (val2,"0123456789")!= strlen (val2) ){
				CTX.hError->getError(cat_missingGroupId,"METS","FILESEC","GROUPID not number",CTX.currentMetsFile,getAttributeValue("CHECKSUM", atts));
			}
		}
		else
		{
			CTX.hError->getError(cat_missingGroupId,"METS","FILESEC","GROUPID missing",CTX.currentMetsFile,getAttributeValue("CHECKSUM", atts));
		}
		const char *val3 = getAttributeValue("CHECKSUM", atts);			
		CTX.f.checksum ="";
		if (val3 != 0) 
		{				
			CTX.f.checksum = val3;					
		}
		val3 = getAttributeValue("CHECKSUMTYPE", atts);			
		CTX.f.checksumtype ="";
		if (val3 != 0) 
		{				
			CTX.f.checksumtype = val3;					
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
private : 
public:

	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){
		//cerr << "SateParserstructDiv :: startElement" << name << endl;
		const char *val1 = getAttributeValue("ID", atts);
		const char *val2 = getAttributeValue("TYPE", atts);
		const char *val3 = getAttributeValue("LABEL", atts);
		const char *val4 = getAttributeValue("DMDID", atts);

		if ( CTX.flagDivCount ){

			std::string entity = (val2 ? val2 : "");
			if ( CTX.hError->getDatabase()->isEntityToCount(CTX.papertype,entity) ){
				CTX.divIDCount[entity]++;
			}
		
		}


		if (CTX.currentItem ==0)
		{		
			//CTX.rootItem = new Item;
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
		if (val1 /*&& val2*/) 
		{
			if ( val2) {
				CTX.typeblock.block = val2;
			}
			CTX.typeblock.alto = val1;	
			//CTX.typeblock.type = CTX.currentItem->parent->type;
			CTX.typeblock.type = CTX.currentItem->type;
			CTX.currentItem->vectTypeBlock.push_back(CTX.typeblock);			
		}
	
	};
};

void SateParserstructMap::startElement (const char* const name, const xercesc::Attributes &atts ){
	//cerr << "SateParserstructMap :: startElement" << name << endl;
	CTX.currentItem =0;
    //CTX.rootItem =0;
									
	std::string val = getAttributeValue("TYPE", atts);
	if (val.find("LOGICAL")!=string::npos){	
		LOGICAL = true;
		CTX.rootItem = &CTX.rootItemLOGICAL;
		CTX.currentItem = 0;
	}else{
		LOGICAL = false;
		CTX.rootItem = &CTX.rootItemPHYSICAL;
		CTX.currentItem = 0;
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
		//delete CTX.rootItem;
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
			map["mods"]=	new StateParsermodState(); // could be better if children of dmdsec
			map["controlfield"]=	new StateParsermodStateInventoryMarc("BIBREC_SYS_NUM"); // could be better if children of dmdsec
            // amd -> has his sub state
			map["amdSec"]=	new StateParseramdSecState();


		}
	} onlyOnes (map);

	std::map<string,StateParserState*>::iterator it = map.find(name);
	if ( it != map.end()) ret = (*it).second;

	return ret;
}
