#include "msl/2d.hpp"

#include "task_list.hpp"

#include "task_ui.hpp"
#include <iostream>
#include <string>

class menu_bar
{
	public:
		menu_bar(const double x=0,const double y=0):x(x),y(y),display_width(0),display_height(0),escape("Exit"),add_task("Add")
		{
			escape.padding=add_task.padding=10;

			h0.widgets.push_back(&escape);
			h0.widgets.push_back(&add_task);
			h0.background_color_to.a=h0.outline_color.a=0;

			v0.widgets.push_back(&h0);
		}

		void loop(const double dt)
		{
			v0.y=y-v0.display_height/2.0;
			v0.loop(dt);
			display_width=v0.display_width;
			display_height=v0.display_height;

			if(escape.pressed)
				exit(0);
		}

		void draw()
		{
			v0.draw();
		}

		double x;
		double y;
		double display_width;
		double display_height;

		msl::button escape;
		msl::button add_task;
		msl::hdock h0;
		msl::vdock v0;
};

class task_list_ui
{
	public:
		task_list_ui(const double x=0,const double y=0):x(x),y(y),display_width(0),display_height(0)
		{
			list_ui.width=480;
		}

		void loop(const double dt)
		{
			list.loop();

			list_ui.y=y-list_ui.display_height/2.0;
			display_width=list_ui.display_width;
			display_height=list_ui.display_height;

			std::vector<std::string> temp;

			for(unsigned int ii=0;ii<list.size();++ii)
				temp.push_back(list[ii].name);

			list_ui.options=temp;
			list_ui.loop(dt);

			if(list_ui.value>=list.size())
				list_ui.value=-1;
		}

		void draw()
		{
			list_ui.draw();
		}

		double x;
		double y;
		double display_width;
		double display_height;

		task_list list;
		msl::list list_ui;
};

menu_bar menu(0,0);
task_list_ui tasks(0,0);

task_ui task_viewer(0,0);

int main()
{
	msl::start_2d("Drudgery",640,480,false);
	return 0;
}

void setup()
{
	msl::set_text_font("Ubuntu-B.ttf");
	msl::set_text_size(12);

	tasks.list.add(task(date(18,12,2013),"I need to add tasks to Drudgery.","My First Task",0,0));
}

void loop(const double dt)
{
	menu.y=msl::window_height/2.0;
	tasks.y=msl::window_height/2.0-menu.display_height;
	task_viewer.y=msl::window_height/2.0-menu.display_height-tasks.display_height-task_viewer.display_height/2.0;

	menu.loop(dt);

	if(menu.add_task.pressed)
		tasks.list.add(task(date(18,12,2013),"","New Task",0,0));

	if(msl::input_check_pressed(kb_f1)&& tasks.list.size()>0)
		tasks.list.remove(tasks.list.size()-1);

	tasks.loop(dt);

	tasks.list_ui.disabled=task_viewer.modify.value;

	if((int)tasks.list_ui.value>=0)
		task_viewer.loop(dt,tasks.list[tasks.list_ui.value]);
}

void draw()
{
	menu.draw();

	unsigned int old_index=tasks.list_ui.value;
	tasks.draw();
	unsigned int new_index=tasks.list_ui.value;

	if((int)tasks.list_ui.value>=0)
	{
		if(old_index!=new_index&&(int)old_index>=0)
			task_viewer.working_on.value=tasks.list[tasks.list_ui.value].working_on;

		task_viewer.draw();
	}
}