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

	val = get_named_attr("HPOS", atts);
	if (val !=0)
	{
		block.hpos = atoi(val);
	}
	val = get_named_attr("VPOS", atts);
	if (val !=0)
	{
			block.vpos = atoi(val);
	}
	val = get_named_attr("HEIGHT", atts);
	if (val !=0)
	{
		block.height = atoi(val);
	}
	val = get_named_attr("WIDTH", atts);
	if (val !=0)
	{
		block.width  = atoi(val);
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
			const char *val = get_named_attr("HPOS", atts);
			if (val !=0)
			{
				blockPrintspace.hpos = atoi(val);
			}
			blockPrintspace.vpos = 0;
			val = get_named_attr("VPOS", atts);
			if (val !=0)
			{
				blockPrintspace.vpos = atoi(val);
			}
			blockPrintspace.height = 0;
			val = get_named_attr("HEIGHT", atts);
			if (val !=0)
			{
				blockPrintspace.height = atoi(val);
			}
			blockPrintspace.width = 0;
			val = get_named_attr("WIDTH", atts);
			if (val !=0)
			{
				blockPrintspace.width = atoi(val);
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