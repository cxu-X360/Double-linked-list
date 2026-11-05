#include "src/List.h"

int main()
{
	START_FUNC

	List main_list = {};

	list_init(&main_list, 10);
	
	int dump_file_num = 1;

	for (int i = 0; i < 5; i++)
	{
		list_pushback(&main_list, (double) i);
		graph_script_generate(&main_list, &dump_file_num);
	}
	for (int i = 5; i < 15; i++)
	{
		list_pushfront(&main_list, (double) i);
		graph_script_generate(&main_list, &dump_file_num);
	}

	list_insert(&main_list, 6, 68.99);
	graph_script_generate(&main_list, &dump_file_num);
	list_insert(&main_list,	7, 78.99);
	graph_script_generate(&main_list, &dump_file_num);
	list_insert(&main_list, 8, 88.99);
	graph_script_generate(&main_list, &dump_file_num);

	print_list(&main_list);

	double temp1 = NAN;
	list_popback(&main_list, &temp1);
	print_list(&main_list);
	graph_script_generate(&main_list, &dump_file_num);

	double temp2 = NAN;
	list_popfront(&main_list, &temp2);
	print_list(&main_list);
	graph_script_generate(&main_list, &dump_file_num);
	
	double temp3 = NAN;
	list_delete(&main_list, 13, &temp3);
	print_list(&main_list);
	graph_script_generate(&main_list, &dump_file_num);

	list_destroy(&main_list);

	END_FUNC

	return 0;
}