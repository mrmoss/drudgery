#include "msl/2d.hpp"

#include "task_list.hpp"

#include "task_ui.hpp"
#include <iostream>
#include <string>

class task_list_ui
{
	public:
		task_list_ui(const double x=0,const double y=0):x(x),y(y),display_width(0),display_height(0),visible(true)
		{
			list_ui.width=480;
		}

		void loop(const double dt)
		{
			list.loop();

			if(visible)
			{
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
		}

		void draw()
		{
			if(visible)
				list_ui.draw();
		}

		double x;
		double y;
		double display_width;
		double display_height;
		bool visible;

		task_list list;
		msl::list list_ui;
};

class menu_bar
{
	public:
		menu_bar(const double x=0,const double y=0):x(x),y(y),display_width(0),display_height(0),
			escape("Exit"),add_task("Add Task")
		{
			escape.padding=add_task.padding=archive_task.padding=10;

			h0.widgets.push_back(&escape);
			h0.widgets.push_back(&add_task);
			h0.widgets.push_back(&archive_task);
			h0.background_color_to.a=h0.background_color_from.a=h0.outline_color.a=0;

			v0.widgets.push_back(&h0);
		}

		void loop(const double dt,task_list_ui& active,task_list_ui& archive)
		{
			v0.y=y-v0.display_height/2.0;
			v0.loop(dt);
			display_width=v0.display_width;
			display_height=v0.display_height;

			if(escape.pressed)
				exit(0);

			if(active.visible)
			{
				if((int)active.list_ui.value>=0)
					archive_task.disabled=false;
				else
					archive_task.disabled=true;

				add_task.disabled=false;
				archive_task.value="Archive Task";

				if(add_task.pressed&&active.visible)
				{
					task new_task(date(18,12,2013),"","New Task",0,0);

					if((int)active.list_ui.value>=0)
						active.list.insert(new_task,active.list_ui.value);
					else
						active.list.add(new_task);
				}

				if(archive_task.pressed&&(int)active.list_ui.value>=0)
				{
					if(active.list[active.list_ui.value].time_working>0)
						archive.list.add(active.list[active.list_ui.value]);

					active.list.remove(active.list_ui.value);
				}
			}
			else if(archive.visible)
			{
				if((int)archive.list_ui.value>=0)
					archive_task.disabled=false;
				else
					archive_task.disabled=true;

				add_task.disabled=true;
				archive_task.value="Delete Task";

				if(archive_task.pressed&&(int)archive.list_ui.value>=0)
					archive.list.remove(archive.list_ui.value);
			}
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
		msl::button archive_task;
		msl::hdock h0;
		msl::vdock v0;
};

menu_bar menu(0,0);
task_list_ui active(0,0);
task_list_ui archive(0,0);

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

	active.list.add(task(date(18,12,2013),"I need to add tasks to Drudgery.","My First Task",0,0));
	archive.visible=false;
	active.visible=!archive.visible;
}

void loop(const double dt)
{
	menu.y=msl::window_height/2.0;
	active.y=msl::window_height/2.0-menu.display_height;
	archive.y=msl::window_height/2.0-menu.display_height;

	if(msl::input_check_pressed(kb_f1))
	{
		archive.visible=!archive.visible;
		active.visible=!archive.visible;
	}

	if(active.visible)
	{
		task_viewer.working_on.disabled=false;
		task_viewer.modify.disabled=false;

		task_viewer.y=msl::window_height/2.0-menu.display_height-active.display_height-task_viewer.display_height/2.0;
	}
	else if(archive.visible)
	{
		task_viewer.working_on.value=false;
		task_viewer.modify.value=false;
		task_viewer.working_on.disabled=true;
		task_viewer.modify.disabled=true;

		task_viewer.y=msl::window_height/2.0-menu.display_height-archive.display_height-task_viewer.display_height/2.0;
	}

	menu.loop(dt,active,archive);

	active.loop(dt);
	archive.loop(dt);

	active.list_ui.disabled=task_viewer.modify.value;

	if(active.visible&&(int)active.list_ui.value>=0)
		task_viewer.loop(dt,active.list[active.list_ui.value]);

	if(archive.visible&&(int)archive.list_ui.value>=0)
		task_viewer.loop(dt,archive.list[archive.list_ui.value]);
}

void draw()
{
	menu.draw();

	unsigned int old_index=active.list_ui.value;
	active.draw();
	unsigned int new_index=active.list_ui.value;

	archive.draw();

	if(active.visible&&(int)active.list_ui.value>=0)
	{
		if(old_index!=new_index&&(int)old_index>=0)
			task_viewer.working_on.value=active.list[active.list_ui.value].working_on;

		task_viewer.draw();
	}

	if(archive.visible&&(int)archive.list_ui.value>=0)
	{
		task_viewer.draw();
	}
}