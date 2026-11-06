#include "List.h"

const char* error_names[-COUNT_ERRORS+1] = {"LIST_NULL_PTR",
	"LESS_ZERO_CAPACITY",
	"LESS_ZERO_SIZE",
	"ARRAY_NULL_PTR",
	"LIST_OVERFLOW" ,
	"LIST_UNDERFLOW", 
	"FREE_OUT_OF_RANGE"};

#define FREE_COLOR "\"#36343b\""
#define LAST_DELETE_COLOR "\"383838\""
#define NODE_COLOR "blue"


#define ERROR_INFO(error) ((!error) ? "no error" : (error_names[-(error)-1]))
#define ERROR_COLOR(error) ((!error) ? "darkgreen" : "\"#590c0e\"")


typedef struct 
{
	FILE* file;
	List* lst;
} GrContext;

static void _create_head_info(GrContext* ctx)
{
	fprintf(ctx->file, 
		"digraph List\n{\n"
		"\tgraph [rankdir=LR, bgcolor=\"#FAE3FF\", pad=0.25, nodesep=0.25, ranksep=0.35];\n" //Pink background
		"\tnode [shape=record, style=\"rounded,filled\", fontname=\"monospace\", fontsize=10, fontcolor=white, color=white fillcolor="NODE_COLOR", penwidth=1.3, margin=\"0.13,0.06\"];\n"
		"\tedge [color=black, arrowsize=0.75, fontname=\"monospace\", fontsize=9, penwidth=1.3]\n;"
	);
}

static void _create_node(GrContext* ctx, size_t pointer)
{
	fprintf(ctx->file, "\tnode_%zu [label=\"{ #%zu | { prev=%zu | next=%zu | val=%lg } }\" %s ];\n", 
			pointer, pointer, ctx->lst->prev[pointer], ctx->lst->next[pointer], ctx->lst->values[pointer], (pointer == (ctx->lst->last_used)) ? " color=\"#f82f0c\" " : " " );
}

static void _create_next_edge(GrContext* ctx, size_t pointer)
{
	fprintf(ctx->file, "\t\"node_%zu\" -> \"node_%zu\" [penwidth=1.6];\n",
			pointer, ctx->lst->next[pointer]);
}

static void _create_prev_edge(GrContext* ctx, size_t pointer)
{
	fprintf(ctx->file, "\t\"node_%zu\" -> \"node_%zu\" [style=dashed, penwidth=1.6];\n",
			pointer, ctx->lst->prev[pointer]);
}

static void _create_free_list(GrContext* ctx)
{
	ssize_t pointer = ctx->lst->last_free;

	while (pointer > 0)
	{
		fprintf(ctx->file, "\tnode_%lld [label=\"{ #%lld | {next=%lld | OLD_val=%lg } }\", fillcolor=" FREE_COLOR"];\n", 
			pointer, pointer, ctx->lst->next[pointer], ctx->lst->values[pointer]); //Free_node

		if ((ssize_t) ctx->lst->next[pointer] > 0)
		{
			fprintf(ctx->file, "\t\"node_%lld\" -> \"node_%lld\" [penwidth=1.6, style=dotted, color="FREE_COLOR"];\n",
					pointer, ctx->lst->next[pointer]);
		}
		
		pointer = ctx->lst->next[pointer];
	}


}

static void _create_main_pointers(GrContext* ctx)
{
	fprintf(ctx->file, "\"Main List\" -> \"node_%zu\" [label=\"HEAD\", color=black, fontcolor=black, penwidth=1.6];\n",
			ctx->lst->next[0]);

	
	if (ctx->lst->last_free > 0) fprintf(ctx->file, "\"Main List\" -> \"node_%zu\" [label=\"FREE\", style=dotted, color=%s fontcolor=%s, penwidth=1.6];\n",
			ctx->lst->last_free, FREE_COLOR, FREE_COLOR);
}

static void _create_error_info(GrContext* ctx)
{
	fprintf(ctx->file, "\"Info\" [label = \"ERRORNO = %d(%s)} \", fillcolor = %s]\n",
			ctx->lst->error, ERROR_INFO(ctx->lst->error), ERROR_COLOR(ctx->lst->error));
}

static void _create_main_node(GrContext* ctx)
{
	fprintf(ctx->file, "\"Main List\" [label=\"{My List | { size=%zu | cap=%zu | last_free=%lld} | {%lg}}\", fillcolor=\"#4f378b\",penwidth=1.4];\n",
			ctx->lst->size, ctx->lst->capacity, ctx->lst->last_free, ctx->lst->values[0]);

}

void graph_script_generate(List* lst, int* dump_file_num)
{
	char file_name[MAX_FILENAME_SIZE] = {};
	snprintf(file_name, MAX_FILENAME_SIZE - 1, "./logs/dot-files/graph_code_%d.dot", *dump_file_num); //(int) ceil(log10((double) *dump_file_num)) + 1

	FILE* graph_script = fopen(file_name, "w");	
	printf("%s opened\n", file_name);
	GrContext ctx = {.lst = lst, .file = graph_script};	

	_create_head_info(&ctx);
	_create_error_info(&ctx);
	_create_main_node(&ctx);
	
	size_t pointer = (ctx.lst)->next[0];
	_create_node(&ctx, pointer);
	if (ctx.lst->size > 1)
	{
		_create_next_edge(&ctx, pointer);

		while (lst->next[lst->next[pointer]] != 0)
		{
			pointer = (ctx.lst)->next[pointer];
			_create_node(&ctx, pointer);
			_create_next_edge(&ctx, pointer);
			_create_prev_edge(&ctx, pointer);
		}

		pointer = (ctx.lst)->next[pointer];
		_create_node(&ctx, pointer);
		_create_prev_edge(&ctx, pointer);
	}	

	_create_free_list(&ctx);

	if (ctx.lst->size > 0)	_create_main_pointers(&ctx);

	fprintf(ctx.file, "}\n");
	fclose(ctx.file);
	(*dump_file_num)++;
}