#ifndef CONFIGPARSER_H_
#define CONFIGPARSER_H_

#include "../common_files/xmlparser.h"
#include "../common_files/struct.h"

//! Parse the config xml and extract parameters of the Testset  
class configparser: public xmlparser_with_stack<configparser>
{	
	enum state 
	{	
		state_root,
		state_database,
		state_batchName,
		state_schemaValidation,
		state_dateFolderIssue,
		state_input,
		state_checkFile,
		state_checkSum,
		state_divs,		
		state_unlinkedIdentifier,
		state_identifierMix,	
		state_altoblockPerPage,
		state_blockStructure,
		state_coveragePercentAlto,
		state_multipleBlockUse,
		state_invalidSupplement,
		state_noIssueDefined,
		state_checkTitle,
		state_sampling,
		state_oddsPages,
		state_dates,
		state_issueNumber
	};
		
	private :
		state currentState;
		Parameters *param;

	public:	
		configparser(Parameters *temp);
		virtual void XMLstartElement(const char *name, const char **atts);
		virtual void XMLendElement(const char *name);
		virtual void XMLcharacterData(const char *s, int len);	
};

#endif	//CONFIGPARSER_H_