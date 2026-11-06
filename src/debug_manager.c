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

void verificator(List* lst)
{
	if (lst->capacity <= 0)
	{
		fprintf(stderr, "capacity < 0 error\n");
		lst->error = LESS_ZERO_CAPACITY;
		return;
	}

	if (lst->size < 0)
	{
		fprintf(stderr, "size < 0 error\n");
		lst->error = LESS_ZERO_SIZE;
		return;
	}

	if (lst->values == NULL)
	{
		fprintf(stderr, "null val ptr error\n");
		lst->error= ARRAY_NULL_PTR;
		return;
	}

	if (lst->prev == NULL)
	{
		fprintf(stderr, "null prev ptr error\n");
		lst->error = ARRAY_NULL_PTR;
		return;
	}

	if (lst->next == NULL)
	{
		fprintf(stderr, "null next ptr error\n");
		lst->error = ARRAY_NULL_PTR;
		return;
	}

	if (lst->size > lst->capacity)
	{
		fprintf(stderr, "List Overflow error\n");
		lst->error = LIST_OVERFLOW;
		return;
	}
	
	if (lst->last_free < -1 || lst->last_free == 0  || lst->last_free >= (ssize_t) lst->capacity)
	{
		fprintf(stderr, "free pointer out of range\n");
		lst->error = FREE_OUT_OF_RANGE;
		return;
	}

	lst->error = 0;
	return;
}



