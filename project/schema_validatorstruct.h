#ifndef SCHEMA_VALIDATORSTRUCT_H_
#define SCHEMA_VALIDATORSTRUCT_H_

#include <string>
#include "schemavalidator.h"
#include "..\Validating Parsers\bnl-newspaper_v1.3-pimpl.hxx"

class validator_bnl_newspaper_v1_3 : public schemavalidator
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
public:
	validator_bnl_newspaper_v1_3();
	virtual ~validator_bnl_newspaper_v1_3();
	virtual Error validate(const std::string &data,int lineError);
	Error validate_oldstyle(const std::string &data,int lineError);
};

extern validator_bnl_newspaper_v1_3 g_validator_bnl_newspaper_v1_3;

#endif // SCHEMA_VALIDATORSTUCT_H_