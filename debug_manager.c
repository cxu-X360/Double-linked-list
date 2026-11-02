#include "List.h"

int verificator(List* lst)
{
	if (lst->capacity <= 0)
	{
		fprintf(stderr, "capacity < 0 error\n");
		return LESS_ZERO_CAPACITY;
	}

	if (lst->size < 0)
	{
		fprintf(stderr, "size < 0 error\n");
		return LESS_ZERO_SIZE;
	}

	if (lst->values == NULL)
	{
		fprintf(stderr, "null val ptr error\n");
		return ARRAY_NULL_PTR;
	}

	if (lst->prev == NULL)
	{
		fprintf(stderr, "null prev ptr error\n");
		return ARRAY_NULL_PTR;
	}

	if (lst->next == NULL)
	{
		fprintf(stderr, "null next ptr error\n");
		return ARRAY_NULL_PTR;
	}

	if ()



	return 0;
}