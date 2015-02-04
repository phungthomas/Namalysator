#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "stateparser.h"
#include <iostream>
#include <fstream>

class transformContext : public StateParserContext{
public :
	transformContext():firstTag(true){};
	std::string filename;
	std::ofstream fileStream;

	void openFile ( std::string _filename );
	void closeFile ();

	bool firstTag;
};

class StateTransformRootState:public StateParserState{
public:
	StateTransformRootState(){};
	virtual ~StateTransformRootState(){};

	virtual StateParserState* getNext(const char* const name);
};

class transformParser : public StateParserCH
{	
private:
	StateTransformRootState _root;
	transformContext ctx;
public:
	transformParser();
	inline transformContext& getContext(){return ctx;};
};




#endif