#include "datehelper.h"
#include <vector>

int parse_numbers(const std::string &s, std::vector<int> &res)
{
	res.clear();
	size_t i = 0, len = s.length();
	while (i < len) {
		if (s[i] >= '0' && s[i] <= '9') {
			int v = 0;
			while (i < len && s[i] >= '0' && s[i] <= '9') {
				v *= 10;
				v += s[i] - '0';
				++i;
			}
			res.push_back(v);
		} else {
			while (i < len && (s[i] < '0' || s[i] > '9')) {
				++i;
			}
		}
	}
	return res.size();
}
bool convert_date(const std::string &s, const std::string &encoding, int &year, int &month, int &day)
{
	if (encoding == "w3cdtf") 
	{
		size_t i = 0;
		year = 0; month = 0; day = 0;
		while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
			year *= 10;
			year += s[i] - '0';
			++i;
		}
		++i;
		while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
			month *= 10;
			month += s[i] - '0';
			++i;
		}
		++i;
		while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
			day *= 10;
			day += s[i] - '0';
			++i;
		}
		return true;
	} else {
		// try to figure it out on our own, assume YYYY MM DD with any kind of spacing characters
		// or it can be DD MM YYYY with any spacing, but never MM DD YYYY or YY with two digits
		std::vector<int> v;
		if (parse_numbers(s, v) >= 3) {
			if (v[0] > 1000) {
				// Assume YYYY MM DD
				year = v[0];
				month = v[1];
				day = v[2];
				return true;
			} else if (v[2] > 1000) {
				// Assume DD MM YYYY
				day = v[0];
				month = v[1];
				year = v[2];
				return true;
			}
		}
	}
	return false;
}