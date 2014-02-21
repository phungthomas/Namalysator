#include "..\Validating Parsers\mix-pimpl.hxx"

#include <iostream>
#include <sstream>
#include "../common_files/struct.h"


Error schema_validatormix(const std::string &data,int lineError)
{
  try
  {
    // Instantiate individual parsers.
    //
    ::mix::mix_pimpl mix_p;
    ::mix::BasicImageParametersType_pimpl BasicImageParametersType_p;
    ::mix::Format_pimpl Format_p;
    ::mix::typeOfFormatType_pimpl typeOfFormatType_p;
    ::xml_schema::any_simple_type_pimpl any_simple_type_p;
    ::mix::typeOfByteOrderType_pimpl typeOfByteOrderType_p;
    ::mix::Compression_pimpl Compression_p;
    ::mix::typeOfCompressionSchemeType_pimpl typeOfCompressionSchemeType_p;
    ::mix::typeOfCompressionLevelType_pimpl typeOfCompressionLevelType_p;
    ::mix::PhotometricInterpretation_pimpl PhotometricInterpretation_p;
    ::mix::typeOfColorSpaceType_pimpl typeOfColorSpaceType_p;
    ::mix::ICCProfile_pimpl ICCProfile_p;
    ::mix::typeOfStringType_pimpl typeOfStringType_p;
    ::mix::typeOfYCbCrSubSamplingType_pimpl typeOfYCbCrSubSamplingType_p;
    ::mix::typeOfYCbCrPositioningType_pimpl typeOfYCbCrPositioningType_p;
    ::mix::typeOfYcbCrCoefficientsType_pimpl typeOfYcbCrCoefficientsType_p;
    ::mix::typeOfReferenceBlackWhiteType_pimpl typeOfReferenceBlackWhiteType_p;
    ::mix::Segments_pimpl Segments_p;
    ::mix::typeOfSegmentTypeType_pimpl typeOfSegmentTypeType_p;
    ::mix::typeOfStripOffsetsType_pimpl typeOfStripOffsetsType_p;
    ::mix::typeOfRowsPerStripType_pimpl typeOfRowsPerStripType_p;
    ::mix::typeOfStripByteCountsType_pimpl typeOfStripByteCountsType_p;
    ::mix::typeOfTileWidthType_pimpl typeOfTileWidthType_p;
    ::mix::typeOfTileLengthType_pimpl typeOfTileLengthType_p;
    ::mix::typeOfTileOffsetsType_pimpl typeOfTileOffsetsType_p;
    ::mix::typeOfTileByteCountsType_pimpl typeOfTileByteCountsType_p;
    ::mix::typeOfPlanarConfigurationType_pimpl typeOfPlanarConfigurationType_p;
    ::mix::File_pimpl File_p;
    ::mix::typeOfImageIdentifierType_pimpl typeOfImageIdentifierType_p;
    ::mix::typeOfFileSizeType_pimpl typeOfFileSizeType_p;
    ::mix::Checksum_pimpl Checksum_p;
    ::mix::typeOfChecksumMethodType_pimpl typeOfChecksumMethodType_p;
    ::mix::typeOfChecksumValueType_pimpl typeOfChecksumValueType_p;
    ::mix::typeOfOrientationType_pimpl typeOfOrientationType_p;
    ::mix::typeOfDisplayOrientationType_pimpl typeOfDisplayOrientationType_p;
    ::mix::TargetedDisplayAR_pimpl TargetedDisplayAR_p;
    ::mix::typeOfXTargetedDisplayARType_pimpl typeOfXTargetedDisplayARType_p;
    ::mix::typeOfYTargetedDisplayARType_pimpl typeOfYTargetedDisplayARType_p;
    ::mix::ImageCreationType_pimpl ImageCreationType_p;
    ::mix::Host_pimpl Host_p;
    ::mix::ScanningSystemCapture_pimpl ScanningSystemCapture_p;
    ::mix::ScanningSystemHardware_pimpl ScanningSystemHardware_p;
    ::mix::ScannerModel_pimpl ScannerModel_p;
    ::mix::ScanningSystemSoftware_pimpl ScanningSystemSoftware_p;
    ::mix::ScannerCaptureSettings_pimpl ScannerCaptureSettings_p;
    ::mix::typeOfNonNegativeRealType_pimpl typeOfNonNegativeRealType_p;
    ::mix::PhysScanResolution_pimpl PhysScanResolution_p;
    ::mix::DigitalCameraCapture_pimpl DigitalCameraCapture_p;
    ::mix::CameraCaptureSettings_pimpl CameraCaptureSettings_p;
    ::mix::typeOfSubjectDistanceType_pimpl typeOfSubjectDistanceType_p;
    ::mix::typeOfMeteringModeType_pimpl typeOfMeteringModeType_p;
    ::mix::typeOfSceneIlluminantType_pimpl typeOfSceneIlluminantType_p;
    ::mix::typeOfFlashType_pimpl typeOfFlashType_p;
    ::mix::typeOfFlashReturnType_pimpl typeOfFlashReturnType_p;
    ::mix::typeOfBackLightType_pimpl typeOfBackLightType_p;
    ::mix::typeOfAutoFocusType_pimpl typeOfAutoFocusType_p;
    ::mix::PrintAspectRatio_pimpl PrintAspectRatio_p;
    ::mix::typeOfSensorType_pimpl typeOfSensorType_p;
    ::mix::typeOfDateTimeType_pimpl typeOfDateTimeType_p;
    ::mix::ImagingPerformanceAssessmentType_pimpl ImagingPerformanceAssessmentType_p;
    ::mix::SpatialMetrics_pimpl SpatialMetrics_p;
    ::mix::typeOfSamplingFrequencyPlaneType_pimpl typeOfSamplingFrequencyPlaneType_p;
    ::mix::typeOfSamplingFrequencyUnitType_pimpl typeOfSamplingFrequencyUnitType_p;
    ::mix::typeOfPositiveIntegerType_pimpl typeOfPositiveIntegerType_p;
    ::mix::Source_X_pimpl Source_X_p;
    ::mix::Source_Y_pimpl Source_Y_p;
    ::mix::Energetics_pimpl Energetics_p;
    ::mix::typeOfBitsPerSampleType_pimpl typeOfBitsPerSampleType_p;
    ::mix::typeOfSamplesPerPixelType_pimpl typeOfSamplesPerPixelType_p;
    ::mix::typeOfExtraSamplesType_pimpl typeOfExtraSamplesType_p;
    ::mix::Colormap_pimpl Colormap_p;
    ::mix::typeOfColormapType_pimpl typeOfColormapType_p;
    ::mix::GrayResponse_pimpl GrayResponse_p;
    ::mix::typeOfGrayResponseCurveType_pimpl typeOfGrayResponseCurveType_p;
    ::mix::typeOfGrayResponseUnitType_pimpl typeOfGrayResponseUnitType_p;
    ::mix::WhitePoint_pimpl WhitePoint_p;
    ::mix::typeOfCIExyType_pimpl typeOfCIExyType_p;
    ::mix::PrimaryChromaticities_pimpl PrimaryChromaticities_p;
    ::mix::TargetData_pimpl TargetData_p;
    ::mix::typeOfTargetTypeType_pimpl typeOfTargetTypeType_p;
    ::mix::TargetID_pimpl TargetID_p;
    ::mix::typeOfReferenceType_pimpl typeOfReferenceType_p;
    ::mix::ChangeHistoryType_pimpl ChangeHistoryType_p;
    ::mix::ImageProcessing_pimpl ImageProcessing_p;
    ::mix::ProcessingSoftware_pimpl ProcessingSoftware_p;
    ::mix::typeOfPreviousImageMetadataType_pimpl typeOfPreviousImageMetadataType_p;

    // Connect the parsers together.
    //
    BasicImageParametersType_p.parsers (Format_p,
                                        File_p,
                                        typeOfStringType_p);

    Format_p.parsers (typeOfFormatType_p,
                      typeOfByteOrderType_p,
                      Compression_p,
                      PhotometricInterpretation_p,
                      Segments_p,
                      typeOfPlanarConfigurationType_p);

    typeOfFormatType_p.parsers (any_simple_type_p);

    typeOfByteOrderType_p.parsers (any_simple_type_p);

    Compression_p.parsers (typeOfCompressionSchemeType_p,
                           typeOfCompressionLevelType_p);

    typeOfCompressionSchemeType_p.parsers (any_simple_type_p);

    typeOfCompressionLevelType_p.parsers (any_simple_type_p);

    PhotometricInterpretation_p.parsers (typeOfColorSpaceType_p,
                                         ICCProfile_p,
                                         typeOfYCbCrSubSamplingType_p,
                                         typeOfYCbCrPositioningType_p,
                                         typeOfYcbCrCoefficientsType_p,
                                         typeOfReferenceBlackWhiteType_p);

    typeOfColorSpaceType_p.parsers (any_simple_type_p);

    ICCProfile_p.parsers (typeOfStringType_p,
                          typeOfStringType_p);

    typeOfStringType_p.parsers (any_simple_type_p);

    typeOfYCbCrSubSamplingType_p.parsers (any_simple_type_p);

    typeOfYCbCrPositioningType_p.parsers (any_simple_type_p);

    typeOfYcbCrCoefficientsType_p.parsers (any_simple_type_p);

    typeOfReferenceBlackWhiteType_p.parsers (any_simple_type_p);

    Segments_p.parsers (typeOfSegmentTypeType_p,
                        typeOfStripOffsetsType_p,
                        typeOfRowsPerStripType_p,
                        typeOfStripByteCountsType_p,
                        typeOfTileWidthType_p,
                        typeOfTileLengthType_p,
                        typeOfTileOffsetsType_p,
                        typeOfTileByteCountsType_p);

    typeOfSegmentTypeType_p.parsers (any_simple_type_p);

    typeOfStripOffsetsType_p.parsers (any_simple_type_p);

    typeOfRowsPerStripType_p.parsers (any_simple_type_p);

    typeOfStripByteCountsType_p.parsers (any_simple_type_p);

    typeOfTileWidthType_p.parsers (any_simple_type_p);

    typeOfTileLengthType_p.parsers (any_simple_type_p);

    typeOfTileOffsetsType_p.parsers (any_simple_type_p);

    typeOfTileByteCountsType_p.parsers (any_simple_type_p);

    typeOfPlanarConfigurationType_p.parsers (any_simple_type_p);

    File_p.parsers (typeOfImageIdentifierType_p,
                    typeOfFileSizeType_p,
                    Checksum_p,
                    typeOfOrientationType_p,
                    typeOfDisplayOrientationType_p,
                    TargetedDisplayAR_p);

    typeOfImageIdentifierType_p.parsers (any_simple_type_p,
                                         any_simple_type_p);

    typeOfFileSizeType_p.parsers (any_simple_type_p);

    Checksum_p.parsers (typeOfChecksumMethodType_p,
                        typeOfChecksumValueType_p);

    typeOfChecksumMethodType_p.parsers (any_simple_type_p);

    typeOfChecksumValueType_p.parsers (any_simple_type_p);

    typeOfOrientationType_p.parsers (any_simple_type_p);

    typeOfDisplayOrientationType_p.parsers (any_simple_type_p);

    TargetedDisplayAR_p.parsers (typeOfXTargetedDisplayARType_p,
                                 typeOfYTargetedDisplayARType_p);

    typeOfXTargetedDisplayARType_p.parsers (any_simple_type_p);

    typeOfYTargetedDisplayARType_p.parsers (any_simple_type_p);

    ImageCreationType_p.parsers (typeOfStringType_p,
                                 typeOfStringType_p,
                                 typeOfStringType_p,
                                 Host_p,
                                 typeOfStringType_p,
                                 ScanningSystemCapture_p,
                                 DigitalCameraCapture_p,
                                 CameraCaptureSettings_p,
                                 typeOfSensorType_p,
                                 typeOfDateTimeType_p,
                                 typeOfStringType_p);

    Host_p.parsers (typeOfStringType_p,
                    typeOfStringType_p,
                    typeOfStringType_p);

    ScanningSystemCapture_p.parsers (ScanningSystemHardware_p,
                                     ScanningSystemSoftware_p,
                                     ScannerCaptureSettings_p);

    ScanningSystemHardware_p.parsers (typeOfStringType_p,
                                      ScannerModel_p);

    ScannerModel_p.parsers (typeOfStringType_p,
                            typeOfStringType_p,
                            typeOfStringType_p);

    ScanningSystemSoftware_p.parsers (typeOfStringType_p,
                                      typeOfStringType_p);

    ScannerCaptureSettings_p.parsers (typeOfNonNegativeRealType_p,
                                      PhysScanResolution_p);

    typeOfNonNegativeRealType_p.parsers (any_simple_type_p);

    PhysScanResolution_p.parsers (typeOfNonNegativeRealType_p,
                                  typeOfNonNegativeRealType_p);

    DigitalCameraCapture_p.parsers (typeOfStringType_p,
                                    typeOfStringType_p);

    CameraCaptureSettings_p.parsers (typeOfNonNegativeRealType_p,
                                     typeOfNonNegativeRealType_p,
                                     typeOfNonNegativeRealType_p,
                                     typeOfNonNegativeRealType_p,
                                     typeOfSubjectDistanceType_p,
                                     typeOfMeteringModeType_p,
                                     typeOfSceneIlluminantType_p,
                                     typeOfNonNegativeRealType_p,
                                     typeOfNonNegativeRealType_p,
                                     typeOfFlashType_p,
                                     typeOfNonNegativeRealType_p,
                                     typeOfFlashReturnType_p,
                                     typeOfBackLightType_p,
                                     typeOfNonNegativeRealType_p,
                                     typeOfAutoFocusType_p,
                                     PrintAspectRatio_p);

    typeOfSubjectDistanceType_p.parsers (any_simple_type_p,
                                         any_simple_type_p,
                                         any_simple_type_p);

    typeOfMeteringModeType_p.parsers (any_simple_type_p);

    typeOfSceneIlluminantType_p.parsers (any_simple_type_p);

    typeOfFlashType_p.parsers (any_simple_type_p);

    typeOfFlashReturnType_p.parsers (any_simple_type_p);

    typeOfBackLightType_p.parsers (any_simple_type_p);

    typeOfAutoFocusType_p.parsers (any_simple_type_p);

    PrintAspectRatio_p.parsers (typeOfNonNegativeRealType_p,
                                typeOfNonNegativeRealType_p);

    typeOfSensorType_p.parsers (any_simple_type_p);

    typeOfDateTimeType_p.parsers (any_simple_type_p);

    ImagingPerformanceAssessmentType_p.parsers (SpatialMetrics_p,
                                                Energetics_p,
                                                TargetData_p);

    SpatialMetrics_p.parsers (typeOfSamplingFrequencyPlaneType_p,
                              typeOfSamplingFrequencyUnitType_p,
                              typeOfPositiveIntegerType_p,
                              typeOfPositiveIntegerType_p,
                              typeOfPositiveIntegerType_p,
                              typeOfPositiveIntegerType_p,
                              Source_X_p,
                              Source_Y_p);

    typeOfSamplingFrequencyPlaneType_p.parsers (any_simple_type_p);

    typeOfSamplingFrequencyUnitType_p.parsers (any_simple_type_p);

    typeOfPositiveIntegerType_p.parsers (any_simple_type_p);

    Source_X_p.parsers (typeOfNonNegativeRealType_p,
                        typeOfStringType_p);

    Source_Y_p.parsers (typeOfNonNegativeRealType_p,
                        typeOfStringType_p);

    Energetics_p.parsers (typeOfBitsPerSampleType_p,
                          typeOfSamplesPerPixelType_p,
                          typeOfExtraSamplesType_p,
                          Colormap_p,
                          GrayResponse_p,
                          WhitePoint_p,
                          PrimaryChromaticities_p);

    typeOfBitsPerSampleType_p.parsers (any_simple_type_p);

    typeOfSamplesPerPixelType_p.parsers (any_simple_type_p);

    typeOfExtraSamplesType_p.parsers (any_simple_type_p);

    Colormap_p.parsers (typeOfColormapType_p,
                        typeOfColormapType_p,
                        typeOfColormapType_p,
                        typeOfColormapType_p);

    typeOfColormapType_p.parsers (any_simple_type_p);

    GrayResponse_p.parsers (typeOfGrayResponseCurveType_p,
                            typeOfGrayResponseUnitType_p);

    typeOfGrayResponseCurveType_p.parsers (any_simple_type_p);

    typeOfGrayResponseUnitType_p.parsers (any_simple_type_p);

    WhitePoint_p.parsers (typeOfCIExyType_p,
                          typeOfCIExyType_p);

    typeOfCIExyType_p.parsers (any_simple_type_p);

    PrimaryChromaticities_p.parsers (typeOfCIExyType_p,
                                     typeOfCIExyType_p,
                                     typeOfCIExyType_p,
                                     typeOfCIExyType_p,
                                     typeOfCIExyType_p,
                                     typeOfCIExyType_p);

    TargetData_p.parsers (typeOfTargetTypeType_p,
                          TargetID_p,
                          typeOfReferenceType_p,
                          typeOfReferenceType_p,
                          typeOfReferenceType_p);

    typeOfTargetTypeType_p.parsers (any_simple_type_p);

    TargetID_p.parsers (typeOfStringType_p,
                        typeOfStringType_p,
                        typeOfStringType_p,
                        typeOfStringType_p);

    typeOfReferenceType_p.parsers (any_simple_type_p);

    ChangeHistoryType_p.parsers (ImageProcessing_p,
                                 typeOfPreviousImageMetadataType_p);

    ImageProcessing_p.parsers (typeOfDateTimeType_p,
                               typeOfReferenceType_p,
                               typeOfStringType_p,
                               ProcessingSoftware_p,
                               typeOfStringType_p);

    ProcessingSoftware_p.parsers (typeOfStringType_p,
                                  typeOfStringType_p);

    // Parse the XML document.
    //
    ::xml_schema::document doc_p (
      mix_p,
      "http://www.loc.gov/mix/",
      "mix");

    mix_p.pre ();
    doc_p.parse (data.c_str(), data.size(), true);
    mix_p.post_mix ();
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

