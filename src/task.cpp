#include "task.hpp"

#include "msl/time_util.hpp"

task::task(const date& due_date,const std::string& info,const std::string& name,const unsigned int time_estimate,
	const unsigned int time_working):due_date(due_date),info(info),name(name),time_estimate(time_estimate),
	time_working(time_working),working_on(false),old_time_(0)
{}

bool task::operator==(const task& rhs) const
{
	return (due_date==rhs.due_date&&info==rhs.info&&name==rhs.name&&time_estimate==rhs.time_estimate&&time_working==rhs.time_working);
}

bool task::operator!=(const task& rhs) const
{
	return !(*this==rhs);
}

void task::loop()
{
	if(working_on)
	{
		if(msl::millis()>=old_time_+1000)
		{
			++time_working;
			old_time_=msl::millis();
		}
	}
	else
	{
		old_time_=msl::millis();
	}
}