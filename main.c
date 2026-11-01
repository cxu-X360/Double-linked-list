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

	list_destroy(&main_list);

	END_FUNC

	return 0;
}