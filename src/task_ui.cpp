#include "task_ui.hpp"

#include "msl/string_util.hpp"

task_ui::task_ui(const double x,const double y):x(x),y(y),display_width(0),display_height(0),modify(false,x,y),padding_(4)
{
	//Setup Name
	name.width=320-padding_*2;
	name.text_color_disabled=msl::color(0,0,0,1);
	name.outline_color_disabled=msl::color(1,1,1,1);
	name.background_color_disabled=msl::color(1,1,1,1);

	//Setup Info
	info.width=320-padding_*2;
	info.text_color_disabled=msl::color(0,0,0,1);
	info.outline_color_disabled=msl::color(1,1,1,1);
	info.background_color_disabled=msl::color(1,1,1,1);

	//Setup Due Day
	due_day.width=32-padding_*2;
	due_day.max_length=2;
	due_day.text_color_disabled=msl::color(0,0,0,1);
	due_day.outline_color_disabled=msl::color(1,1,1,1);
	due_day.background_color_disabled=msl::color(1,1,1,1);

	//Setup Due Month
	due_month.width=32-padding_*2;
	due_month.max_length=2;
	due_month.text_color_disabled=msl::color(0,0,0,1);
	due_month.outline_color_disabled=msl::color(1,1,1,1);
	due_month.background_color_disabled=msl::color(1,1,1,1);

	//Setup Due Year
	due_year.width=44-padding_*2;
	due_year.max_length=4;
	due_year.text_color_disabled=msl::color(0,0,0,1);
	due_year.outline_color_disabled=msl::color(1,1,1,1);
	due_year.background_color_disabled=msl::color(1,1,1,1);

	//Setup Time Working
	time_working.width=40-padding_*2;
	time_working.text_color_disabled=msl::color(0,0,0,1);
	time_working.outline_color_disabled=msl::color(1,1,1,1);
	time_working.background_color_disabled=msl::color(1,1,1,1);

	//Setup Time Estimate
	time_estimate.width=40-padding_*2;
	time_estimate.text_color_disabled=msl::color(0,0,0,1);
	time_estimate.outline_color_disabled=msl::color(1,1,1,1);
	time_estimate.background_color_disabled=msl::color(1,1,1,1);

	//Setup Captions
	name_caption.disabled=true;
	name_caption.outline_color_disabled.a=name_caption.background_color_to.a=0;
	name_caption.text_color_disabled=msl::color(0,0,0,1);
	name_caption.value="Name";
	name_caption.width=32;
	info_caption.disabled=true;
	info_caption.outline_color_disabled.a=info_caption.background_color_to.a=0;
	info_caption.text_color_disabled=msl::color(0,0,0,1);
	info_caption.value="Info";
	info_caption.width=32;
	time_estimate_caption.disabled=true;
	time_estimate_caption.outline_color_disabled.a=time_estimate_caption.background_color_to.a=0;
	time_estimate_caption.text_color_disabled=msl::color(0,0,0,1);
	time_estimate_caption.value="Time Estimate (min)";
	time_working_caption.disabled=true;
	time_working_caption.outline_color_disabled.a=time_working_caption.background_color_to.a=0;
	time_working_caption.text_color_disabled=msl::color(0,0,0,1);
	time_working_caption.value="Time Working (min)";
	working_caption.disabled=true;
	working_caption.outline_color_disabled.a=working_caption.background_color_to.a=0;
	working_caption.text_color_disabled=msl::color(0,0,0,1);
	working_caption.value="Working On";
	due_date_caption.disabled=true;
	due_date_caption.outline_color_disabled.a=due_date_caption.background_color_to.a=0;
	due_date_caption.text_color_disabled=msl::color(0,0,0,1);
	due_date_caption.value="Due Date (MM/DD/YYYY)";
	modify_caption.disabled=true;
	modify_caption.outline_color_disabled.a=modify_caption.background_color_to.a=0;
	modify_caption.text_color_disabled=msl::color(0,0,0,1);
	modify_caption.value="Modify";

	//Setup First Row
	h0.widgets.push_back(&name_caption);
	h0.widgets.push_back(&name);
	h0.outline_color=h0.background_color_to=h0.background_color_from=msl::color(0,0,0,0);

	//Setup Second Row
	h1.widgets.push_back(&info_caption);
	h1.widgets.push_back(&info);
	h1.outline_color=h1.background_color_to=h1.background_color_from=msl::color(0,0,0,0);

	//Setup Third Row
	h2.widgets.push_back(&time_estimate_caption);
	h2.widgets.push_back(&time_estimate);
	h2.widgets.push_back(&time_working_caption);
	h2.widgets.push_back(&time_working);
	h2.outline_color=h2.background_color_to=h2.background_color_from=msl::color(0,0,0,0);

	//Setup Third Row
	h3.widgets.push_back(&due_date_caption);
	h3.widgets.push_back(&due_month);
	h3.widgets.push_back(&due_day);
	h3.widgets.push_back(&due_year);
	h3.outline_color=h3.background_color_to=h3.background_color_from=msl::color(0,0,0,0);

	//Setup Fourth Row
	h4.widgets.push_back(&working_caption);
	h4.widgets.push_back(&working_on);
	h4.widgets.push_back(&modify_caption);
	h4.widgets.push_back(&modify);
	h4.outline_color=h4.background_color_to=h4.background_color_from=msl::color(0,0,0,0);

	//Setup Column
	v0.widgets.push_back(&h0);
	v0.widgets.push_back(&h1);
	v0.widgets.push_back(&h2);
	v0.widgets.push_back(&h3);
	v0.widgets.push_back(&h4);
}

