#ifndef TASK_UI
#define TASK_UI

#include "msl/glut_ui.hpp"

#include "task.hpp"

class task_ui
{
	public:
		task_ui(const double x,const double y);

		void loop(const double dt,task& my_task);

		void draw();

		double x;
		double y;
		double display_width;
		double display_height;

		bool disabled;

		msl::textbox name;
		msl::textbox info;
		msl::textbox due_day;
		msl::textbox due_month;
		msl::textbox due_year;
		msl::textbox time_estimate;
		msl::textbox time_working;
		msl::checkbox modify;
		msl::checkbox working_on;

	private:
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
		msl::hdock h4;

		double padding_;
};

#endif