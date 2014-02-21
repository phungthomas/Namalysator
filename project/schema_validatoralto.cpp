#include <iostream>
#include <sstream>
#include "schema_validatoralto.h"
#include "../Validating Parsers/alto-2-0-pimpl.hxx"

////////////////////////////////////////////
// Old style validator
Error schema_validatoralto(const std::string &data)
{
	::alto::alto_pimpl alto_p;
    ::alto::Description_pimpl Description_p;
    ::alto::MeasurementUnit_pimpl MeasurementUnit_p;
    ::alto::sourceImageInformationType_pimpl sourceImageInformationType_p;
    ::xml_schema::string_pimpl string_p;
    ::alto::fileIdentifierType_pimpl fileIdentifierType_p;
    ::xml_schema::any_simple_type_pimpl any_simple_type_p;
    ::alto::OCRProcessing_pimpl OCRProcessing_p;
    ::alto::processingStepType_pimpl processingStepType_p;
    ::alto::dateTimeType_pimpl dateTimeType_p;
    ::alto::processingSoftwareType_pimpl processingSoftwareType_p;
    ::xml_schema::id_pimpl id_p;
    ::alto::Styles_pimpl Styles_p;
    ::alto::TextStyle_pimpl TextStyle_p;
    ::alto::fontTypeType_pimpl fontTypeType_p;
    ::alto::fontWidthType_pimpl fontWidthType_p;
    ::xml_schema::float_pimpl float_p;
    ::xml_schema::hex_binary_pimpl hex_binary_p;
    ::alto::fontStylesType_pimpl fontStylesType_p;
    ::alto::ParagraphStyle_pimpl ParagraphStyle_p;
    ::alto::ALIGN_pimpl ALIGN_p;
    ::alto::Layout_pimpl Layout_p;
    ::alto::Page_pimpl Page_p;
    ::alto::PageSpaceType_pimpl PageSpaceType_p;
    ::alto::TextBlockType_pimpl TextBlockType_p;
    ::alto::ShapeType_pimpl ShapeType_p;
    ::alto::PolygonType_pimpl PolygonType_p;
    ::alto::PointsType_pimpl PointsType_p;
    ::alto::EllipseType_pimpl EllipseType_p;
    ::alto::CircleType_pimpl CircleType_p;
    ::xml_schema::idrefs_pimpl idrefs_p;
    ::xml_schema::int_pimpl int_p;
    ::xml_schema::idref_pimpl idref_p;
    ::xml_schema::uri_pimpl uri_p;
    ::xlink::show_pimpl show_p;
    ::xlink::actuate_pimpl actuate_p;
    ::alto::TextLine_pimpl TextLine_p;
    ::alto::StringType_pimpl StringType_p;
    ::alto::ALTERNATIVE_pimpl ALTERNATIVE_p;
    ::alto::CONTENT_pimpl CONTENT_p;
    ::alto::SUBS_TYPE_pimpl SUBS_TYPE_p;
    ::alto::WC_pimpl WC_p;
    ::alto::SP_pimpl SP_p;
    ::alto::HYP_pimpl HYP_p;
    ::xml_schema::boolean_pimpl boolean_p;
    ::xml_schema::language_pimpl language_p;
    ::alto::IllustrationType_pimpl IllustrationType_p;
    ::alto::GraphicalElementType_pimpl GraphicalElementType_p;
    ::alto::ComposedBlockType_pimpl ComposedBlockType_p;
    ::alto::QUALITY_pimpl QUALITY_p;
    ::alto::POSITION_pimpl POSITION_p;
    ::alto::PC_pimpl PC_p;

    alto_p.parsers (Description_p,
                    Styles_p,
                    Layout_p);

    Description_p.parsers (MeasurementUnit_p,
                           sourceImageInformationType_p,
                           OCRProcessing_p);

    sourceImageInformationType_p.parsers (string_p,
                                          fileIdentifierType_p);

    fileIdentifierType_p.parsers (any_simple_type_p);

    OCRProcessing_p.parsers (processingStepType_p,
                             processingStepType_p,
                             processingStepType_p,
                             id_p);

    processingStepType_p.parsers (dateTimeType_p,
                                  string_p,
                                  string_p,
                                  string_p,
                                  processingSoftwareType_p);

    processingSoftwareType_p.parsers (string_p,
                                      string_p,
                                      string_p,
                                      string_p);

    Styles_p.parsers (TextStyle_p,
                      ParagraphStyle_p);

    TextStyle_p.parsers (id_p,
                         string_p,
                         fontTypeType_p,
                         fontWidthType_p,
                         float_p,
                         hex_binary_p,
                         fontStylesType_p);

    ParagraphStyle_p.parsers (id_p,
                              ALIGN_p,
                              float_p,
                              float_p,
                              float_p,
                              float_p);

    Layout_p.parsers (Page_p,
                      idrefs_p);

    Page_p.parsers (PageSpaceType_p,
                    PageSpaceType_p,
                    PageSpaceType_p,
                    PageSpaceType_p,
                    PageSpaceType_p,
                    id_p,
                    string_p,
                    idrefs_p,
                    int_p,
                    int_p,
                    int_p,
                    string_p,
                    QUALITY_p,
                    string_p,
                    POSITION_p,
                    idref_p,
                    float_p,
                    PC_p);

    PageSpaceType_p.parsers (TextBlockType_p,
                             IllustrationType_p,
                             GraphicalElementType_p,
                             ComposedBlockType_p,
                             id_p,
                             idrefs_p,
                             float_p,
                             float_p,
                             float_p,
                             float_p);

    TextBlockType_p.parsers (ShapeType_p,
                             id_p,
                             idrefs_p,
                             int_p,
                             int_p,
                             int_p,
                             int_p,
                             float_p,
                             idref_p,
                             string_p,
                             uri_p,
                             string_p,
                             string_p,
                             string_p,
                             show_p,
                             actuate_p,
                             TextLine_p,
                             language_p);

    ShapeType_p.parsers (PolygonType_p,
                         EllipseType_p,
                         CircleType_p);

    PolygonType_p.parsers (PointsType_p);

    EllipseType_p.parsers (any_simple_type_p,
                           any_simple_type_p,
                           any_simple_type_p,
                           any_simple_type_p);

    CircleType_p.parsers (any_simple_type_p,
                          any_simple_type_p,
                          any_simple_type_p);

    TextLine_p.parsers (StringType_p,
                        SP_p,
                        HYP_p,
                        id_p,
                        idrefs_p,
                        float_p,
                        float_p,
                        float_p,
                        float_p,
                        float_p,
                        boolean_p);

    StringType_p.parsers (ALTERNATIVE_p,
                          id_p,
                          idrefs_p,
                          float_p,
                          float_p,
                          float_p,
                          float_p,
                          CONTENT_p,
                          fontStylesType_p,
                          SUBS_TYPE_p,
                          string_p,
                          WC_p,
                          string_p);

    ALTERNATIVE_p.parsers (string_p);

    SP_p.parsers (id_p,
                  float_p,
                  float_p,
                  float_p);

    HYP_p.parsers (float_p,
                   float_p,
                   float_p,
                   any_simple_type_p);

    IllustrationType_p.parsers (ShapeType_p,
                                id_p,
                                idrefs_p,
                                int_p,
                                int_p,
                                int_p,
                                int_p,
                                float_p,
                                idref_p,
                                string_p,
                                uri_p,
                                string_p,
                                string_p,
                                string_p,
                                show_p,
                                actuate_p,
                                string_p,
                                string_p);

    ComposedBlockType_p.parsers (ShapeType_p,
                                 id_p,
                                 idrefs_p,
                                 int_p,
                                 int_p,
                                 int_p,
                                 int_p,
                                 float_p,
                                 idref_p,
                                 string_p,
                                 uri_p,
                                 string_p,
                                 string_p,
                                 string_p,
                                 show_p,
                                 actuate_p,
                                 TextBlockType_p,
                                 IllustrationType_p,
                                 GraphicalElementType_p,
                                 ComposedBlockType_p,
                                 string_p,
                                 string_p);
  try
  {
    ::xml_schema::document doc_p (
      alto_p,
      "http://schema.ccs-gmbh.com/ALTO",
      "alto");

    alto_p.pre ();
   doc_p.parse (data.c_str(), data.size(), true);
//	doc_p.parse(data);
    alto_p.post_alto ();
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