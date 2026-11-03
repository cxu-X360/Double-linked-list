#include "List.h"

#define FREE_COLOR "\"#36343b\""
#define NODE_COLOR "blue"
#define BORDER_COLOR "white"

typedef struct 
{
	FILE* file;
	List* lst;
} GrContext;

static void _create_head_info(GrContext* ctx)
{
	fprintf(ctx->file, 
		"digraph List\n{\n"
		"\tgraph [rankdir=LR, bgcolor=\"#FDE3FF\", pad=0.25, nodesep=0.25, ranksep=0.35];\n" //Pink background
		"\tnode [shape=record, style=\"rounded,filled\", fontname=\"monospace\", fontsize=10, fontcolor=white, color="BORDER_COLOR" fillcolor="NODE_COLOR", penwidth=1.3, margin=\"0.13,0.06\"];\n"
		"\tedge [color=black, arrowsize=0.75, fontname=\"monospace\", fontsize=9, penwidth=1.3]\n;"
	);
}

static void _create_node(GrContext* ctx, size_t pointer)
{
	fprintf(ctx->file, "\tnode_%zu [label=\"{ #%zu | { prev=%zu | next=%zu | val=%lg } }\"];\n", 
			pointer, pointer, ctx->lst->prev[pointer], ctx->lst->next[pointer], ctx->lst->values[pointer]);
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
		fprintf(ctx->file, "\tnode_%lld [label=\"{ #%lld | {next=%lld | val=NAN } }\", fillcolor=%s];\n", 
			pointer, pointer, ctx->lst->next[pointer], FREE_COLOR); //Free_node
		fprintf(ctx->file, "\t\"node_%lld\" -> \"node_%lld\" [penwidth=1.6, style=dotted, color=%s];\n",
			pointer, ctx->lst->next[pointer], FREE_COLOR);
		pointer = ctx->lst->next[pointer];
	}
}

static void _create_main_pointers(GrContext* ctx)
{
	fprintf(ctx->file, "\"Main List\" -> \"node_%zu\" [label=\"HEAD\", color=black, fontcolor=red, penwidth=1.6];\n",
			ctx->lst->next[0]);

	fprintf(ctx->file, "\"Main List\" -> \"node_%zu\" [label=\"FREE\", style=dotted, color=%s fontcolor=%s, penwidth=1.6];\n",
			ctx->lst->last_free, FREE_COLOR, FREE_COLOR);
}



void graph_script_generate(List* lst)
{
	FILE* graph_script = fopen("graph.dot", "w");	
	GrContext ctx = {.lst = lst, .file = graph_script};	

	//char* buffer = calloc(START_BUFF_CAP, sizeof(char));


	_create_head_info(&ctx);

	fprintf(ctx.file, "\"Main List\" [label=\"{My List | { size=%zu | cap=%zu | last_free=%zu} | {%lg}}\", fillcolor=\"#4f378b\",penwidth=1.4];\n",
			lst->size, lst->capacity, lst->last_free, lst->values[0]);

	size_t pointer = (ctx.lst)->next[0];
	_create_node(&ctx, pointer);
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

	_create_free_list(&ctx);

	_create_main_pointers(&ctx);

	fprintf(ctx.file, "}\n");
	fclose(ctx.file);
}