#ifndef configparserinventaire_H_
#define configparserinventaire_H_

#include "../common_files/xmlparser.h"
#include "../common_files/struct.h"
#include "../common_files/xmltostr.h"
#include "insertinventaire.h"
//! Parse the config xml and extract parameters of the Testset  
class configparserinventaire: public xmlparser_with_stack<configparserinventaire>
{	
	enum state 
	{	
		state_root,
		state_title,
		state_cote,
		state_input,
		state_database,
	};
		
	private :
		state currentState;
		Inventaire *inv;

	public:	
		configparserinventaire(Inventaire *inventaire);
		virtual void XMLstartElement(const char *name, const char **atts);
		virtual void XMLendElement(const char *name);
		virtual void XMLcharacterData(const char *s, int len);	
};

#endif	//configparserinventaire_H_