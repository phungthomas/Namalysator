#include "odstemplate.h"

const char ods_mimetype[] = "application/vnd.oasis.opendocument.spreadsheet";

const char ods_meta[] =
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
	"<office:document-meta xmlns:office=\"urn:oasis:names:tc:opendocument:xmlns:office:1.0\" "
	"xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" "
	"xmlns:meta=\"urn:oasis:names:tc:opendocument:xmlns:meta:1.0\" "
	"xmlns:ooo=\"http://openoffice.org/2004/office\" office:version=\"1.1\">"
	"<office:meta><meta:generator>OpenOffice.org/2.4$Win32 OpenOffice.org_project/680m12$Build-9286</meta:generator>"
	"</office:meta>"
	"</office:document-meta>";

const char ods_manifest_1[] =
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
	"<manifest:manifest xmlns:manifest=\"urn:oasis:names:tc:opendocument:xmlns:manifest:1.0\">\n"
	"<manifest:file-entry manifest:media-type=\"application/vnd.oasis.opendocument.spreadsheet\" manifest:full-path=\"/\"/>\n"
	"<manifest:file-entry manifest:media-type=\"text/xml\" manifest:full-path=\"content.xml\"/>\n"
	"<manifest:file-entry manifest:media-type=\"text/xml\" manifest:full-path=\"meta.xml\"/>\n"
	"<manifest:file-entry manifest:media-type=\"\" manifest:full-path=\"Pictures/\"/>\n";

// Need to insert the filename of the JPG file (without a path)
const char ods_manifest_pic[] =
	"<manifest:file-entry manifest:media-type=\"image/jpeg\" manifest:full-path=\"Pictures/%s\"/>\n";

const char ods_manifest_2[] =
	"</manifest:manifest>";

const char ods_content_1[] =
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
	"<office:document-content xmlns:office=\"urn:oasis:names:tc:opendocument:xmlns:office:1.0\" "
	"xmlns:style=\"urn:oasis:names:tc:opendocument:xmlns:style:1.0\" "
	"xmlns:text=\"urn:oasis:names:tc:opendocument:xmlns:text:1.0\" "
	"xmlns:table=\"urn:oasis:names:tc:opendocument:xmlns:table:1.0\" "
	"xmlns:draw=\"urn:oasis:names:tc:opendocument:xmlns:drawing:1.0\" "
	"xmlns:fo=\"urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0\" "
	"xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" "
	"xmlns:meta=\"urn:oasis:names:tc:opendocument:xmlns:meta:1.0\" "
	"xmlns:number=\"urn:oasis:names:tc:opendocument:xmlns:datastyle:1.0\" "
	"xmlns:presentation=\"urn:oasis:names:tc:opendocument:xmlns:presentation:1.0\" "
	"xmlns:svg=\"urn:oasis:names:tc:opendocument:xmlns:svg-compatible:1.0\" "
	"xmlns:chart=\"urn:oasis:names:tc:opendocument:xmlns:chart:1.0\" "
	"xmlns:dr3d=\"urn:oasis:names:tc:opendocument:xmlns:dr3d:1.0\" "
	"xmlns:math=\"http://www.w3.org/1998/Math/MathML\" "
	"xmlns:form=\"urn:oasis:names:tc:opendocument:xmlns:form:1.0\" "
	"xmlns:script=\"urn:oasis:names:tc:opendocument:xmlns:script:1.0\" "
	"xmlns:ooo=\"http://openoffice.org/2004/office\" xmlns:ooow=\"http://openoffice.org/2004/writer\" "
	"xmlns:oooc=\"http://openoffice.org/2004/calc\" xmlns:dom=\"http://www.w3.org/2001/xml-events\" "
	"xmlns:xforms=\"http://www.w3.org/2002/xforms\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" "
	"xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" office:version=\"1.1\">"
	"<office:scripts/>"
	"<office:font-face-decls>"
	"<style:font-face style:name=\"Arial\" svg:font-family=\"Arial\" style:font-family-generic=\"swiss\" style:font-pitch=\"variable\"/>"
	"<style:font-face style:name=\"Arial Unicode MS\" svg:font-family=\"&apos;Arial Unicode MS&apos;\" "
	"style:font-family-generic=\"system\" style:font-pitch=\"variable\"/>"
	"<style:font-face style:name=\"Tahoma\" svg:font-family=\"Tahoma\" style:font-family-generic=\"system\" style:font-pitch=\"variable\"/>"
	"</office:font-face-decls>"
	"<office:automatic-styles>"
	"<style:style style:name=\"co1\" style:family=\"table-column\">"
	"<style:table-column-properties fo:break-before=\"auto\" style:column-width=\"9.999cm\"/>"
	"</style:style>"
	"<style:style style:name=\"co2\" style:family=\"table-column\">"
	"<style:table-column-properties fo:break-before=\"auto\" style:column-width=\"2.267cm\"/>"
	"</style:style>"
	"<style:style style:name=\"ro1\" style:family=\"table-row\">"
	"<style:table-row-properties style:row-height=\"0.453cm\" fo:break-before=\"auto\" style:use-optimal-row-height=\"false\"/>"
	"</style:style>";

