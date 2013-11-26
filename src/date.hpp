#ifndef DRUDGERY_DATE
#define DRUDGERY_DATE

class date
{
	public:
		date(const int day,const int month,const int year);

		bool operator==(const date& rhs) const;
		bool operator!=(const date& rhs) const;

		int day;
		int month;
		int year;
};

#endif