void task_ui::loop(const double dt,task& my_task)
{
	if(!modify.value)
	{
		due_day.value=msl::to_string(my_task.due_date.day);
		due_day.disabled=true;

		due_month.value=msl::to_string(my_task.due_date.month);
		due_month.disabled=true;

		due_year.value=msl::to_string(my_task.due_date.year);
		due_year.disabled=true;

		info.value=my_task.info;
		info.disabled=true;

		name.value=my_task.name;
		name.disabled=true;

		time_estimate.value=msl::to_string(my_task.time_estimate);
		time_estimate.disabled=true;

		time_working.value=msl::to_string(my_task.time_working);
		time_working.disabled=true;
	}
	else
	{
		my_task.due_date.day=msl::to_int(due_day.value);
		due_day.disabled=false;

		my_task.due_date.month=msl::to_int(due_month.value);
		due_month.disabled=false;

		my_task.due_date.year=msl::to_int(due_year.value);
		due_year.disabled=false;

		my_task.info=info.value;
		info.disabled=false;

		my_task.name=name.value;
		name.disabled=false;

		my_task.time_estimate=msl::to_int(time_estimate.value);
		time_estimate.disabled=false;

		my_task.time_working=msl::to_int(time_working.value);
		time_working.disabled=false;
	}

	my_task.working_on=(working_on.value&&!modify.value);

	v0.x=x;
	v0.y=y;

	//Loop GUI
	v0.loop(dt);

	display_width=v0.display_width;
	display_height=v0.display_height;

	//Restrict Number Entries to Numbers
	if((modify.value&&due_day.value.size()>1)||!modify.value)
	{
		due_day.value=msl::to_string(msl::to_int(due_day.value));

		if(msl::to_int(due_day.value)<1)
		{
			due_day.value=msl::to_string(1);
			my_task.due_date.day=msl::to_int(due_day.value);
		}

		if(msl::to_int(due_day.value)>31)
		{
			due_day.value=msl::to_string(31);
			my_task.due_date.day=msl::to_int(due_day.value);
		}
	}

	if((modify.value&&due_month.value.size()>1)||!modify.value)
	{
		due_month.value=msl::to_string(msl::to_int(due_month.value));

		if(msl::to_int(due_month.value)<1)
		{
			due_month.value=msl::to_string(1);
			my_task.due_date.month=msl::to_int(due_month.value);
		}

		if(msl::to_int(due_month.value)>12)
		{
			due_month.value=msl::to_string(12);
			my_task.due_date.month=msl::to_int(due_month.value);
		}
	}

	if((modify.value&&due_year.value.size()>3)||!modify.value)
	{
		due_year.value=msl::to_string(msl::to_int(due_year.value));

		if(msl::to_int(due_year.value)<1970)
		{
			due_year.value=msl::to_string(1970);
			my_task.due_date.year=msl::to_int(due_year.value);
		}
	}

	if((modify.value&&time_estimate.value.size()>0)||!modify.value)
		time_estimate.value=msl::to_string(msl::to_int(time_estimate.value));

	if((modify.value&&time_working.value.size()>0)||!modify.value)
		time_working.value=msl::to_string(msl::to_int(time_working.value));
}

void task_ui::draw()
{
	v0.draw();
}