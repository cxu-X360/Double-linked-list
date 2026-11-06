#include "src/List.h"

#define CHECK_ERROR(lst) \
{\
	verificator(lst); \
	graph_script_generate(lst, &dump_file_num); \
	printf("!!!!!!!!ERRORNO ==== %d\n", (lst)->error);\
	if ((lst)->error) return (lst)->error; \
}


int main()
{
	START_FUNC

	List main_list = {};

	list_init(&main_list, 10);
	
	int dump_file_num = 1;

	for (int i = 0; i < 5; i++)
	{
		list_pushback(&main_list, (double) i);
		CHECK_ERROR(&main_list)
	}
	for (int i = 5; i < 15; i++)
	{
		list_pushfront(&main_list, (double) i);
		CHECK_ERROR(&main_list)

	}

	list_insert(&main_list, 6, 68.99);
			CHECK_ERROR(&main_list)

	list_insert(&main_list,	7, 78.99);
		CHECK_ERROR(&main_list)
	list_insert(&main_list, 8, 88.99);
		CHECK_ERROR(&main_list)

	print_list(&main_list);
	main_list.last_free = -2;
	CHECK_ERROR(&main_list)

	double temp1 = NAN;
	list_popback(&main_list, &temp1);
	print_list(&main_list);
		CHECK_ERROR(&main_list)

	double temp2 = NAN;
	list_popfront(&main_list, &temp2);
	print_list(&main_list);
		CHECK_ERROR(&main_list)
	
	double temp3 = NAN;
	list_delete(&main_list, 13, &temp3);
	print_list(&main_list);
		CHECK_ERROR(&main_list)

	list_destroy(&main_list);

	END_FUNC

	return 0;
}