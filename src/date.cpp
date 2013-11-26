#include "date.hpp"

date::date(const int day,const int month,const int year):day(day),month(month),year(year)
{}

bool date::operator==(const date& rhs) const
{
	return (day==rhs.day&&month==rhs.month&&year==rhs.year);
}

bool date::operator!=(const date& rhs) const
{
	return !(*this==rhs);
}