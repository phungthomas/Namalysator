#include <sstream>
#include <iostream>
#include "schema_validatorstruct.h"

// global instance
validator_bnl_newspaper_v1_3 g_validator_bnl_newspaper_v1_3;

validator_bnl_newspaper_v1_3::validator_bnl_newspaper_v1_3()
{
    // Connect the parsers together.
    //
    Newspaper_p.parsers (ct_HIERARCHY_p);

    ct_HIERARCHY_p.parsers (ct_SUPPLEMENT_p,
                            ct_ISSUE_p);

    ct_SUPPLEMENT_p.parsers (TITLE_SECTION1_p,
                             CONTENT1_p);

    TITLE_SECTION1_p.parsers (ct_FINAL_p,
                              ct_FINAL_p,
                              ct_LIST_LIKE_p,
                              ct_FINAL_p,
                              ct_ILLUSTRATION_LIKE_STRUCT_p,
                              ct_FINAL_p,
                              ct_FINAL_p,
                              ct_FINAL_p,
                              ct_FINAL_p,
                              ct_FINAL_p);

    ct_FINAL_p.parsers (ct_FPTR_p);

    ct_FPTR_p.parsers (any_type_p,
                       ct_SEQ_p,
                       par_p);

    ct_SEQ_p.parsers (any_type_p);

    par_p.parsers (any_type_p,
                   ct_SEQ_p);

    ct_LIST_LIKE_p.parsers (ct_FINAL_p,
                            DATA_p,
                            ct_LIST_LIKE_p,
                            ct_LIST_LIKE_p,
                            ct_ITEM_p);

    DATA_p.parsers (ct_FINAL_p,
                    ct_FINAL_p,
                    ct_FINAL_p,
                    ct_FINAL_p,
                    ct_FINAL_p);

    ct_ITEM_p.parsers (ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_ITEM_p);

    ct_ILLUSTRATION_LIKE_STRUCT_p.parsers (ct_FINAL_p,
                                           ct_FINAL_p,
                                           ct_FINAL_p);

    CONTENT1_p.parsers (ct_FINAL_p,
                        ct_FINAL_p,
                        ct_SECTION_p,
                        ct_PARAGRAPH_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_FINAL_p,
                        ct_FINAL_p,
                        ct_FINAL_p,
                        ct_FINAL_p);

    ct_SECTION_p.parsers (ct_CHAPTER_LIKE_HEADING_p,
                          ct_BODY_SECTION_p,
                          ct_SECTION_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p);

    ct_CHAPTER_LIKE_HEADING_p.parsers (ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p);

    ct_BODY_SECTION_p.parsers (ct_BODY_CONTENT_SECTION_p,
                               ct_FOOTNOTE_PARAGRAPH_p,
                               ct_ILLUSTRATION_LIKE_STRUCT_p,
                               ct_TABLE_LIKE_STRUCT_p);

    ct_BODY_CONTENT_SECTION_p.parsers (ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_PARAGRAPH_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p);

    ct_PARAGRAPH_p.parsers (ct_FINAL_p);

    ct_FOOTNOTE_PARAGRAPH_p.parsers (ct_FINAL_p);

    ct_TABLE_LIKE_STRUCT_p.parsers (ct_FINAL_p,
                                    ct_FINAL_p);

    ct_ARTICLE_LIKE_p.parsers (ct_CHAPTER_LIKE_HEADING_p,
                               ct_BODY_ARTICLE_p,
                               ct_LIST_LIKE_p,
                               ct_LIST_LIKE_p,
                               ct_CHAPTER_p);

    ct_BODY_ARTICLE_p.parsers (ct_BODY_CONTENT_ARTICLE_p,
                               ct_FOOTNOTE_PARAGRAPH_p,
                               ct_ILLUSTRATION_LIKE_STRUCT_p,
                               ct_TABLE_LIKE_STRUCT_p);

    ct_BODY_CONTENT_ARTICLE_p.parsers (ct_FINAL_p,
                                       ct_PARAGRAPH_p,
                                       ct_FINAL_p,
                                       ct_FORMULA_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p);

    ct_FORMULA_p.parsers (ct_FINAL_p);

    ct_CHAPTER_p.parsers (ct_CHAPTER_HEADING_p,
                          ct_BODY_CHAPTER_p,
                          ct_LIST_LIKE_p,
                          ct_CHAPTER_p);

    ct_CHAPTER_HEADING_p.parsers (ct_FINAL_p,
                                  ct_FINAL_p,
                                  ct_FINAL_p);

    ct_BODY_CHAPTER_p.parsers (ct_BODY_CONTENT_CHAPTER_p,
                               ct_FOOTNOTE_PARAGRAPH_p,
                               ct_ILLUSTRATION_LIKE_STRUCT_p,
                               ct_TABLE_LIKE_STRUCT_p);

    ct_BODY_CONTENT_CHAPTER_p.parsers (ct_PARAGRAPH_p,
                                       ct_FINAL_p,
                                       ct_FORMULA_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p);

    ct_ISSUE_p.parsers (TITLE_SECTION_p,
                        CONTENT_p,
                        ct_SUPPLEMENT_p);

    TITLE_SECTION_p.parsers (ct_FINAL_p,
                             ct_FINAL_p,
                             ct_LIST_LIKE_p,
                             ct_FINAL_p,
                             ct_ILLUSTRATION_LIKE_STRUCT_p,
                             ct_FINAL_p,
                             ct_FINAL_p,
                             ct_FINAL_p,
                             ct_FINAL_p,
                             ct_FINAL_p);

    CONTENT_p.parsers (ct_FINAL_p,
                       ct_FINAL_p,
                       ct_SECTION_p,
                       ct_PARAGRAPH_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p);
}

