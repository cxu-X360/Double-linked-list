#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define LIST_DEBUG

#define INT_PZ 111111
#define NUL_EL_VAL 6.02e23
#define MAX_FILENAME_SIZE 64

#define START_FUNC printf("%s started\n", __FUNCTION__ );
#define END_FUNC printf("%s ended\n", __FUNCTION__);

enum ERRNO
{
	LIST_NULL_PTR = -1,
	LESS_ZERO_CAPACITY = -2,
	LESS_ZERO_SIZE = -3,
	ARRAY_NULL_PTR = -4,
	LIST_OVERFLOW = -5,
	LIST_UNDERFLOW = -6,
	FREE_OUT_OF_RANGE = -7,
	COUNT_ERRORS,
};


#ifdef LIST_DEBUG
	#define ON_DEBUG(...) __VAR_ARGS__
#else
	#define ON_DEBUG(...) 
#endif

typedef struct 
{
	double* values; 
	size_t* prev;
	size_t* next; 

	size_t capacity;
	size_t size;

	ssize_t last_free; //указатель на  первой свободной ячейки
	size_t last_used;
	enum ERRNO error;

} List;


void graph_script_generate(List* lst, int* dump_file_num);

void verificator(List* lst);
void print_list(List* lst);


int list_init(List* lst, size_t start_cap);
int list_destroy(List* lst);

int list_insert(List* lst, size_t index, double value);
int list_pushback(List* lst, double val);
int list_pushfront(List* lst, double val);

int list_delete(List* lst, size_t index, double* value);
int list_popback(List* lst, double* value);
int list_popfront(List* lst, double* value);

size_t list_len(List* lst);
void print_list(List* lst);
void traverse_list(List* lst, void (*func) (void*));

#endif