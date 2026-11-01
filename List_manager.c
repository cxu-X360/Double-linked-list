#include "List.h"


//SERVICE segment
//-----------------------------------------------------------------------------------------------------------------------------
void _fill_poison(List* lst)
{
	for (size_t i = lst->size + 1; i < lst->capacity; i++)
	{
		if (i == 0) continue;

		lst->values[i] = NAN;
		lst->prev[i] = INT_PZ;
		lst->next[i] = INT_PZ;
	}
}

size_t _find_el(List* lst, size_t index)
{
	//verif
	size_t pointer = 0;

	for (size_t i = 0; i < index + 1; i++) pointer = lst->next[pointer];
	
	//verif
	return pointer;
}



//[name it] seqment
//-----------------------------------------------------------------------------------------------------------------------------
int list_init(List* lst, size_t start_capacity)
{
	START_FUNC

	if ((ssize_t) start_capacity < 0)
	{	
		fprintf(stderr, "capacity < 0 error\n");
		return LESS_ZERO_CAPACITY;
	}

	*lst = (List) {.values = calloc(start_capacity, sizeof(double)),
				   .prev =   calloc(start_capacity, sizeof(size_t)),   
				   .next =   calloc(start_capacity, sizeof(size_t)),   
				   .capacity = start_capacity,
				   .size = 0,
				   .free_el = -1};
	//verif

	_fill_poison(lst);

	lst->values[0] = NUL_EL_VAL;
	lst->prev[0] = 0;
	lst->next[0] = 0;

	//verif

	END_FUNC

	return 0;
}

int list_destroy(List* lst)
{
	//verif

	free(lst->values);
	free(lst->prev);
	free(lst->next);

	lst->capacity = 0;
	lst->size = 0;

	return 0;
}

void traverse_list(List* lst, void (*func) (void*))
{
	START_FUNC

	//verif
	size_t pointer = 0;

	while (pointer  != 0)
	{
		pointer = lst->next[pointer];
		func(&(lst->values[pointer]));
	} 

	puts("\ntraverse ended.\n");
}

void print_list(List* lst)
{
	size_t pointer = 0;
	printf("size = %zu, cap = %zu\n",lst->size, lst->capacity);
	printf("head = [%zu], tail = [%zu]\n", lst->next[0], lst->prev[0]);

	while (pointer < 50)
	{
		
		printf("pointer = [%zu]|<val = %lg, next_ptr = %zu, prev_ptr = %zu>\n", pointer, lst->values[pointer], lst->next[pointer], lst->prev[pointer]);
		pointer++;
	}
}

//ADD segment
//-----------------------------------------------------------------------------------------------------------------------------
int list_resize_up(List* lst)
{
	//verif

	lst->capacity *= 2;

	lst->values = realloc(lst->values, lst->capacity * sizeof(double));
	lst->next = realloc(lst->next, lst->capacity * sizeof(size_t));
	lst->prev = realloc(lst->prev, lst->capacity * sizeof(size_t));

	//verif
	return 0;
}

int _add_element(List* lst, size_t prev_ptr,  double val)
{
	START_FUNC

	size_t pointer = 0;
	if (lst->free_el >= 0)
	{
		pointer = lst->free_el;
		lst->free_el = lst->next[lst->free_el];
	}
	else pointer = lst->size + 1;

	lst->values[pointer] = val;

	lst->next[pointer] = lst->next[prev_ptr];
	lst->prev[pointer] = prev_ptr;

	lst->prev[lst->next[prev_ptr]] = pointer;
	lst->next[prev_ptr] = pointer;
	
	lst->size++;

	END_FUNC

	return 0;
}


int list_pushback(List* lst, double val)
{
	START_FUNC
	//verif

	if ((lst->size + 1) == lst->capacity) list_resize_up(lst);
	print_list(lst);

	size_t tail = lst->prev[0];
	printf("tail = %zu\n", tail);
	_add_element(lst, tail, val);

	//verif
	END_FUNC

	return 0;
}

int list_pushfront(List* lst, double val)
{	
	//verif

	if (lst->size == lst->capacity) list_resize_up(lst);
	

	_add_element(lst, 0, val);
	print_list(lst);

	//verif
	return 0;
}

int list_insert(List* lst, size_t index, double val)
{
	//verif

	if (lst->size == lst->capacity) list_resize_up(lst);

	size_t prev_elem_ptr = _find_el(lst, index - 1);
	_add_element(lst, prev_elem_ptr, val);


	//verif
	return 0;
}




//DELETE segment
//------------------------------------------------------------------------------------------------------------------------------
int _delete_element(List* lst, size_t pointer, double* val)
{
	*val = lst->values[pointer];
	lst->values[pointer] = NAN;

	lst->next[lst->prev[pointer]] = lst->next[pointer];
	lst->prev[lst->next[pointer]] = lst->prev[pointer];

	lst->next[pointer] = lst->free_el;
	lst->free_el = pointer;
	lst->prev[pointer] = INT_PZ;

	lst->size--;

	return 0;
}

int list_popback(List* lst, double* val)
{
	//verif 

	if (lst->size == 0)
	{
		fprintf(stderr, "LIST UNDERFLOW. NO elements to push(\n");
		return LIST_UNDERFLOW;
	}

	size_t tail = lst->prev[0];
	_delete_element(lst, tail, val);

	//verif
	return 0;
}

int list_popfront(List* lst, double* val)
{
	//verif 

	if (lst->size == 0)
	{
		fprintf(stderr, "LIST UNDERFLOW. NO elements to push(\n");
		return LIST_UNDERFLOW;
	}

	size_t head = lst->next[0];
	_delete_element(lst, head, val);

	//verif
	return 0;
}

int list_delete(List* lst, size_t index, double* value)
{
	//verif 

	if (lst->size == 0)
	{
		fprintf(stderr, "LIST UNDERFLOW. NO elements to push(\n");
		return LIST_UNDERFLOW;
	}

	size_t cur_elem_ptr = _find_el(lst, index);
	_delete_element(lst, cur_elem_ptr, value);

	//verif
	return 0;
}