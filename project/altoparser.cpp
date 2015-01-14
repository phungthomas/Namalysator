#include "altoparser.h"
#include <string>
#include <iostream>
#include "../common_files/xmltostr.h"
using namespace std;



altoparser::altoparser(const std::string &alto_fname,const std::string &altoId,errorHandler *h, datafactory *df):StateParserCH(ctx,root){	
	ctx.altoFile = alto_fname;
	ctx.alto = altoId;
	ctx.hError = h; // no more usefull like parsing will validate !
	ctx.dfalto = df;	
}

#define CTX (*((altoparserContext*)ctx))

class StateParserAltoState : public StateParserAltoRootState{
	virtual void endElement (const char* const name){
			CTX.dfalto->set(CTX.alto,CTX.altoBlock);

	};
};

class StateParserBlockSpace : public StateParserAltoRootState{
	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){
		Block block;
		
		const char *val = getAttributeValue("ID", atts);
		std::string idBlock = val;		

		const char *val2 = getAttributeValue("HPOS", atts);
		if (val2 !=0)
		{
			block.hpos = atoi(val2);
		}
		const char *val3 = getAttributeValue("VPOS", atts);
		if (val3 !=0)
		{
			block.vpos = atoi(val3);
		}
		const char *val4 = getAttributeValue("HEIGHT", atts);
		if (val4 !=0)
		{
			block.height = atoi(val4);
		}
		const char *val5 = getAttributeValue("WIDTH", atts);
		if (val5 !=0)
		{
			block.width  = atoi(val5);
		}
		CTX.altoBlock.mapalto[idBlock]= block;
	};
};

class StateParserPrintSpace : public StateParserAltoRootState{
	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){	
			CTX.altoBlock.printSpaceHpos = 0;
			const char *val2 = getAttributeValue ("HPOS", atts);
			if (val2 !=0)
			{
				CTX.altoBlock.printSpaceHpos = atoi(val2);
			}
			CTX.altoBlock.printSpaceVpos = 0;
			const char *val3 = getAttributeValue ("VPOS", atts);
			if (val3 !=0)
			{
				CTX.altoBlock.printSpaceVpos = atoi(val3);
			}
			CTX.altoBlock.printSpaceHeight = 0;
			const char *val4 = getAttributeValue ("HEIGHT", atts);
			if (val4 !=0)
			{
				CTX.altoBlock.printSpaceHeight = atoi(val4);
			}
			CTX.altoBlock.printSpaceWidth = 0;
			const char *val5 = getAttributeValue ("WIDTH", atts);
			if (val5 !=0)
			{
				CTX.altoBlock.printSpaceWidth = atoi(val5);
			}	
	}
};

class StateParserMeasurementUnit : public StateParserAltoRootState{
public:
	virtual void characters (const char* const s, const int len){
		CTX.altoBlock.measurement =	xml2stringData(s,len);

		if (strncmp(s, "pixel", len) == 0) {
			CTX.is_mm10 = false;
		} else if (strncmp(s, "mm10", len) == 0) {
			CTX.is_mm10 = true;
		}
		
	
	};
};



StateParserState* StateParserAltoRootState::getNext(const char* const name){
	
	static std::map<string,StateParserState*> map;
	static StateParserState* root=this;

	StateParserState* ret=root;
	
	static struct _onlyOnes {
		_onlyOnes(std::map<string,StateParserState*>& map){
			map["alto"]=	new StateParserAltoState();
			map["MeasurementUnit"]=	new StateParserMeasurementUnit();
			map["PrintSpace"]=	new StateParserPrintSpace();
			map["TextBlock"]=
			map["Illustration"]=
			map["ComposedBlock"]=	new StateParserBlockSpace();
		}
	} onlyOnes (map);

	std::map<string,StateParserState*>::iterator it = map.find(name);
	if ( it != map.end()) ret = (*it).second;

	return ret;
}


