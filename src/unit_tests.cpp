//Date Header
#include "date.hpp"

//IO Stream Header
#include <iostream>

//Task Header
#include "task.hpp"

//Task List Header
#include "task_list.hpp"

//Time Utility Header
#include "msl/time_util.hpp"

//Main
int main()
{
	//Output Program Name
	std::cout<<"drudgery unit testing"<<std::endl<<std::endl;

	//Output Test Name
	std::cout<<"\tdate tests"<<std::endl;
	date d0(1,1,1970);
	date d1(1,1,1970);
	date d2(2,1,1970);
	date d3(1,2,1970);
	date d4(1,1,1971);
	date d5(2,2,1970);

	//Test Output
	std::cout<<"\t\tdate equality\t";

	//Test Case
	if(d0==d1)
		std::cout<<":)"<<std::endl;
	else
		std::cout<<":("<<std::endl;

	//Test Output
	std::cout<<"\t\tdate inequality\t";

	//Test Case
	if(d1!=d2&&d2!=d3&&d1!=d4&&d1!=d5)
		std::cout<<":)"<<std::endl;
	else
		std::cout<<":("<<std::endl;


	//Output Test Name
	std::cout<<"\ttask tests"<<std::endl;

	//Create a Task
	task t0(date(1,1,1970),"Blah blah blarg.","Task A",54,23);

	//Test Output
	std::cout<<"\t\tadd task test\t";

	//Test Case
	if(t0.name=="Task A"&&t0.info=="Blah blah blarg."&&t0.time_estimate==54&&t0.time_working==23)
		std::cout<<":)"<<std::endl;
	else
		std::cout<<":("<<std::endl;

	//Add Some Minutes
	++t0.time_working;
	++t0.time_working;
	++t0.time_working;

	//Test Output
	std::cout<<"\t\tadd minute test\t";

	//Test Case
	if(t0.time_working==26)
		std::cout<<":)"<<std::endl;
	else
		std::cout<<":("<<std::endl;

	//Create Task List
	task_list l0;

	//Add Some Tasks
	task t1(date(2,3,1945),"info1","name1",12,12);
	l0.add(t0);
	l0.add(t1);

	//Test Output
	std::cout<<"\t\tsave task list\t";

	//Test Case
	if(l0.save("test.bak"))
		std::cout<<":)"<<std::endl;
	else
		std::cout<<":("<<std::endl;

	//Create Another Task List
	task_list l1;

	//Test Output
	std::cout<<"\t\tload task list\t";

	//Test Case
	if(l1.load("test.bak"))
		std::cout<<":)"<<std::endl;
	else
		std::cout<<":("<<std::endl;

	//Test Output
	std::cout<<"\t\ttest for match\t";

	//Test Case
	if(l0==l1)
		std::cout<<":)"<<std::endl;
	else
		std::cout<<":("<<std::endl;

	//Load/Save 10000 Tasks
	long time_start=msl::millis();
	task_list l2;
	for(unsigned int ii=0;ii<10000;++ii)
		l2.add(task(date(2,3,1945),"info1","name1",12,12));
	bool passed_10000=l2.save("1000.bak");
	task_list l3;
	passed_10000=passed_10000&&l3.load("1000.bak");
	passed_10000=passed_10000&&(l2==l3);
	long time_end=msl::millis();

	//Test Output
	std::cout<<"\t\ttest list of 10000 tasks\t";

	if(passed_10000)
		std::cout<<":)\t";
	else
		std::cout<<":(\t";

	std::cout<<"\n\t\t\tcompleted in:  "<<time_end-time_start<<" ms"<<std::endl;


	//Return Gracefully
	return 0;
}