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
		{}

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

			display_width=0;
			display_height=0;
			double draw_y=y;

			if(list.size()>0)
			{
				display_width=ui_list[0]->display_width;
				display_height=ui_list[0]->display_height*list.size();
				draw_y-=ui_list[0]->display_height/2.0;
			}

			for(unsigned int ii=0;ii<list.size();++ii)
			{
				ui_list[ii]->x=x;
				ui_list[ii]->y=draw_y-(ii*ui_list[0]->display_height);
				ui_list[ii]->loop(dt,list[ii]);
			}
		}

		void draw()
		{
			for(unsigned int ii=0;ii<ui_list.size();++ii)
				ui_list[ii]->draw();

			if(list.size()==0)
			{
				std::string text_string="You have no tasks";
				double text_width=msl::text_width(text_string);
				double text_height=msl::text_height(text_string);
				msl::draw_text(x-text_width/2.0,y-text_height,text_string,msl::color(0,0,0,1));
			}
		}

		double x;
		double y;
		double display_width;
		double display_height;

		task_list list;
		std::vector<task_ui*> ui_list;
};

menu_bar menu(0,0);
task_list_ui tasks(0,0);

msl::list test;

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
	/*menu.y=msl::window_height/2.0;
	tasks.y=msl::window_height/2.0-menu.display_height;

	menu.loop(dt);*/

	if(msl::input_check_pressed(kb_escape))
		exit(0);

	if(msl::input_check_pressed(kb_f2))
		tasks.list.add(task(date(12,1,1980),"This is my task description.","Task title",12,95));

	if(msl::input_check_pressed(kb_f1)&& tasks.list.size()>0)
		tasks.list.remove(tasks.list.size()-1);

	tasks.loop(dt);

	std::vector<std::string> temp;

	for(unsigned int ii=0;ii<tasks.list.size();++ii)
		temp.push_back(tasks.list[ii].name);

	test.options=temp;
	test.loop(dt);
}

void draw()
{
	//menu.draw();
	//tasks.draw();
	test.draw();
}