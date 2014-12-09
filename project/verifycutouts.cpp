#include "verifycutouts.h"

void verifycutouts(datafactory *df, errorHandler *h, std::string &fileName)
{
	bool foundOne = false;
	h->begin("Verify: cut-out references in mix");
	datafactory_set<AmdSec> dfAmdSec = df->get_set<AmdSec>();
	datafactory_set<File_Group> dfFileGrp = df->get_set<File_Group>();
	for (datafactory_set<AmdSec>::iterator it = dfAmdSec.begin(); it != dfAmdSec.end(); ++it) {
		if (it->sourceData.length()) {
			// Look for the identifier in the fileGrp
			foundOne = false;
			for (datafactory_set<File_Group>::iterator it2 = dfFileGrp.begin(); it2 != dfFileGrp.end(); ++it2) {
				for (std::vector<Type_File>::const_iterator itv = it2->vect.begin(); itv != it2->vect.end(); itv++) {
					if (itv->id == it->sourceData) {
						foundOne = true;
					}
				}
			}
			if (!foundOne) {
				h->getError(cat_cutoutoriginal, "METS", "MIX", it->amdSecId + " references cut-out " + it->sourceData + " which is not the ID of an Image",fileName, "SourceData>" + it->sourceData);
			}
		}
	}
}