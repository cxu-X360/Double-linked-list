#include "List.h"

void print_list(List* lst)
{
	size_t pointer = 0;
	printf("\n\n");
	printf("size = %zu, cap = %zu\n", lst->size, lst->capacity);
	printf("head = [%zu], tail = [%zu]\n", lst->next[0], lst->prev[0]);

	do
	{
		printf("pointer = [%zu]|<val = %lg, next_ptr = %zu, prev_ptr = %zu>\n", pointer, lst->values[pointer], lst->next[pointer], lst->prev[pointer]);
		pointer = lst->next[pointer];
	} while (pointer != 0);

	printf("Free cells:\n");
	ssize_t free_el_pointer = lst->last_free;
	while (free_el_pointer > 0)
	{
		printf("pointer = [%zu]| <val = FREE>, next_free_ptr = [%zu]\n", free_el_pointer, lst->next[free_el_pointer]);
		free_el_pointer = lst->next[free_el_pointer];
	}

	printf("End of dump\n");
}

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

	if (lst->size > lst->capacity)
	{
		fprintf(stderr, "List Overflow error\n");
		return LIST_OVERFLOW;
	}
	
	if (lst->last_free < -1 || lst->last_free == 0  || lst->last_free >= lst->capacity)
	{
		fprintf(stderr, "free pointer out of range\n");
		return FREE_OUT_OF_RANGE;
	}

	return 0;
}



