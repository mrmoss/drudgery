#ifndef MENU_BAR
#define MENU_BAR

#include "msl/glut_ui.hpp"
#include "task_ui.hpp"
#include "task_list_ui.hpp"

class menu_bar
{
	public:
		menu_bar(const double x=0,const double y=0);

		void setup(task_list_ui& active,task_list_ui& archive);

		void loop(const double dt,task_list_ui& active,task_list_ui& archive,task_ui& task_viewer);

		void draw();

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

#endif