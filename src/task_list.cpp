#include "task_list.hpp"

#include "date.hpp"
#include "msl/file_util.hpp"
#include "msl/json.hpp"
#include "msl/string_util.hpp"

void task_list::add(const task& item)
{
	list_.push_back(item);
}

void task_list::remove(const unsigned int index)
{
	list_.erase(list_.begin()+index);
}

unsigned int task_list::size() const
{
	return list_.size();
}

task& task_list::operator[](const unsigned int index)
{
	return list_[index];
}

const task task_list::operator[](const unsigned int index) const
{
	return list_[index];
}

void task_list::insert(const task& item,const unsigned int index)
{
	list_.insert(list_.begin()+index,item);
}

void task_list::loop()
{
	for(unsigned int ii=0;ii<list_.size();++ii)
		list_[ii].loop();
}

bool task_list::save(const std::string& filename) const
{
	msl::json save_json;

	save_json.set("size",list_.size());

	for(unsigned int ii=0;ii<list_.size();++ii)
	{
		msl::json task_json;
		task_json.set("due_day",list_[ii].due_date.day);
		task_json.set("due_month",list_[ii].due_date.month);
		task_json.set("due_year",list_[ii].due_date.year);
		task_json.set("info",list_[ii].info);
		task_json.set("name",list_[ii].name);
		task_json.set("time_estimate",list_[ii].time_estimate);
		task_json.set("time_working",list_[ii].time_working);

		save_json.set(msl::to_string(ii),task_json);
	}

	return msl::string_to_file(save_json.str(),filename);
}

bool task_list::load(const std::string& filename)
{
	std::string load_json_string;

	if(msl::file_to_string(filename,load_json_string))
	{
		msl::json load_json(load_json_string);

		std::vector<task> temp_list;

		for(unsigned int ii=0;ii<(unsigned int)msl::to_int(load_json.get("size"));++ii)
		{
			msl::json task_json=load_json.get(msl::to_string(ii));

			date temp_date(msl::to_int(task_json.get("due_day")),msl::to_int(task_json.get("due_month")),msl::to_int(task_json.get("due_year")));

			task temp_task;
				temp_task.due_date=temp_date;
				temp_task.info=task_json.get("info");
				temp_task.name=task_json.get("name");
				temp_task.time_estimate=msl::to_int(task_json.get("time_estimate"));
				temp_task.time_working=msl::to_int(task_json.get("time_working"));


			temp_list.push_back(temp_task);
		}

		list_=temp_list;

		return true;
	}

	return false;
}

bool task_list::operator==(const task_list& rhs) const
{
	if(size()!=rhs.size())
		return false;

	bool match=true;

	for(unsigned int ii=0;ii<size();++ii)
	{
		if(list_[ii]!=rhs[ii])
		{
			match=false;
			break;
		}
	}

	return match;
}

bool task_list::operator!=(const task_list& rhs) const
{
	return !(*this==rhs);
}