#ifndef INVENTAIREPARSER_H_
#define INVENTAIREPARSER_H_

#include <map>

#include "insertinventaire.h"
#include "xmlparser.h"
#include "../common_files/struct.h"
#include "../common_files/utilities.h"

const std::string stop_sheet = "ANNEXES";
class inventaireparser: public xmlparser_with_stack<inventaireparser>
{	
	enum state_t 
	{	
		root,
		sheet,
		row,
		cell
	};
		
	private :
		state_t state;
		info_t info;
		size_t ncols;
		bool is_row_data();
		void dump_row();
		std::vector<info_t> vInfo;
		std::map<std::string,std::vector<info_t> > mapInventaire;		
		bool isInHeader;
		bool isAnnexes;		
	public:	
		inventaireparser();
		virtual void XMLstartElement(const char *name, const char **atts);
		virtual void XMLendElement(const char *name);
		virtual void XMLcharacterData(const char *s, int len);	
		std::map<std::string,std::vector<info_t> > getMapInventaire();
};

#endif	//INVENTAIREPARSER_H_