#ifndef ODSTEMPLATE_H_
#define ODSTEMPLATE_H_

extern const char ods_mimetype[];
extern const char ods_meta[];
extern const char ods_manifest_1[];
// Need to insert the filename of the JPG file (without a path)
extern const char ods_manifest_pic[];
extern const char ods_manifest_2[];
extern const char ods_content_1[];
// Need to insert (i_styleNumber, f_Height) with f_Height in cm
extern const char ods_content_row_style[];
extern const char ods_content_2[];
// Need to insert the name of the sheet
extern const char ods_content_sheet_open[];
extern const char ods_content_row_open[];
// Need to insert row style (integer)
extern const char ods_content_row_open_style[];
// Need to insert the text to be placed inside (with xml escapes for ", < and >)
extern const char ods_content_cell_text[];
// Need to insert (f_value, f_value) i.e. the value twice
extern const char ods_content_cell_number[];
// Need to insert (i_counter, f_width, f_height, s_picfile) where width and height are in cm (72 dpi monitor)
extern const char ods_content_cell_image[];
extern const char ods_content_row_close[];
extern const char ods_content_sheet_close[];
extern const char ods_content_3[];

#endif // ODSTEMPLATE_H_
