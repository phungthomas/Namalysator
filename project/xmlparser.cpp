#include "../common_files/xmlparser.h"
#include <expat.h>

void XMLCALL StartElement(void *userData, const XML_Char *name, const XML_Char **atts)
{
	xmlparser *p = (xmlparser *) userData;	
	p->startElement(name, atts);
	
}

void XMLCALL EndElement(void *userData, const XML_Char *name)
{
	xmlparser *p = (xmlparser *) userData;
	p->endElement(name);
}

void XMLCALL CharacterData(void *userData, const XML_Char *s, int len)
{
	xmlparser *p = (xmlparser *) userData;
	p->characterData(s, len);
}


int ParseDocument(const char *fname, xmlparser *parser)
{
	const int BUFF_SIZE = 1024;
	if (!parser) {
		return 2;
	}

	FILE *fp ;
	fopen_s(&fp,fname, "r");
	if (!fp) {
		printf("could not open file %s\n", fname);
		return 2;
	}
	XML_Parser p;
	p = XML_ParserCreate(0);
	if (!p) {
		fprintf(stderr, "Unable to create Expat parser\n");
		fclose(fp);
		return 1;
	}
	XML_SetElementHandler(p, &StartElement, &EndElement);
	XML_SetCharacterDataHandler(p, &CharacterData);
	XML_SetUserData(p, parser);
	parser->expat_parser = p;
	for (;;) {
		int bytes_read;
		void *buff = XML_GetBuffer(p, BUFF_SIZE);
		if (buff == NULL) {
			fprintf(stderr, "Could not allocate memory\n");
			fclose(fp);
			return 1;
		}

		bytes_read = fread(buff, 1, BUFF_SIZE, fp);
		int ferr;
		if (bytes_read != BUFF_SIZE && (ferr = ferror(fp)) != 0) {
			fprintf(stderr, "Could not read XML file (error: %d)\n", ferr);
			fclose(fp);
			return 1;
		}

		if (!XML_ParseBuffer(p, bytes_read, bytes_read == 0)) {
			fprintf(stderr, "Error parsing XML\n");
			return 1;
		}

		if (bytes_read == 0)
		break;
	}
	XML_ParserFree(p);
	fclose(fp);
	return 0;	
}
