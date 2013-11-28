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
			due_year.width=40;
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

			//Position Name
			name.x=x-width/2.0+padding_+name.display_width/2.0;
			name.y=y+height/2.0-padding_-name.display_height/2.0;

			//Position Due Date Month
			due_month.x=x-width/2.0+padding_+due_month.display_width/2.0;
			due_month.y=name.y-name.display_height/2.0-padding_-due_month.display_height/2.0;

			//Position Due Date Day
			due_day.x=due_month.x+padding_+(due_month.display_width+due_day.display_width)/2.0;
			due_day.y=due_month.y;

			//Position Due Date Year
			due_year.x=due_day.x+padding_+(due_day.display_width+due_year.display_width)/2.0;
			due_year.y=due_month.y;

			//Position Time Working
			time_working.x=due_year.x+due_year.display_width/2.0+padding_*4+time_working.display_width/2.0;
			time_working.y=due_month.y;

			//Position Time Estimate
			time_estimate.x=time_working.x+time_working.display_width/2.0+padding_+time_estimate.display_width/2.0;
			time_estimate.y=due_month.y;

			//Position Info
			info.x=x-width/2.0+padding_+info.display_width/2.0;
			info.y=due_year.y-due_year.display_height/2.0-padding_-info.display_height/2.0;

			//Loop
			due_day.loop(dt);
			due_month.loop(dt);
			due_year.loop(dt);
			info.loop(dt);
			name.loop(dt);
			time_estimate.loop(dt);
			time_working.loop(dt);
			modify.loop(dt);

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