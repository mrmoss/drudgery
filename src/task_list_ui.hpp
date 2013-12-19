#ifndef TASK_LIST_UI
#define TASK_LIST_UI

#include "msl/glut_ui.hpp"
#include "task_list.hpp"

class task_list_ui
{
	public:
		task_list_ui(const double x=0,const double y=0);

		void loop(const double dt);

		void draw();

		double x;
		double y;
		double display_width;
		double display_height;
		bool visible;
		bool needs_saving;

		task_list list;
		msl::list list_ui;
};

#endif