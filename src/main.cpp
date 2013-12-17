#include "msl/2d.hpp"

#include "msl/glut_ui.hpp"

#include "task_list.hpp"

#include "task.hpp"

#include "msl/time_util.hpp"

class task_ui
{
	public:
		task_ui(const double x,const double y,task& T):t(&T),x(x),y(y),width(328),height(248),
			modify(false,x,y),padding_(4),old_time_(0)
		{}

		void setup()
		{
			//Setup Text
			msl::set_text_font("Ubuntu-B.ttf");
			msl::set_text_size(12);

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
			time_working.width=48-padding_*2;
			time_working.text_color_disabled=msl::color(0,0,0,1);
			time_working.outline_color_disabled=msl::color(1,1,1,1);
			time_working.background_color_disabled=msl::color(1,1,1,1);

			//Setup Time Estimate
			time_estimate.width=48-padding_*2;
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
			time_estimate_caption.value="Time Estimate";
			time_working_caption.disabled=true;
			time_working_caption.outline_color_disabled.a=time_working_caption.background_color_to.a=0;
			time_working_caption.text_color_disabled=msl::color(0,0,0,1);
			time_working_caption.value="Time Working";
			working_caption.disabled=true;
			working_caption.outline_color_disabled.a=working_caption.background_color_to.a=0;
			working_caption.text_color_disabled=msl::color(0,0,0,1);
			working_caption.value="Working On";
			due_date_caption.disabled=true;
			due_date_caption.outline_color_disabled.a=due_date_caption.background_color_to.a=0;
			due_date_caption.text_color_disabled=msl::color(0,0,0,1);
			due_date_caption.value="Due Date";
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
			h3.widgets.push_back(&working_caption);
			h3.widgets.push_back(&working_on);
			h3.widgets.push_back(&modify_caption);
			h3.widgets.push_back(&modify);
			h3.outline_color=h3.background_color_to=h3.background_color_from=msl::color(0,0,0,0);

			//Setup Column
			v0.widgets.push_back(&h0);
			v0.widgets.push_back(&h1);
			v0.widgets.push_back(&h2);
			v0.widgets.push_back(&h3);
		}

		void loop(const double dt)
		{
			if(!modify.value)
			{
				due_day.value=msl::to_string(t->due_date.day);
				due_day.disabled=true;

				due_month.value=msl::to_string(t->due_date.month);
				due_month.disabled=true;

				due_year.value=msl::to_string(t->due_date.year);
				due_year.disabled=true;

				info.value=t->info;
				info.disabled=true;

				name.value=t->name;
				name.disabled=true;

				time_estimate.value=msl::to_string(t->time_estimate);
				time_estimate.disabled=true;

				time_working.value=msl::to_string(t->time_working);
				time_working.disabled=true;

				if(working_on.value&&msl::millis()>=old_time_+60000)
				{
					++t->time_working;
					old_time_=msl::millis();
				}
			}
			else
			{
				t->due_date.day=msl::to_int(due_day.value);
				due_day.disabled=false;

				t->due_date.month=msl::to_int(due_month.value);
				due_month.disabled=false;

				t->due_date.year=msl::to_int(due_year.value);
				due_year.disabled=false;

				t->info=info.value;
				info.disabled=false;

				t->name=name.value;
				name.disabled=false;

				t->time_estimate=msl::to_int(time_estimate.value);
				time_estimate.disabled=false;

				t->time_working=msl::to_int(time_working.value);
				time_working.disabled=false;
			}

			if(!working_on.value||modify.value)
				old_time_=msl::millis();

			//Loop
			v0.loop(dt);

			//Restrict Number Entries to Numbers
			if((modify.value&&due_day.value.size()>1)||!modify.value)
			{
				due_day.value=msl::to_string(msl::to_int(due_day.value));

				if(msl::to_int(due_day.value)<1)
					due_day.value=msl::to_string(1);

				if(msl::to_int(due_day.value)>31)
					due_day.value=msl::to_string(31);
			}

			if((modify.value&&due_month.value.size()>1)||!modify.value)
			{
				due_month.value=msl::to_string(msl::to_int(due_month.value));

				if(msl::to_int(due_month.value)<1)
					due_month.value=msl::to_string(1);

				if(msl::to_int(due_month.value)>12)
					due_month.value=msl::to_string(12);
			}

			if((modify.value&&due_year.value.size()>3)||!modify.value)
			{
				due_year.value=msl::to_string(msl::to_int(due_year.value));

				if(msl::to_int(due_year.value)<1970)
					due_year.value=msl::to_string(1970);
			}

			if((modify.value&&time_estimate.value.size()>0)||!modify.value)
				time_estimate.value=msl::to_string(msl::to_int(time_estimate.value));

			if((modify.value&&time_working.value.size()>0)||!modify.value)
				time_working.value=msl::to_string(msl::to_int(time_working.value));

		}

		void draw()
		{
			v0.draw();
		}

		task* t;
		double x;
		double y;
		double width;
		double height;

		msl::textbox name;
		msl::textbox info;
		msl::textbox due_day;
		msl::textbox due_month;
		msl::textbox due_year;
		msl::textbox time_estimate;
		msl::textbox time_working;
		msl::checkbox modify;
		msl::checkbox working_on;

		msl::button name_caption;
		msl::button info_caption;
		msl::button time_estimate_caption;
		msl::button time_working_caption;
		msl::button working_caption;
		msl::button due_date_caption;
		msl::button modify_caption;

		msl::vdock v0;
		msl::hdock h0;
		msl::hdock h1;
		msl::hdock h2;
		msl::hdock h3;

	private:
		double padding_;
		long old_time_;
};

task t(date(12,1,1945),"This is my task description.","Task title",12,95);

task_ui test(0,0,t);

int main()
{
	msl::start_2d("Drudgery",640,480,false);
	return 0;
}

void setup()
{
	test.setup();
}

void loop(const double dt)
{
	if(msl::input_check_pressed(kb_escape))
		exit(0);

	test.loop(dt);
}

void draw()
{
	test.draw();
}