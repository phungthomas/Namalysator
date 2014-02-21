#include "configparserinventaire.h"
#include "../common_files/xmltostr.h"
#include "../common_files/utilities.h"
#include <iostream>

configparserinventaire::configparserinventaire(Inventaire *i)
{	
	currentState = state_root;
	inv = i;
}

void configparserinventaire::XMLstartElement(const char *name, const char **atts)
{	
	if (strcmp(name,"title")== 0)	
	{
		currentState = state_title;
	}
	else if (strcmp(name,"cote")== 0)			
	{
		currentState = state_cote;
	}	
	else if (strcmp(name,"input") == 0)		
	{
		currentState = state_input;
	}
	else if (strcmp(name,"database") == 0)		
	{
		currentState = state_database;
	}		
}


void configparserinventaire::XMLendElement(const char *name)
{		
	currentState = state_root;
}


void configparserinventaire::XMLcharacterData(const char *s, int len)
{	
	if (currentState == state_title)
	{
	std::string message = std::string(s,len);
		for ( size_t i = 0; i < message.length(); i++)
	{
		if (message[i] =='\'')
		{
			message.replace(i,1,"''");
			i+=2; 
		}
	}  
		inv->name = message;	
	}
	else if (currentState == state_cote)
	{
		inv->code = std::string(s,len);		
	}
	else if (currentState == state_input)
	{
		inv->input = std::string(s,len);		
	}
	else if (currentState == state_database)
	{
		inv->database = std::string(s,len);		
	}
}



