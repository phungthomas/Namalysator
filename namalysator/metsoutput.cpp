#include <stdio.h>
#include <stdlib.h>
#include "blockcutter.h"
#include "structgui.h"
#include "metsoutput.h"


bool headcutter::open_document(const std::string &filename)
{
	if (!ow.open_document(filename)) {
		return false;
	}
	ow.open_sheet("Headings");
	ow.open_row();
	ow.add_text("Title");
	ow.add_text("Countcaracter");
	ow.add_text("Error");
	ow.add_text("Image");
	ow.close_row();
	sequence_number = 1;
	return true;
}

void headcutter::close_document()
{
	ow.close_sheet();
	ow.close_document();
}


void headcutter::cut_headings(std::string currentTiff, std::string currentAlto, Block block, std::string title)
{
	block_cutter cutter;
	std::map<std::string, std::vector<char> > image_data;
	const float factor = 0.5;
	char s[256];
	sprintf(s, "%010d.jpg", sequence_number);
	++sequence_number;

	alto_rectangle ar(block.vpos,block.hpos,block.width,block.height);
	ow.open_row(int((ar.height * factor * 2.54 / 72 + 0.6f) * 1000.0));
	ow.add_text(title);
	ow.add_number(title.size());
	ow.add_text("");
	ow.add_picture_link(s, float(ar.width * factor * 2.54 / 72), float(ar.height * factor * 2.54 / 72));
	ow.close_row();
	cutter.add(ar,s);
	cutter.cut_all(currentTiff, factor, &image_data);
	for (std::map<std::string, std::vector<char> >::iterator im_it = image_data.begin(); im_it != image_data.end(); ++im_it) {
		ow.store_picture(im_it->first, im_it->second);
	}
}


void cut_headings(bool only_level1, const std::string &filename, const std::string &prefix, int permille, const std::string &metsfile)
{
/*
	g_err.begin_group(metsfile);
	g_err.begin_group("cut_headings");
	const float factor = 0.5;
	char s[256];
	std::map<std::string, block_cutter>	cutter;
	FILE *fp = fopen(filename.c_str(), "a");
	
	for (size_t i = 0; i < data->article_tree.size(); ++i) {
		if (!only_level1 || data->article_tree[i].second == 2) {
			// Found article on the correct level
			std::map<std::string, metsinfo::article_sequence>::iterator it = data->proper_articles.find(data->article_tree[i].first);
			// determine whether we cut it or not
			if (rand() % 1000 < permille) {
				if (it != data->proper_articles.end()) {
					// Now go through the article blocks to find their pages and whether they are in headings
					const metsinfo::article_sequence &sequence = it->second;
					bool first_heading_found = false;
					std::set<alto_rectangle, altorect_sort> already_cut;
					for (size_t o = 0; o < sequence.size(); ++o) {
						if (sequence[o].type == "HEADING") {
							g_err.add_message(err_info, "Cutting ALTO BLOCK", sequence[o].alto + " " + sequence[o].block, true);
							const alto_rectangle &ar = data->alto[sequence[o].alto][sequence[o].block];
							if (already_cut.find(ar) == already_cut.end()) {
								already_cut.insert(ar);
								sprintf(s, "%02d-%02d", i, o);
								fprintf(fp, "<tr height=\"%d\">\n\t<td>%s</td>\n", max(int(ar.height * factor) + 4, 24), data->article_names[data->article_tree[i].first].c_str());
								if (!first_heading_found) {
									first_heading_found = true;
									fprintf(fp, "\t<td>%d</td>\n", data->article_names[data->article_tree[i].first].length());
								} else {
									fprintf(fp, "\t<td>&nbsp;</td>\n");
								}
								fprintf(fp, "\t<td>&nbsp;</td>\n");
								fprintf(fp, "\t<td width=\"%d\"><img src=\"file://%s%s.jpg\" width=\"%d\" height=\"%d\"></td>\n", int(ar.width * factor), prefix.c_str(), s, int(ar.width * factor), int(ar.height * factor));
								fprintf(fp, "\t<td>%s</td>\n", metsfile.c_str());
								fprintf(fp, "</tr>\n");
								fclose(fp);
								fp = fopen(filename.c_str(), "a");
								cutter[sequence[o].alto].add(ar, prefix + std::string(s) + ".jpg");
							}
						}
					}
				} else {
					if (data->all_articles.find(data->article_tree[i].first) == data->all_articles.end()) {
						g_err.add_message(err_major, "Article has no blocks", data->article_tree[i].first, true);
					} else {
						if (data->article_names.find(data->article_tree[i].first) == data->article_names.end()) {
							g_err.add_message(err_minor, 
								"Could not find heading of article", 
								data->article_tree[i].first + 
								" starting on page " + 
								(data->all_articles[data->article_tree[i].first].begin())->alto +
								" and it has no title", true); 
						} else {
							g_err.add_message(err_info, 
								"Could not find heading of article", 
								data->article_tree[i].first + 
								" starting on page " + 
								(data->all_articles[data->article_tree[i].first].begin())->alto +
								" with title " +
								data->article_names[data->article_tree[i].first], true); 
						}
					}
				}
			}
		}
	}
	fclose(fp);
	for (std::map<std::string, block_cutter>::iterator it = cutter.begin(); it != cutter.end(); ++it) {
		const std::string &tiff = data->alto2tif[it->first].second;
		it->second.cut_all(tiff, factor);
	}
	g_err.end_group();
	g_err.end_group();
}

void cut_article(metsinfo *data, const std::string &prefix, const std::string &articleid)
{
	/*const float factor = 0.5;
	std::map<std::string, block_cutter>	cutter;
	*/
}

bool ismets(const std::string &fname)
{
	// Extension has to be .xml
	if (fname.length() < 4) {
		return false;
	}
	if (fname.substr(fname.length() - 4) != ".xml") {
		return false;
	}
	FILE *fp = fopen(fname.c_str(), "r");
	char buf[100];
	int nread = fread(buf, 1, 100, fp);
	fclose(fp);
	// The file should begin with <?xml and the second line should begin with <mets
	if (nread < 100) {
		return false;
	}
	if (strncmp(buf, "<?xml", 5) != 0) {
		return false;
	}
	int i = 0;
	while (i < 100 && buf[i] != '\n') {
		++i;
	}
	++i;
	if (strncmp(buf + i, "<mets", 5) != 0) {
		return false;
	}
	return true;
}


