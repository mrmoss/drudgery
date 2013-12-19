#include "msl/2d.hpp"

#include "task_list.hpp"

#include "task_ui.hpp"
#include <iostream>
#include <string>

class task_list_ui
{
	public:
		task_list_ui(const double x=0,const double y=0):x(x),y(y),display_width(0),display_height(0),
			visible(true),needs_saving(false)
		{
			list_ui.width=480;
		}

		void loop(const double dt)
		{
			task_list temp(list);

			list.loop();

			if(list!=temp)
				needs_saving=true;

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
		bool needs_saving;

		task_list list;
		msl::list list_ui;
};

class menu_bar
{
	public:
		menu_bar(const double x=0,const double y=0):x(x),y(y),display_width(0),display_height(0),loaded_active(false),
			escape("Exit"),active_list_view("Active List"),archive_list_view("Archive List"),move_top("Move to Top"),
			move_down("Move Down"),move_up("Move Up")
		{
			escape.padding=add_task.padding=archive_task.padding=active_list_view.padding=archive_list_view.padding=
				move_top.padding=move_down.padding=move_up.padding=10;

			add_task.width=archive_task.width=active_list_view.width=archive_list_view.width=move_top.width=96;

			h0.widgets.push_back(&escape);
			h0.widgets.push_back(&add_task);
			h0.widgets.push_back(&archive_task);
			h0.widgets.push_back(&active_list_view);
			h0.widgets.push_back(&archive_list_view);
			h0.widgets.push_back(&move_top);
			h0.widgets.push_back(&move_down);
			h0.widgets.push_back(&move_up);
			h0.background_color_to.a=h0.background_color_from.a=h0.outline_color.a=0;

			v0.widgets.push_back(&h0);
		}

		void setup(task_list_ui& active,task_list_ui& archive)
		{
			loaded_active=active.list.load("active.bak");
			archive.list.load("archive.bak");
		}

		void loop(const double dt,task_list_ui& active,task_list_ui& archive,task_ui& task_viewer)
		{
			move_top.disabled=true;

			bool save_active=false;
			bool save_archive=false;

			if(active.needs_saving)
			{
				save_active=true;
				active.needs_saving=false;
			}

			if(archive.needs_saving)
			{
				save_archive=true;
				archive.needs_saving=false;
			}

			if(active.visible&&(int)active.list_ui.value>0&&!task_viewer.modify.value)
				move_top.disabled=false;

			v0.loop(dt);

			v0.y=y-v0.display_height/2.0;
			display_width=v0.display_width;
			display_height=v0.display_height;

			if(active_list_view.pressed&&!task_viewer.modify.value)
			{
				active.visible=true;
				archive.visible=false;

				if((int)active.list_ui.value>=0)
					task_viewer.working_on.value=active.list[active.list_ui.value].working_on;
				else
					task_viewer.working_on.value=false;
			}

			if(archive_list_view.pressed)
			{
				active.visible=false;
				archive.visible=true;
			}

			if(active.visible)
				active_list_view.down=true;

			if(archive.visible)
				archive_list_view.down=true;

			archive_list_view.disabled=task_viewer.modify.value;

			if(escape.pressed)
				exit(0);

			if(active.visible)
			{
				move_down.disabled=true;
				move_up.disabled=true;

				if((int)active.list_ui.value>0&&!task_viewer.modify.value)
					move_up.disabled=false;

				if((int)active.list_ui.value<(int)active.list.size()-1&&!task_viewer.modify.value)
					move_down.disabled=false;

				if(move_up.pressed&&active.list_ui.value-1>=0&&active.list.size()>1)
				{
					task temp=active.list[active.list_ui.value];
					active.list[active.list_ui.value]=active.list[active.list_ui.value-1];
					active.list[active.list_ui.value-1]=temp;
					--active.list_ui.value;

					save_active=true;
				}

				if(move_down.pressed&&active.list_ui.value+1<active.list.size()&&active.list.size()>1)
				{
					task temp=active.list[active.list_ui.value];
					active.list[active.list_ui.value]=active.list[active.list_ui.value+1];
					active.list[active.list_ui.value+1]=temp;
					++active.list_ui.value;

					save_active=true;
				}

				if((int)active.list_ui.value>=0)
					archive_task.disabled=false;
				else
					archive_task.disabled=true;

				add_task.disabled=false;
				add_task.value="Create Task";
				archive_task.value="Archive Task";

				if((int)active.list_ui.value>=0&&active.list[active.list_ui.value].time_working==0)
					archive_task.value="Delete Task";

				if(task_viewer.modify.value)
				{
					add_task.disabled=true;
					archive_task.disabled=true;
				}

				if(task_viewer.modify.pressed)
					save_active=true;

				if(add_task.pressed)
				{
					task new_task(date(18,12,2013),"","New Task",0,0);

					if((int)active.list_ui.value>=0)
					{
						active.list.insert(new_task,active.list_ui.value);
						task_viewer.working_on.value=false;
					}
					else
					{
						active.list.add(new_task);
					}

					save_active=true;
				}

				if(archive_task.pressed&&(int)active.list_ui.value>=0)
				{
					if(active.list[active.list_ui.value].time_working>0)
					{
						archive.list.add(active.list[active.list_ui.value]);

						save_archive=true;
					}

					active.list.remove(active.list_ui.value);

					if(active.list_ui.value>=active.list.size())
						task_viewer.working_on.value=false;
					else
						task_viewer.working_on.value=active.list[active.list_ui.value].working_on;

					save_active=true;
				}

				if(move_top.pressed)
				{
					task temp=active.list[active.list_ui.value];
					active.list.remove(active.list_ui.value);

					active.list.insert(temp,0);
					active.list_ui.value=0;
					task_viewer.working_on.value=active.list[0].working_on;
					save_active=true;
				}
			}
			else if(archive.visible)
			{
				move_down.disabled=true;
				move_up.disabled=true;

				if((int)archive.list_ui.value>=0)
				{
					add_task.disabled=false;
					archive_task.disabled=false;
				}
				else
				{
					add_task.disabled=true;
					archive_task.disabled=true;
				}

				add_task.value="Restore Task";
				archive_task.value="Delete Task";

				if(add_task.pressed)
				{
					if((int)archive.list_ui.value>=0)
					{
						active.list.insert(archive.list[archive.list_ui.value],0);
						archive.list.remove(archive.list_ui.value);

						save_active=true;
						save_archive=true;
					}
				}

				if(archive_task.pressed&&(int)archive.list_ui.value>=0)
				{
					archive.list.remove(archive.list_ui.value);

					save_archive=true;
				}
			}

			if(save_active)
				active.list.save("active.bak");

			if(save_archive)
				archive.list.save("archive.bak");
		}

