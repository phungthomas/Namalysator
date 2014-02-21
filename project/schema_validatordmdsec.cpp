#include "..\Validating Parsers\mods-3-0-pimpl.hxx"
 
#include <iostream>
#include <sstream>
#include "../common_files/struct.h"

Error schema_validatordmdsec(const std::string &data,int lineError)
{
  try
  {
    // Instantiate individual parsers.
    //
    ::mods::v3::modsType_pimpl modsType_p;
    ::mods::v3::titleInfoType_pimpl titleInfoType_p;
    ::xml_schema::any_type_pimpl any_type_p;
    ::xml_schema::id_pimpl id_p;
    ::mods::v3::type_pimpl type_p;
    ::xml_schema::any_simple_type_pimpl any_simple_type_p;
    ::xml_schema::string_pimpl string_p;
    ::xml_schema::uri_pimpl uri_p;
    ::xlink::show_pimpl show_p;
    ::xlink::actuate_pimpl actuate_p;
    ::xml_schema::language_pimpl language_p;
    ::mods::v3::nameType_pimpl nameType_p;
    ::mods::v3::namePartType_pimpl namePartType_p;
    ::mods::v3::type2_pimpl type2_p;
    ::mods::v3::roleType_pimpl roleType_p;
    ::mods::v3::roleTerm_pimpl roleTerm_p;
    ::mods::v3::codeOrText_pimpl codeOrText_p;
    ::mods::v3::type1_pimpl type1_p;
    ::mods::v3::typeOfResourceType_pimpl typeOfResourceType_p;
    ::mods::v3::collection_pimpl collection_p;
    ::mods::v3::manuscript_pimpl manuscript_p;
    ::mods::v3::genreType_pimpl genreType_p;
    ::mods::v3::originInfoType_pimpl originInfoType_p;
    ::mods::v3::placeType_pimpl placeType_p;
    ::mods::v3::placeTermType_pimpl placeTermType_p;
    ::mods::v3::placeAuthority_pimpl placeAuthority_p;
    ::mods::v3::dateType_pimpl dateType_p;
    ::mods::v3::encoding_pimpl encoding_p;
    ::mods::v3::qualifier_pimpl qualifier_p;
    ::mods::v3::point_pimpl point_p;
    ::mods::v3::keyDate_pimpl keyDate_p;
    ::mods::v3::issuance_pimpl issuance_p;
    ::mods::v3::languageType_pimpl languageType_p;
    ::mods::v3::languageTerm_pimpl languageTerm_p;
    ::mods::v3::authority_pimpl authority_p;
    ::mods::v3::physicalDescriptionType_pimpl physicalDescriptionType_p;
    ::mods::v3::form_pimpl form_p;
    ::mods::v3::reformattingQuality_pimpl reformattingQuality_p;
    ::mods::v3::digitalOrigin_pimpl digitalOrigin_p;
    ::mods::v3::unstructuredText_pimpl unstructuredText_p;
    ::mods::v3::targetAudienceType_pimpl targetAudienceType_p;
    ::mods::v3::subjectType_pimpl subjectType_p;
    ::mods::v3::geographicCode_pimpl geographicCode_p;
    ::mods::v3::hierarchicalGeographic_pimpl hierarchicalGeographic_p;
    ::mods::v3::cartographics_pimpl cartographics_p;
    ::mods::v3::classificationType_pimpl classificationType_p;
    ::mods::v3::relatedItemType_pimpl relatedItemType_p;
    ::mods::v3::identifierType_pimpl identifierType_p;
    ::mods::v3::invalid_pimpl invalid_p;
    ::mods::v3::locationType_pimpl locationType_p;
    ::mods::v3::physicalLocation_pimpl physicalLocation_p;
    ::mods::v3::url_pimpl url_p;
    ::mods::v3::extensionType_pimpl extensionType_p;
    ::mods::v3::recordInfoType_pimpl recordInfoType_p;
    ::mods::v3::sourceType_pimpl sourceType_p;
    ::mods::v3::recordIdentifier_pimpl recordIdentifier_p;
    ::mods::v3::version_pimpl version_p;
    ::mods::v3::partType_pimpl partType_p;
    ::mods::v3::detailType_pimpl detailType_p;
    ::xml_schema::positive_integer_pimpl positive_integer_p;
    ::mods::v3::extentType_pimpl extentType_p;
    ::mods::v3::baseDateType_pimpl baseDateType_p;
    ::mods::v3::type3_pimpl type3_p;

    // Connect the parsers together.
    // 
    modsType_p.parsers (titleInfoType_p,
                        nameType_p,
                        typeOfResourceType_p,
                        genreType_p,
                        originInfoType_p,
                        languageType_p,
                        physicalDescriptionType_p,
                        unstructuredText_p,
                        unstructuredText_p,
                        targetAudienceType_p,
                        unstructuredText_p,
                        subjectType_p,
                        classificationType_p,
                        relatedItemType_p,
                        identifierType_p,
                        locationType_p,
                        unstructuredText_p,
                        extensionType_p,
                        recordInfoType_p,
                        id_p,
                        version_p);

    titleInfoType_p.parsers (any_type_p,
                             any_type_p,
                             any_type_p,
                             any_type_p,
                             any_type_p,
                             id_p,
                             type_p,
                             any_simple_type_p,
                             string_p,
                             string_p,
                             uri_p,
                             string_p,
                             string_p,
                             string_p,
                             show_p,
                             actuate_p,
                             any_simple_type_p,
                             language_p,
                             any_simple_type_p,
                             any_simple_type_p);

    nameType_p.parsers (namePartType_p,
                        any_type_p,
                        any_type_p,
                        roleType_p,
                        any_type_p,
                        id_p,
                        type1_p,
                        any_simple_type_p,
                        string_p,
                        uri_p,
                        string_p,
                        string_p,
                        string_p,
                        show_p,
                        actuate_p,
                        any_simple_type_p,
                        language_p,
                        any_simple_type_p,
                        any_simple_type_p);

    namePartType_p.parsers (type2_p);

    roleType_p.parsers (roleTerm_p);

    roleTerm_p.parsers (any_simple_type_p,
                        codeOrText_p);

    typeOfResourceType_p.parsers (collection_p,
                                  manuscript_p);

    genreType_p.parsers (any_simple_type_p,
                         any_simple_type_p,
                         language_p,
                         any_simple_type_p,
                         any_simple_type_p);

    originInfoType_p.parsers (placeType_p,
                              any_type_p,
                              dateType_p,
                              dateType_p,
                              dateType_p,
                              dateType_p,
                              dateType_p,
                              dateType_p,
                              dateType_p,
                              any_type_p,
                              issuance_p,
                              any_type_p,
                              any_simple_type_p,
                              language_p,
                              any_simple_type_p,
                              any_simple_type_p);

    placeType_p.parsers (placeTermType_p);

    placeTermType_p.parsers (placeAuthority_p,
                             codeOrText_p);

    dateType_p.parsers (encoding_p,
                        qualifier_p,
                        point_p,
                        keyDate_p);

    languageType_p.parsers (languageTerm_p);

    languageTerm_p.parsers (authority_p,
                            codeOrText_p);

    physicalDescriptionType_p.parsers (form_p,
                                       reformattingQuality_p,
                                       any_type_p,
                                       any_type_p,
                                       digitalOrigin_p,
                                       unstructuredText_p,
                                       any_simple_type_p,
                                       language_p,
                                       any_simple_type_p,
                                       any_simple_type_p);

    form_p.parsers (any_simple_type_p);

    unstructuredText_p.parsers (string_p,
                                uri_p,
                                string_p,
                                string_p,
                                string_p,
                                show_p,
                                actuate_p,
                                any_simple_type_p,
                                language_p,
                                any_simple_type_p,
                                any_simple_type_p,
                                string_p,
                                string_p);

    targetAudienceType_p.parsers (any_simple_type_p,
                                  any_simple_type_p,
                                  language_p,
                                  any_simple_type_p,
                                  any_simple_type_p);

    subjectType_p.parsers (any_type_p,
                           any_type_p,
                           dateType_p,
                           titleInfoType_p,
                           nameType_p,
                           geographicCode_p,
                           hierarchicalGeographic_p,
                           cartographics_p,
                           any_type_p,
                           id_p,
                           string_p,
                           uri_p,
                           string_p,
                           string_p,
                           string_p,
                           show_p,
                           actuate_p,
                           any_simple_type_p,
                           any_simple_type_p,
                           language_p,
                           any_simple_type_p,
                           any_simple_type_p);

    geographicCode_p.parsers (placeAuthority_p);

    hierarchicalGeographic_p.parsers (any_type_p,
                                      any_type_p,
                                      any_type_p,
                                      any_type_p,
                                      any_type_p,
                                      any_type_p,
                                      any_type_p,
                                      any_type_p,
                                      any_type_p,
                                      any_type_p);

    cartographics_p.parsers (any_type_p,
                             any_type_p,
                             any_type_p);

    classificationType_p.parsers (any_simple_type_p,
                                  any_simple_type_p,
                                  any_simple_type_p,
                                  language_p,
                                  any_simple_type_p,
                                  any_simple_type_p);

    relatedItemType_p.parsers (titleInfoType_p,
                               nameType_p,
                               typeOfResourceType_p,
                               genreType_p,
                               originInfoType_p,
                               languageType_p,
                               physicalDescriptionType_p,
                               unstructuredText_p,
                               unstructuredText_p,
                               targetAudienceType_p,
                               unstructuredText_p,
                               subjectType_p,
                               classificationType_p,
                               relatedItemType_p,
                               identifierType_p,
                               locationType_p,
                               unstructuredText_p,
                               extensionType_p,
                               recordInfoType_p,
                               id_p,
                               version_p,
                               partType_p,
                               type3_p,
                               string_p,
                               string_p,
                               uri_p,
                               string_p,
                               string_p,
                               string_p,
                               show_p,
                               actuate_p);

    identifierType_p.parsers (any_simple_type_p,
                              any_simple_type_p,
                              invalid_p,
                              any_simple_type_p,
                              language_p,
                              any_simple_type_p,
                              any_simple_type_p);

    locationType_p.parsers (physicalLocation_p,
                            url_p);

    physicalLocation_p.parsers (any_simple_type_p,
                                any_simple_type_p,
                                language_p,
                                any_simple_type_p,
                                any_simple_type_p,
                                any_simple_type_p);

    url_p.parsers (any_simple_type_p,
                   any_simple_type_p);

    recordInfoType_p.parsers (sourceType_p,
                              dateType_p,
                              dateType_p,
                              recordIdentifier_p,
                              languageType_p,
                              any_type_p,
                              any_simple_type_p,
                              language_p,
                              any_simple_type_p,
                              any_simple_type_p);

    sourceType_p.parsers (any_simple_type_p,
                          any_simple_type_p,
                          language_p,
                          any_simple_type_p,
                          any_simple_type_p);

    recordIdentifier_p.parsers (any_simple_type_p);

    partType_p.parsers (detailType_p,
                        extentType_p,
                        baseDateType_p,
                        unstructuredText_p);

    detailType_p.parsers (any_type_p,
                          any_type_p,
                          any_type_p,
                          any_simple_type_p,
                          positive_integer_p);

    extentType_p.parsers (any_type_p,
                          any_type_p,
                          positive_integer_p,
                          any_type_p,
                          any_simple_type_p);

    baseDateType_p.parsers (encoding_p,
                            qualifier_p,
                            point_p);

    // Parse the XML document.
    //
    ::xml_schema::document doc_p (
      modsType_p,
      "http://www.loc.gov/mods/v3",
      "mods");

    modsType_p.pre ();	

	doc_p.parse(data.c_str(), data.size(), true);
    modsType_p.post_modsType ();
  }
  catch (const ::xml_schema::parsing & e) 
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