// Need to insert (i_styleNumber, f_Height) with f_Height in cm
const char ods_content_row_style[] = 
	"<style:style style:name=\"ro%d\" style:family=\"table-row\">"
	"<style:table-row-properties style:row-height=\"%1.3fcm\" fo:break-before=\"auto\" style:use-optimal-row-height=\"false\"/>"
	"</style:style>";

const char ods_content_2[] =
	"<style:style style:name=\"ta1\" style:family=\"table\" style:master-page-name=\"Default\">"
	"<style:table-properties table:display=\"true\" style:writing-mode=\"lr-tb\"/>"
	"</style:style>"
	"<style:style style:name=\"ce1\" style:family=\"table-cell\" style:parent-style-name=\"Default\">"
	"<style:table-cell-properties style:vertical-align=\"top\"/>"
	"</style:style>"
	"<style:style style:name=\"gr1\" style:family=\"graphic\">"
	"<style:graphic-properties draw:stroke=\"none\" draw:fill=\"none\" "
	"draw:textarea-horizontal-align=\"center\" draw:textarea-vertical-align=\"middle\" "
	"draw:color-mode=\"standard\" draw:luminance=\"0%\" draw:contrast=\"0%\" draw:gamma=\"100%\" "
	"draw:red=\"0%\" draw:green=\"0%\" draw:blue=\"0%\" fo:clip=\"rect(0cm 0cm 0cm 0cm)\" draw:image-opacity=\"100%\" style:mirror=\"none\" style:protect=\"position size\" />"
	"</style:style>"
	"<style:style style:name=\"P1\" style:family=\"paragraph\">"
	"<style:paragraph-properties fo:text-align=\"center\"/>"
	"</style:style>"
	"</office:automatic-styles>"
	"<office:body>";

// Need to insert the name of the sheet
const char ods_content_sheet_open[] =
	"<office:spreadsheet>"
	"<table:table table:name=\"%s\" table:style-name=\"ta1\" table:print=\"false\">"
	"<table:table-column table:style-name=\"co2\" table:number-columns-repeated=\"10\" table:default-cell-style-name=\"Default\"/>";

const char ods_content_row_open[] =
	"<table:table-row table:style-name=\"ro1\">";

// Need to insert row style (integer)
const char ods_content_row_open_style[] =
	"<table:table-row table:style-name=\"ro%d\">";

// Need to insert the text to be placed inside (with xml escapes for ", < and >)
const char ods_content_cell_text[] =
	"<table:table-cell office:value-type=\"string\"><text:p>%s</text:p></table:table-cell>";

// Need to insert first the link and then the text (with xml escapes for ", < and >)
const char ods_content_cell_text_with_link[] =
	"<table:table-cell office:value-type=\"string\">"
		"<text:p><text:a xlink:href=\"%s\" xlink:type=\"simple\">%s</text:a></text:p>"
	"</table:table-cell>";

// Need to insert (f_value, f_value) i.e. the value twice
const char ods_content_cell_number[] =
	"<table:table-cell office:value-type=\"float\" office:value=\"%f\">"
	"<text:p>%f</text:p>"
	"</table:table-cell>";

// Need to insert (i_counter, f_width, f_height, s_picfile)
const char ods_content_cell_image[] =
	"<table:table-cell>"
	"<draw:frame draw:z-index=\"0\" draw:name=\"Graphics %d\" draw:style-name=\"gr1\" "
	"draw:text-style-name=\"P1\" svg:width=\"%1.3fcm\" svg:height=\"%1.3fcm\" svg:x=\"0cm\" svg:y=\"0cm\">"
	"<draw:image xlink:href=\"Pictures/%s\" xlink:type=\"simple\" xlink:show=\"embed\" xlink:actuate=\"onLoad\">"
	"<text:p/>"
	"</draw:image>"
	"</draw:frame>"
	"</table:table-cell>";

const char ods_content_row_close[] =
	"</table:table-row>";

const char ods_content_sheet_close[] =
	"</table:table>"
	"</office:spreadsheet>";

const char ods_content_3[] =
	"</office:body>"
	"</office:document-content>";
