#include "List.h"



void print_double(void* val_ptr)
{
	START_FUNC

	double val = *(double*) val_ptr;
	printf("%lg, ", val);

	END_FUNC
}

int main()
{
	START_FUNC

	List main_list = {};

	list_init(&main_list, 10);

	for (int i = 0; i < 25; i++)
	{
		list_pushback(&main_list, (double) i);
		//traverse_list(&main_list, print_double);
	}
	for (int i = 25; i < 50; i++)
	{
		list_pushfront(&main_list, (double) i);
	}

	list_insert(&main_list, 6, 68.99);
	list_insert(&main_list,	7, 78.99);
	list_insert(&main_list, 8, 88.99);

	print_list(&main_list);

	double temp1 = NAN;
	list_popback(&main_list, &temp1);
	print_list(&main_list);

	double temp2 = NAN;
	list_popfront(&main_list, &temp2);
	print_list(&main_list);
	
	double temp3 = NAN;
	list_delete(&main_list, 26, &temp3);
	print_list(&main_list);

	list_destroy(&main_list);

	END_FUNC

	return 0;
}