#include "msl/2d.hpp"

#include "task_list.hpp"

#include "task_ui.hpp"
#include <iostream>

class task_list_ui
{
	public:
		void cleanup()
		{
			for(unsigned int ii=0;ii<ui_list.size();++ii)
				delete ui_list[ii];

			ui_list.clear();
		}

		void loop(const double dt)
		{
			list.loop();

			while(ui_list.size()<list.size())
				ui_list.push_back(new task_ui(0,0));

			while(ui_list.size()>list.size()&&ui_list.size()>0)
			{
				delete ui_list[ui_list.size()-1];
				ui_list.pop_back();
			}

			for(unsigned int ii=0;ii<list.size();++ii)
			{
				ui_list[ii]->y=-(ii*160.0);
				ui_list[ii]->loop(dt,list[ii]);
			}
		}

		void draw()
		{
			for(unsigned int ii=0;ii<ui_list.size();++ii)
				ui_list[ii]->draw();
		}

		task_list list;
		std::vector<task_ui*> ui_list;
};

task_list_ui tasks;

int main()
{
	msl::start_2d("Drudgery",640,480,false);
	return 0;
}

void setup()
{
	msl::set_text_font("Ubuntu-B.ttf");
	msl::set_text_size(12);

	tasks.list.add(task(date(12,1,1980),"This is my task description.","Task title",12,95));
	tasks.list.add(task(date(11,23,2001),"This is my task description2.","Task title2",13,10));
}

void loop(const double dt)
{
	if(msl::input_check_pressed(kb_escape))
		exit(0);

	if(msl::input_check_pressed(kb_space))
		tasks.list.add(task(date(12,1,1980),"This is my task description.","Task title",12,95));

	tasks.loop(dt);
}

void draw()
{
	tasks.draw();
}