validator_bnl_newspaper_v1_3::~validator_bnl_newspaper_v1_3()
{
}

Error validator_bnl_newspaper_v1_3::validate(const std::string &data,int lineError)
{
  try
  {
    // Parse the XML document.
    //
    ::xml_schema::document doc_p (Newspaper_p, "Newspaper");

    Newspaper_p.pre ();
	doc_p.parse (data.c_str(), data.size(), true);  
    Newspaper_p.post_Newspaper ();
  }
  catch (const ::xml_schema::parsing& e)
  {
	Error error;
	
	error.errorcolumn = e.diagnostics()[0].column();
	error.errorline = e.diagnostics()[0].line() + lineError;
	error.message = e.diagnostics()[0].message();
	error.severity = e.diagnostics()[0].severity();
	return error;
  }

  Error error;
  return  error;
}

Error validator_bnl_newspaper_v1_3::validate_oldstyle(const std::string &data,int lineError)
{
  try
  {
	::Newspaper_pimpl Newspaper_p;
    ::ct_HIERARCHY_pimpl ct_HIERARCHY_p;
    ::ct_SUPPLEMENT_pimpl ct_SUPPLEMENT_p;
    ::TITLE_SECTION1_pimpl TITLE_SECTION1_p;
    ::ct_FINAL_pimpl ct_FINAL_p;
    ::ct_FPTR_pimpl ct_FPTR_p;
    ::xml_schema::any_type_pimpl any_type_p;
    ::ct_SEQ_pimpl ct_SEQ_p;
    ::par_pimpl par_p;
    ::ct_LIST_LIKE_pimpl ct_LIST_LIKE_p;
    ::DATA_pimpl DATA_p;
    ::ct_ITEM_pimpl ct_ITEM_p;
    ::ct_ILLUSTRATION_LIKE_STRUCT_pimpl ct_ILLUSTRATION_LIKE_STRUCT_p;
    ::CONTENT1_pimpl CONTENT1_p;
    ::ct_SECTION_pimpl ct_SECTION_p;
    ::ct_CHAPTER_LIKE_HEADING_pimpl ct_CHAPTER_LIKE_HEADING_p;
    ::ct_BODY_SECTION_pimpl ct_BODY_SECTION_p;
    ::ct_BODY_CONTENT_SECTION_pimpl ct_BODY_CONTENT_SECTION_p;
    ::ct_PARAGRAPH_pimpl ct_PARAGRAPH_p;
    ::ct_FOOTNOTE_PARAGRAPH_pimpl ct_FOOTNOTE_PARAGRAPH_p;
    ::ct_TABLE_LIKE_STRUCT_pimpl ct_TABLE_LIKE_STRUCT_p;
    ::ct_ARTICLE_LIKE_pimpl ct_ARTICLE_LIKE_p;
    ::ct_BODY_ARTICLE_pimpl ct_BODY_ARTICLE_p;
    ::ct_BODY_CONTENT_ARTICLE_pimpl ct_BODY_CONTENT_ARTICLE_p;
    ::ct_FORMULA_pimpl ct_FORMULA_p;
    ::ct_CHAPTER_pimpl ct_CHAPTER_p;
    ::ct_CHAPTER_HEADING_pimpl ct_CHAPTER_HEADING_p;
    ::ct_BODY_CHAPTER_pimpl ct_BODY_CHAPTER_p;
    ::ct_BODY_CONTENT_CHAPTER_pimpl ct_BODY_CONTENT_CHAPTER_p;
    ::ct_ISSUE_pimpl ct_ISSUE_p;
    ::TITLE_SECTION_pimpl TITLE_SECTION_p;
    ::CONTENT_pimpl CONTENT_p;
     // Connect the parsers together.
    //
    Newspaper_p.parsers (ct_HIERARCHY_p);

    ct_HIERARCHY_p.parsers (ct_SUPPLEMENT_p,
                            ct_ISSUE_p);

    ct_SUPPLEMENT_p.parsers (TITLE_SECTION1_p,
                             CONTENT1_p);

    TITLE_SECTION1_p.parsers (ct_FINAL_p,
                              ct_FINAL_p,
                              ct_LIST_LIKE_p,
                              ct_FINAL_p,
                              ct_ILLUSTRATION_LIKE_STRUCT_p,
                              ct_FINAL_p,
                              ct_FINAL_p,
                              ct_FINAL_p,
                              ct_FINAL_p,
                              ct_FINAL_p);

    ct_FINAL_p.parsers (ct_FPTR_p);

    ct_FPTR_p.parsers (any_type_p,
                       ct_SEQ_p,
                       par_p);

    ct_SEQ_p.parsers (any_type_p);

    par_p.parsers (any_type_p,
                   ct_SEQ_p);

    ct_LIST_LIKE_p.parsers (ct_FINAL_p,
                            DATA_p,
                            ct_LIST_LIKE_p,
                            ct_LIST_LIKE_p,
                            ct_ITEM_p);

    DATA_p.parsers (ct_FINAL_p,
                    ct_FINAL_p,
                    ct_FINAL_p,
                    ct_FINAL_p,
                    ct_FINAL_p);

    ct_ITEM_p.parsers (ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_ITEM_p);

    ct_ILLUSTRATION_LIKE_STRUCT_p.parsers (ct_FINAL_p,
                                           ct_FINAL_p,
                                           ct_FINAL_p);

    CONTENT1_p.parsers (ct_FINAL_p,
                        ct_FINAL_p,
                        ct_SECTION_p,
                        ct_PARAGRAPH_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_ARTICLE_LIKE_p,
                        ct_FINAL_p,
                        ct_FINAL_p,
                        ct_FINAL_p,
                        ct_FINAL_p);

    ct_SECTION_p.parsers (ct_CHAPTER_LIKE_HEADING_p,
                          ct_BODY_SECTION_p,
                          ct_SECTION_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p,
                          ct_ARTICLE_LIKE_p);

    ct_CHAPTER_LIKE_HEADING_p.parsers (ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p);

    ct_BODY_SECTION_p.parsers (ct_BODY_CONTENT_SECTION_p,
                               ct_FOOTNOTE_PARAGRAPH_p,
                               ct_ILLUSTRATION_LIKE_STRUCT_p,
                               ct_TABLE_LIKE_STRUCT_p);

    ct_BODY_CONTENT_SECTION_p.parsers (ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_PARAGRAPH_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p);

    ct_PARAGRAPH_p.parsers (ct_FINAL_p);

    ct_FOOTNOTE_PARAGRAPH_p.parsers (ct_FINAL_p);

    ct_TABLE_LIKE_STRUCT_p.parsers (ct_FINAL_p,
                                    ct_FINAL_p);

    ct_ARTICLE_LIKE_p.parsers (ct_CHAPTER_LIKE_HEADING_p,
                               ct_BODY_ARTICLE_p,
                               ct_LIST_LIKE_p,
                               ct_LIST_LIKE_p,
                               ct_CHAPTER_p);

    ct_BODY_ARTICLE_p.parsers (ct_BODY_CONTENT_ARTICLE_p,
                               ct_FOOTNOTE_PARAGRAPH_p,
                               ct_ILLUSTRATION_LIKE_STRUCT_p,
                               ct_TABLE_LIKE_STRUCT_p);

    ct_BODY_CONTENT_ARTICLE_p.parsers (ct_FINAL_p,
                                       ct_PARAGRAPH_p,
                                       ct_FINAL_p,
                                       ct_FORMULA_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p);

    ct_FORMULA_p.parsers (ct_FINAL_p);

    ct_CHAPTER_p.parsers (ct_CHAPTER_HEADING_p,
                          ct_BODY_CHAPTER_p,
                          ct_LIST_LIKE_p,
                          ct_CHAPTER_p);

    ct_CHAPTER_HEADING_p.parsers (ct_FINAL_p,
                                  ct_FINAL_p,
                                  ct_FINAL_p);

    ct_BODY_CHAPTER_p.parsers (ct_BODY_CONTENT_CHAPTER_p,
                               ct_FOOTNOTE_PARAGRAPH_p,
                               ct_ILLUSTRATION_LIKE_STRUCT_p,
                               ct_TABLE_LIKE_STRUCT_p);

    ct_BODY_CONTENT_CHAPTER_p.parsers (ct_PARAGRAPH_p,
                                       ct_FINAL_p,
                                       ct_FORMULA_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p,
                                       ct_FINAL_p);

    ct_ISSUE_p.parsers (TITLE_SECTION_p,
                        CONTENT_p,
                        ct_SUPPLEMENT_p);

    TITLE_SECTION_p.parsers (ct_FINAL_p,
                             ct_FINAL_p,
                             ct_LIST_LIKE_p,
                             ct_FINAL_p,
                             ct_ILLUSTRATION_LIKE_STRUCT_p,
                             ct_FINAL_p,
                             ct_FINAL_p,
                             ct_FINAL_p,
                             ct_FINAL_p,
                             ct_FINAL_p);

    CONTENT_p.parsers (ct_FINAL_p,
                       ct_FINAL_p,
                       ct_SECTION_p,
                       ct_PARAGRAPH_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_ARTICLE_LIKE_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p,
                       ct_FINAL_p);   // Parse the XML document.
    //
    ::xml_schema::document doc_p (Newspaper_p, "Newspaper");

    Newspaper_p.pre ();
	doc_p.parse (data.c_str(), data.size(), true);  
    Newspaper_p.post_Newspaper ();
  }
  catch (const ::xml_schema::parsing& e)
  {
	Error error;
	
	error.errorcolumn = e.diagnostics()[0].column();
	error.errorline = e.diagnostics()[0].line() + lineError;
	error.message = e.diagnostics()[0].message();
	error.severity = e.diagnostics()[0].severity();
	return error;
  }

  Error error;
  return  error;
}