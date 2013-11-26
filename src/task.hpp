#ifndef DRUDGERY_TASK
#define DRUDGERY_TASK

#include <string>

#include "date.hpp"

class task
{
	public:
		task(const date& due_date=date(1,1,1970),const std::string& info="",const std::string& name="",const unsigned int time_estimate=0,
			const unsigned int time_working=0);

		date due_date;
		std::string info;
		std::string name;
		unsigned int time_estimate;
		unsigned int time_working;
};

#endif