#include "altoparser.h"
#include "gui_utilities.h"

const char *extract_blocks[] = {
	"TextBlock",
	"Illustration",
	"ComposedBlock"};
		
altoparser::altoparser(std::string &alto_fname,LinkedFiles lf,int d)//(const std::string &alto_fname,const std::string &altoId,handleerror *h, datafactory *df)
{	
	convert_to_pixels = true;
	altoFile = alto_fname;
	alto =lf.fileId;
	currentstate = state_alto;	
	measurement_unit = false;
	dpi= d;
	
	for (size_t i = 0; i < sizeof(extract_blocks) / sizeof(extract_blocks[0]); ++i)
	{
		to_extract.insert(extract_blocks[i]);
	}
}

void altoparser::getElement(const char *name, const char **atts)
{
	Block block;
	//currentstate = state_block;	
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

	if (convert_to_pixels && is_mm10)
	{
		block.convert_to_pixel(dpi);
	}

	altoBlock.mapalto[idBlock]= block;		
	currentstate = state_alto;	
	
}
void altoparser::XMLstartElement(const char *name, const char **atts)
{	
	if (strcmp(name, "MeasurementUnit") == 0) 
	{
		measurement_unit = true;
	}
	else if(currentstate == state_alto)
	{	
		if (strcmp(name,"PrintSpace")==0)
		{		
			blockPrintspace.hpos = 0;
			const char *val2 = get_named_attr("HPOS", atts);
			if (val2 !=0)
			{
				blockPrintspace.hpos = atoi(val2);
			//	altoBlock.printSpaceHpos = atoi(val2);
			}
			blockPrintspace.vpos = 0;
			const char *val3 = get_named_attr("VPOS", atts);
			if (val3 !=0)
			{
				//altoBlock.printSpaceVpos = atoi(val3);
				blockPrintspace.vpos = atoi(val3);
			}
			blockPrintspace.height = 0;
			const char *val4 = get_named_attr("HEIGHT", atts);
			if (val4 !=0)
			{
				//altoBlock.printSpaceHeight = atoi(val4);
				blockPrintspace.height = atoi(val4);
			}
			blockPrintspace.width = 0;
			const char *val5 = get_named_attr("WIDTH", atts);
			if (val5 !=0)
			{
				//altoBlock.printSpaceWidth = atoi(val5);
				blockPrintspace.width = atoi(val5);
			}	
			
			if (convert_to_pixels && is_mm10)
			{
				blockPrintspace.convert_to_pixel(dpi);
			}	
			
			altoBlock.printSpaceHeight = blockPrintspace.height;
			altoBlock.printSpaceHpos = blockPrintspace.hpos;
			altoBlock.printSpaceVpos = blockPrintspace.vpos;
			altoBlock.printSpaceWidth = blockPrintspace.width;
			
		}
		if (to_extract.find(name) != to_extract.end())
		{	
			getElement(name,atts);
		} 	
	}	
	/*
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
	}*/
}

void altoparser::XMLendElement(const char *name)
{	
	if (measurement_unit) 
	{
		measurement_unit = false;
	}	
}

void altoparser::XMLcharacterData(const char *s, int len)
{	
	if (measurement_unit) 
	{
		altoBlock.measurement =	std::string(s,len);

		if (strncmp(s, "pixel", len) == 0) {
			is_mm10 = false;
		} else if (strncmp(s, "mm10", len) == 0) {
			is_mm10 = true;
		}
	}
}

altoblock altoparser::getAltoBlock()
{
	return altoBlock;
} 