#include "msl/2d.hpp"
#include "menu_bar.hpp"
#include "task_ui.hpp"
#include "task_list_ui.hpp"

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