		void draw()
		{
			v0.draw();
		}

		double x;
		double y;
		double display_width;
		double display_height;
		bool loaded_active;

		msl::button escape;
		msl::button add_task;
		msl::button archive_task;
		msl::button active_list_view;
		msl::button archive_list_view;
		msl::button move_top;
		msl::button move_down;
		msl::button move_up;
		msl::hdock h0;
		msl::vdock v0;
};

menu_bar menu(0,0);
task_list_ui active(0,0);
task_list_ui archive(0,0);

task_ui task_viewer(0,0);

int main()
{
	msl::start_2d("Drudgery",744.562+9,480,false);
	return 0;
}

void setup()
{
	msl::set_text_font("Ubuntu-B.ttf");
	msl::set_text_size(12);

	menu.setup(active,archive);

	if(!menu.loaded_active)
		active.list.add(task(date(18,12,2013),"I need to add tasks to Drudgery.","My First Task",0,0));

	archive.visible=false;
	active.visible=!archive.visible;
}

void loop(const double dt)
{
	menu.y=msl::window_height/2.0;

	task_viewer.y=msl::window_height/2.0-menu.display_height-task_viewer.display_height/2.0-1;

	active.y=task_viewer.y-task_viewer.display_height/2.0-1;
	archive.y=task_viewer.y-task_viewer.display_height/2.0-1;

	active.list_ui.width=archive.list_ui.width=menu.display_width-active.list_ui.padding*2;

	std::cout<<active.list_ui.width<<std::endl;

	if(active.visible)
	{
		task_viewer.working_on.disabled=false;
		task_viewer.modify.disabled=false;
	}
	else if(archive.visible)
	{
		task_viewer.working_on.value=false;
		task_viewer.modify.value=false;
		task_viewer.working_on.disabled=true;
		task_viewer.modify.disabled=true;
	}

	active.loop(dt);
	archive.loop(dt);

	menu.loop(dt,active,archive,task_viewer);

	active.list_ui.disabled=task_viewer.modify.value;

	if(active.visible&&(int)active.list_ui.value>=0&&active.list.size()>0)
	{
		task_viewer.disabled=false;
		task_viewer.loop(dt,active.list[active.list_ui.value]);
	}
	else if(archive.visible&&(int)archive.list_ui.value>=0&&archive.list.size()>0)
	{
		task_viewer.disabled=false;
		task_viewer.loop(dt,archive.list[archive.list_ui.value]);
	}
	else
	{
		task temp(date(0,0,0),"","",0,0);
		task_viewer.disabled=true;
		task_viewer.loop(dt,temp);
	}
}

void draw()
{
	menu.draw();

	active.list_ui.y=task_viewer.y-task_viewer.display_height/2.0-1-active.list_ui.display_height/2.0;
	archive.list_ui.y=task_viewer.y-task_viewer.display_height/2.0-1-archive.list_ui.display_height/2.0;

	unsigned int old_index=active.list_ui.value;
	if(active.list.size()>0)
		active.draw();
	unsigned int new_index=active.list_ui.value;

	if(archive.list.size()>0)
		archive.draw();

	if(old_index!=new_index&&(int)old_index>=0)
		task_viewer.working_on.value=active.list[active.list_ui.value].working_on;

	task_viewer.draw();
	task_viewer.draw();
}