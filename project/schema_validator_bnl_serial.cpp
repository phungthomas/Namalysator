#include "..\Validating Parsers\bnl-serial_v1.0-pimpl.hxx"

#include <iostream>
#include <sstream>
#include "../common_files/struct.h"

Error schema_validator_bnl_serial(const std::string &data)
{
  try
  {
    // Instantiate individual parsers.
    //
    ::bnl_serial_v1_0::Serial_pimpl Serial_p;
    ::bnl_serial_v1_0::ct_HIERARCHY_pimpl ct_HIERARCHY_p;
    ::bnl_serial_v1_0::ct_FRONT_pimpl ct_FRONT_p;
    ::bnl_serial_v1_0::ct_TITLE_SECTION_pimpl ct_TITLE_SECTION_p;
    ::bnl_serial_v1_0::ct_FINAL_pimpl ct_FINAL_p;
    ::bnl_serial_v1_0::ct_FPTR_pimpl ct_FPTR_p;
    ::xml_schema::any_type_pimpl any_type_p;
    ::bnl_serial_v1_0::ct_SEQ_pimpl ct_SEQ_p;
    ::bnl_serial_v1_0::par_pimpl par_p;
    ::bnl_serial_v1_0::CONTENT1_pimpl CONTENT1_p;
    ::bnl_serial_v1_0::ct_TABLE_LIKE_STRUCT_pimpl ct_TABLE_LIKE_STRUCT_p;
    ::bnl_serial_v1_0::ct_ILLUSTRATION_LIKE_STRUCT_pimpl ct_ILLUSTRATION_LIKE_STRUCT_p;
    ::bnl_serial_v1_0::ct_FORMULA_pimpl ct_FORMULA_p;
    ::bnl_serial_v1_0::ct_PAGE_LIKE_pimpl ct_PAGE_LIKE_p;
    ::bnl_serial_v1_0::CONTENT_pimpl CONTENT_p;
    ::bnl_serial_v1_0::ct_PARAGRAPH_pimpl ct_PARAGRAPH_p;
    ::bnl_serial_v1_0::ct_FOOTNOTE_PARAGRAPH_pimpl ct_FOOTNOTE_PARAGRAPH_p;
    ::bnl_serial_v1_0::ct_LIST_LIKE_pimpl ct_LIST_LIKE_p;
    ::bnl_serial_v1_0::DATA_pimpl DATA_p;
    ::bnl_serial_v1_0::ct_ITEM_pimpl ct_ITEM_p;
    ::bnl_serial_v1_0::ct_CHAPTER_LIKE_pimpl ct_CHAPTER_LIKE_p;
    ::bnl_serial_v1_0::ct_HEADING_pimpl ct_HEADING_p;
    ::bnl_serial_v1_0::MOTTO_pimpl MOTTO_p;
    ::bnl_serial_v1_0::HEADING_TEXT_pimpl HEADING_TEXT_p;
    ::bnl_serial_v1_0::ct_BODY_pimpl ct_BODY_p;
    ::bnl_serial_v1_0::ct_BODY_CONTENT_pimpl ct_BODY_CONTENT_p;
    ::bnl_serial_v1_0::ct_MAP_GROUP_pimpl ct_MAP_GROUP_p;
    ::bnl_serial_v1_0::ct_ILLUSTRATION_GROUP_pimpl ct_ILLUSTRATION_GROUP_p;
    ::bnl_serial_v1_0::ct_CHART_DIAGRAM_GROUP_pimpl ct_CHART_DIAGRAM_GROUP_p;
    ::bnl_serial_v1_0::ct_TABLE_GROUP_pimpl ct_TABLE_GROUP_p;
    ::bnl_serial_v1_0::ct_ISSUE_pimpl ct_ISSUE_p;
    ::bnl_serial_v1_0::ct_MAIN_pimpl ct_MAIN_p;
    ::bnl_serial_v1_0::ct_BACK_pimpl ct_BACK_p;

    // Connect the parsers together.
    //
    Serial_p.parsers (ct_HIERARCHY_p);

    ct_HIERARCHY_p.parsers (ct_FRONT_p,
                            ct_ISSUE_p,
                            ct_BACK_p);

    ct_FRONT_p.parsers (ct_TITLE_SECTION_p,
                        ct_PAGE_LIKE_p,
                        ct_PAGE_LIKE_p,
                        ct_PAGE_LIKE_p,
                        ct_PAGE_LIKE_p,
                        ct_PAGE_LIKE_p,
                        ct_LIST_LIKE_p,
                        ct_LIST_LIKE_p,
                        ct_LIST_LIKE_p,
                        ct_LIST_LIKE_p,
                        ct_LIST_LIKE_p,
                        ct_LIST_LIKE_p,
                        ct_LIST_LIKE_p,
                        ct_LIST_LIKE_p,
                        ct_CHAPTER_LIKE_p,
                        ct_CHAPTER_LIKE_p,
                        ct_CHAPTER_LIKE_p,
                        ct_CHAPTER_LIKE_p,
                        ct_CHAPTER_LIKE_p,
                        ct_CHAPTER_LIKE_p,
                        ct_CHAPTER_LIKE_p,
                        ct_CHAPTER_LIKE_p,
                        ct_CHAPTER_LIKE_p,
                        ct_FINAL_p);

    ct_TITLE_SECTION_p.parsers (ct_FINAL_p,
                                ct_FINAL_p,
                                ct_FINAL_p,
                                ct_FINAL_p,
                                CONTENT1_p);

    ct_FINAL_p.parsers (ct_FPTR_p);

    ct_FPTR_p.parsers (any_type_p,
                       ct_SEQ_p,
                       par_p);

    ct_SEQ_p.parsers (any_type_p);

    par_p.parsers (any_type_p,
                   ct_SEQ_p);

    CONTENT1_p.parsers (ct_TABLE_LIKE_STRUCT_p,
                        ct_ILLUSTRATION_LIKE_STRUCT_p,
                        ct_ILLUSTRATION_LIKE_STRUCT_p,
                        ct_ILLUSTRATION_LIKE_STRUCT_p,
                        ct_ILLUSTRATION_LIKE_STRUCT_p,
                        ct_ILLUSTRATION_LIKE_STRUCT_p,
                        ct_FORMULA_p);

    ct_TABLE_LIKE_STRUCT_p.parsers (ct_FINAL_p,
                                    ct_FINAL_p);

    ct_ILLUSTRATION_LIKE_STRUCT_p.parsers (ct_FINAL_p,
                                           ct_FINAL_p);

    ct_FORMULA_p.parsers (ct_FINAL_p);

    ct_PAGE_LIKE_p.parsers (CONTENT_p);

    CONTENT_p.parsers (ct_FINAL_p,
                       ct_TABLE_LIKE_STRUCT_p,
                       ct_FINAL_p,
                       ct_PARAGRAPH_p,
                       ct_ILLUSTRATION_LIKE_STRUCT_p,
                       ct_ILLUSTRATION_LIKE_STRUCT_p,
                       ct_ILLUSTRATION_LIKE_STRUCT_p,
                       ct_ILLUSTRATION_LIKE_STRUCT_p,
                       ct_ILLUSTRATION_LIKE_STRUCT_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FORMULA_p,
                       ct_FOOTNOTE_PARAGRAPH_p,
                       ct_FINAL_p);

    ct_PARAGRAPH_p.parsers (ct_FINAL_p,
                            ct_FINAL_p);

    ct_FOOTNOTE_PARAGRAPH_p.parsers (ct_FINAL_p);

    ct_LIST_LIKE_p.parsers (ct_FINAL_p,
                            DATA_p,
                            ct_LIST_LIKE_p,
                            ct_LIST_LIKE_p,
                            ct_LIST_LIKE_p,
                            ct_LIST_LIKE_p,
                            ct_LIST_LIKE_p,
                            ct_LIST_LIKE_p,
                            ct_LIST_LIKE_p,
                            ct_LIST_LIKE_p,
                            ct_LIST_LIKE_p,
                            ct_ITEM_p);

    DATA_p.parsers (ct_FINAL_p,
                    ct_FINAL_p,
                    ct_FINAL_p,
                    ct_FINAL_p);

    ct_ITEM_p.parsers (ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_ITEM_p);

    ct_CHAPTER_LIKE_p.parsers (ct_HEADING_p,
                               ct_CHAPTER_LIKE_p,
                               ct_BODY_p,
                               ct_LIST_LIKE_p,
                               ct_LIST_LIKE_p,
                               ct_LIST_LIKE_p,
                               ct_LIST_LIKE_p,
                               ct_LIST_LIKE_p,
                               ct_LIST_LIKE_p,
                               ct_LIST_LIKE_p,
                               ct_LIST_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_CHAPTER_LIKE_p,
                               ct_MAP_GROUP_p,
                               ct_ILLUSTRATION_GROUP_p,
                               ct_CHART_DIAGRAM_GROUP_p,
                               ct_TABLE_GROUP_p);

    ct_HEADING_p.parsers (ct_FINAL_p,
                          ct_FINAL_p,
                          ct_FINAL_p,
                          MOTTO_p,
                          HEADING_TEXT_p);

    MOTTO_p.parsers (ct_FINAL_p);

    HEADING_TEXT_p.parsers (ct_FINAL_p);

    ct_BODY_p.parsers (ct_BODY_CONTENT_p,
                       ct_FOOTNOTE_PARAGRAPH_p,
                       ct_ILLUSTRATION_LIKE_STRUCT_p,
                       ct_ILLUSTRATION_LIKE_STRUCT_p,
                       ct_ILLUSTRATION_LIKE_STRUCT_p,
                       ct_ILLUSTRATION_LIKE_STRUCT_p,
                       ct_ILLUSTRATION_LIKE_STRUCT_p,
                       ct_TABLE_LIKE_STRUCT_p,
                       ct_LIST_LIKE_p);

    ct_BODY_CONTENT_p.parsers (ct_FINAL_p,
                               ct_PARAGRAPH_p,
                               ct_FORMULA_p);

    ct_MAP_GROUP_p.parsers (ct_ILLUSTRATION_LIKE_STRUCT_p);

    ct_ILLUSTRATION_GROUP_p.parsers (ct_ILLUSTRATION_LIKE_STRUCT_p);

    ct_CHART_DIAGRAM_GROUP_p.parsers (ct_ILLUSTRATION_LIKE_STRUCT_p);

    ct_TABLE_GROUP_p.parsers (ct_TABLE_LIKE_STRUCT_p);

    ct_ISSUE_p.parsers (ct_MAIN_p,
                        ct_FRONT_p,
                        ct_BACK_p);

    ct_MAIN_p.parsers (ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_FINAL_p);

    ct_BACK_p.parsers (ct_PAGE_LIKE_p,
                       ct_PAGE_LIKE_p,
                       ct_PAGE_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_LIST_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_CHAPTER_LIKE_p,
                       ct_FINAL_p);


    // Parse the XML document.
    //
    ::xml_schema::document doc_p (
      Serial_p,
      "Serial");

    Serial_p.pre();
   doc_p.parse (data.c_str(), data.size(), true);
//	doc_p.parse(data);
    Serial_p.post_Serial();
  }
  catch (const ::xml_schema::parsing & e) 
 {		
	Error error;
	error.errorcolumn = e.diagnostics()[0].column();
	error.errorline = e.diagnostics()[0].line()+1 ;
	error.message = e.diagnostics()[0].message();
	error.severity = e.diagnostics()[0].severity();		
	return error;
  }

  Error error;
  return  error;

}
