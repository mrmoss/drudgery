#include "msl/2d.hpp"

#include "msl/glut_ui.hpp"

#include "task_list.hpp"

#include "task.hpp"

class task_ui
{
	public:
		task_ui(const double x,const double y,task& T):t(&T),x(x),y(y),width(328),height(248),
			due_day("",x,y),due_month("",x,y),due_year("",x,y),info("",x,y),name("",x,y),
			time_estimate("",x,y),time_working("",x,y),modify(false,x,y),padding_(4)
		{}

		void setup()
		{

			//Setup Name
			name.width=320;
			name.text_color_disabled=msl::color(0,0,0,1);
			name.outline_color_disabled=msl::color(1,1,1,1);
			name.background_color_disabled=msl::color(1,1,1,1);

			//Setup Due Day
			due_day.width=22;
			due_day.max_length=2;
			due_day.text_color_disabled=msl::color(0,0,0,1);
			due_day.outline_color_disabled=msl::color(1,1,1,1);
			due_day.background_color_disabled=msl::color(1,1,1,1);

			//Setup Due Month
			due_month.width=22;
			due_month.max_length=2;
			due_month.text_color_disabled=msl::color(0,0,0,1);
			due_month.outline_color_disabled=msl::color(1,1,1,1);
			due_month.background_color_disabled=msl::color(1,1,1,1);

			//Setup Due Year
			due_year.width=32;
			due_year.max_length=4;
			due_year.text_color_disabled=msl::color(0,0,0,1);
			due_year.outline_color_disabled=msl::color(1,1,1,1);
			due_year.background_color_disabled=msl::color(1,1,1,1);

			//Setup Info
			info.width=320;
			info.text_color_disabled=msl::color(0,0,0,1);
			info.outline_color_disabled=msl::color(1,1,1,1);
			info.background_color_disabled=msl::color(1,1,1,1);

			//Setup Time Working
			time_working.width=48;
			time_working.text_color_disabled=msl::color(0,0,0,1);
			time_working.outline_color_disabled=msl::color(1,1,1,1);
			time_working.background_color_disabled=msl::color(1,1,1,1);

			//Setup Time Estimate
			time_estimate.width=48;
			time_estimate.text_color_disabled=msl::color(0,0,0,1);
			time_estimate.outline_color_disabled=msl::color(1,1,1,1);
			time_estimate.background_color_disabled=msl::color(1,1,1,1);
		}

		void loop(const double dt)
		{
			due_day.disabled=due_month.disabled=due_year.disabled=info.disabled=name.disabled=time_estimate.disabled=time_working.disabled=!modify.value;

			if(!modify.value)
			{
				due_day.value=msl::to_string(t->due_date.day);
				due_month.value=msl::to_string(t->due_date.month);
				due_year.value=msl::to_string(t->due_date.year);
				info.value=t->info;
				name.value=t->name;
				time_estimate.value=msl::to_string(t->time_estimate);
				time_working.value=msl::to_string(t->time_working);
			}


			//Position Name
			name.x=x-width/2.0+padding_+name.display_width/2.0;
			name.y=y+height/2.0-padding_-name.display_height/2.0;

			//Position Due Date Day
			due_day.x=x-width/2.0+padding_+due_day.display_width/2.0;
			due_day.y=name.y-name.display_height/2.0-padding_-due_day.display_height/2.0;

			//Position Due Date Month
			due_month.x=due_day.x+padding_+(due_day.display_width+due_month.display_width)/2.0;
			due_month.y=due_day.y;

			//Position Due Date Year
			due_year.x=due_month.x+padding_+(due_month.display_width+due_year.display_width)/2.0;
			due_year.y=due_day.y;

			//Position Time Working
			time_working.x=due_year.x+due_year.display_width/2.0+padding_*4+time_working.display_width/2.0;
			time_working.y=due_day.y;

			//Position Time Estimate
			time_estimate.x=time_working.x+time_working.display_width/2.0+padding_+time_estimate.display_width/2.0;
			time_estimate.y=due_day.y;

			//Position Info
			info.x=x-width/2.0+padding_+info.display_width/2.0;
			info.y=due_year.y-due_year.display_height/2.0-padding_-info.display_height/2.0;

			if(modify.value)
			{
				t->due_date.day=msl::to_int(due_day.value);
				t->due_date.month=msl::to_int(due_month.value);
				t->due_date.year=msl::to_int(due_year.value);
				t->info=info.value;
				t->name=name.value;
				t->time_estimate=msl::to_int(time_estimate.value);
				t->time_working=msl::to_int(time_working.value);
			}

			due_day.loop(dt);
			due_month.loop(dt);
			due_year.loop(dt);
			info.loop(dt);
			name.loop(dt);
			time_estimate.loop(dt);
			time_working.loop(dt);
			modify.loop(dt);
		}

		void draw()
		{
			msl::draw_rectangle(x,y,width+padding_*2,height+padding_*2,true);

			due_day.draw();
			due_month.draw();
			due_year.draw();
			info.draw();
			name.draw();
			time_estimate.draw();
			time_working.draw();
			modify.draw();
		}

		task* t;
		double x;
		double y;
		double width;
		double height;

		msl::textbox due_day;
		msl::textbox due_month;
		msl::textbox due_year;
		msl::textbox info;
		msl::textbox name;
		msl::textbox time_estimate;
		msl::textbox time_working;
		msl::checkbox modify;

	private:
		double padding_;
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