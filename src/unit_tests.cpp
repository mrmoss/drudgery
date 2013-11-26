//Date Header
#include "date.hpp"

//IO Stream Header
#include <iostream>

//Task Header
#include "task.hpp"

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
	task add_task_test(date(1,1,1970),"Blah blah blarg.","Task A",54,23);

	//Test Output
	std::cout<<"\t\tadd task test\t";

	//Test Case
	if(add_task_test.name=="Task A"&&add_task_test.info=="Blah blah blarg."&&add_task_test.time_estimate==54&&add_task_test.time_working==23)
		std::cout<<":)"<<std::endl;
	else
		std::cout<<":("<<std::endl;

	//Add Some Minutes
	++add_task_test.time_working;
	++add_task_test.time_working;
	++add_task_test.time_working;

	//Test Output
	std::cout<<"\t\tadd minute test\t";

	//Test Case
	if(add_task_test.time_working==26)
		std::cout<<":)"<<std::endl;
	else
		std::cout<<":("<<std::endl;

	//Return Gracefully
	return 0;
}