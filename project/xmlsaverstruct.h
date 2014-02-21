#ifndef XMLSAVERSTRUCT_H_
#define XMLSAVERSTRUCT_H_

		std::string  saveStartElement(const char *name, const char **atts);
		std::string  saveEndElement(const char *name,std::string el) ;
		std::string  saveCharacterData(const char *s, int len);		

#endif //XMLSAVER_H_