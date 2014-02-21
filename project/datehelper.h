#ifndef DATEHELPER_H_
#define DATEHELPER_H_

#include <string>

inline int to_julian(int year, int month, int day)
{
	return day - 32075
	  + 1461 * ( year + 4800 - ( 14 - month ) / 12 ) / 4
	  + 367 * ( month - 2 + ( ( 14 - month ) / 12 ) * 12 ) / 12
	  - 3 * ( ( year + 4900 - ( 14 - month ) / 12 ) / 100 ) / 4;
}

inline void from_julian(int julian_day, int &year, int &month, int &day)
{
	int julian_tmp;
	
	julian_tmp = julian_day - 1721119;
	year = (4 * julian_tmp - 1) / 146097;
	julian_tmp = 4 * julian_tmp - 1 - 146097 * year;
	day = julian_tmp/4;
	julian_tmp = (4 * day + 3)/1461;
	day = 4 * day + 3 - 1461 * julian_tmp;
	day = (day + 4)/4;
	month = (5 * day - 3) / 153;
	day = 5 * day - 3 - 153 * month;
	day = (day + 5) / 5;
	year = 100 * year + julian_tmp;
	if (month < 10) {
		month += 3;
	} else {
		month -= 9;
		++year;
	}
}

inline int from_julian_to_day(int julian_day)
{
	int julian_tmp;
	
	julian_tmp = julian_day - 1721119;
	int year = (4 * julian_tmp - 1) / 146097;
	julian_tmp = 4 * julian_tmp - 1 - 146097 * year;
	int day = julian_tmp/4;
	julian_tmp = (4 * day + 3)/1461;
	day = 4 * day + 3 - 1461 * julian_tmp;
	day = (day + 4)/4;
	int month = (5 * day - 3) / 153;
	day = 5 * day - 3 - 153 * month;
	day = (day + 5) / 5;
	return day;
}

bool convert_date(const std::string &s, const std::string &encoding, int &year, int &month, int &day);

#endif // DATEHELPER_H_
