#include "task_list_ui.hpp"

task_list_ui::task_list_ui(const double x,const double y):x(x),y(y),display_width(0),display_height(0),
	visible(true),needs_saving(false)
{}

void task_list_ui::loop(const double dt)
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

void task_list_ui::draw()
{
	if(visible)
		list_ui.draw();
}