#include "altoparser.h"

const char *extract_blocks[] = {
	"TextBlock",
	"Illustration",
	"ComposedBlock"};

altoparser::altoparser(const std::string &alto_fname,const std::string &altoId,errorHandler *h, datafactory *df)
{	
	xml = initializeXmlValidator();
	altoFile = alto_fname;
	alto =altoId;
	currentstate = state_header;
	headerIn = false;
	hError = h;
	dfalto = df;	
	measurement_unit = false;	

	for (size_t i = 0; i < sizeof(extract_blocks) / sizeof(extract_blocks[0]); ++i)
	{
		to_extract.insert(extract_blocks[i]);
	}
}

void altoparser::getElement(const char *name, const char **atts)
{
	Block block;
	currentstate = state_block;	
	const char *val = get_named_attr("ID", atts);
	std::string idBlock = val;		

	const char *val2 = get_named_attr("HPOS", atts);
	if (val2 !=0)
	{
		block.hpos = atoi(val2);
	}
	const char *val3 = get_named_attr("VPOS", atts);
	if (val3 !=0)
	{
		block.vpos = atoi(val3);
	}
	const char *val4 = get_named_attr("HEIGHT", atts);
	if (val4 !=0)
	{
		block.height = atoi(val4);
	}
	const char *val5 = get_named_attr("WIDTH", atts);
	if (val5 !=0)
	{
		block.width  = atoi(val5);
	}
	altoBlock.mapalto[idBlock]= block;		
	currentstate = state_alto;	
}

void altoparser::XMLstartElement(const char *name, const char **atts)
{		
	if (headerIn ==true)
	{
		xml += 	xml2stringBegin(name,atts);
	} 
	if(currentstate == state_header)
	{
		xml += 	xml2stringHeader(name,atts);

		currentstate = state_alto;
		headerIn =true;
	}

	if (strcmp(name, "MeasurementUnit") == 0) 
	{
		measurement_unit = true;
	}
	else if(currentstate == state_alto)
	{	
		if (strcmp(name,"PrintSpace")==0)
		{		
			altoBlock.printSpaceHpos = 0;
			const char *val2 = get_named_attr("HPOS", atts);
			if (val2 !=0)
			{
				altoBlock.printSpaceHpos = atoi(val2);
			}
			altoBlock.printSpaceVpos = 0;
			const char *val3 = get_named_attr("VPOS", atts);
			if (val3 !=0)
			{
				altoBlock.printSpaceVpos = atoi(val3);
			}
			altoBlock.printSpaceHeight = 0;
			const char *val4 = get_named_attr("HEIGHT", atts);
			if (val4 !=0)
			{
				altoBlock.printSpaceHeight = atoi(val4);
			}
			altoBlock.printSpaceWidth = 0;
			const char *val5 = get_named_attr("WIDTH", atts);
			if (val5 !=0)
			{
				altoBlock.printSpaceWidth = atoi(val5);
			}	
		}
		if (to_extract.find(name) != to_extract.end())
		{	
			getElement(name,atts);
		} 	
	}	
	else if (currentstate ==state_block)
	{	
		if (strcmp(name,"String")==0)
		{
			const char *val = get_named_attr("CONTENT", atts);
			if (val!=0)
			{
				std::string my_val= val;
				content += my_val + " ";
			}
		}
	}
}

void altoparser::XMLendElement(const char *name)
{		
	xml += xml2stringEnd(name);
	if (measurement_unit) 
	{
		measurement_unit = false;
	}
	else  if (strcmp(name,"alto") == 0)
	{	
		dfalto->set(alto,altoBlock);
		/* // no more validation
		if (schemaValidation =="1")
		{			
			Error error = schema_validatoralto(xml);	
			if (error.message !="")
			{			
				hError->getMetsError(cat_schema_err,"ALTO","ALTO",error,altoFile);				
			}		

		}	
		*/
	}
}

void altoparser::XMLcharacterData(const char *s, int len)
{	
	if (measurement_unit) 
	{
		altoBlock.measurement =	xml2stringData(s,len);

		if (strncmp(s, "pixel", len) == 0) {
			is_mm10 = false;
		} else if (strncmp(s, "mm10", len) == 0) {
			is_mm10 = true;
		}
	}
}


