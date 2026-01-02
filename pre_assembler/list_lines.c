#include <stdlib.h>
#include <stdio.h>
#include "strings.h"
#include "list_lines.h"
#include "list_mcr.h"

Node_line* new_Node_line(int line_new,int diff);

/*void print(Node_line* head)
{
	int i;
	Node_line* temp;
	if(head == NULL)
		return;
	for(i = 2; i<25;i += 3){
		temp = head;
		while(temp->next != NULL && i > temp->next->new_line)
			temp = temp->next;
		if(temp != NULL)		
			printf("%d\t%d\n", i, i + temp->diff_lines);
	}
	return;

}*/

/*Line counter of the source file*/
int source_linec(act _act)
{
	static int source_line = 0;
	switch(_act)
	{
		case GET:
			return source_line;
		case ADD:
			return ++source_line;
		case RESET:
			return source_line = 0;
	}
	return -1;
}

/*Line counter (and line counter new file)*/
int linec(act _act)
{
	static int line = 0;
	switch(_act)
	{
		case GET:
			return line;
		case ADD:
			return ++line;
		case RESET:
			return line = 0;
	}
	return -1;
}

/*Returns the head of the list of line*/
Node_line *get_head_lines()
{
	static Node_line head = {0};
	return &head;
}

/*Adds a node line to the end of the list*/
int add_node_line(int diff)
{
	static Node_line *end_list = NULL;/*Saves the end of the list*/
	if(!(get_head_lines()->next))
		end_list = get_head_lines();


	if(!(end_list->next = new_Node_line(new_linec(GET), diff)))
		return print_error("Memory is full", source_linec(GET));
			
	end_list = end_list->next;
	return 1;
}


/*adds new node of macro with the value 'name'*/
Node_line* new_Node_line(int line_new, int diff)
{
	Node_line* temp = malloc(sizeof(Node_line));
	temp->new_line = line_new;
	temp->diff_lines = diff;
	temp->next = NULL;
	return temp;
}

/*Frees the list line*/
void free_list_lines(Node_line* Node)
{
	if(Node == NULL)
		return;
	free_list_lines(Node->next);
	free(Node->next);
	Node->next = NULL;
	return;
}

/*Returns the line of the source file*/
int get_line()
{
	Node_line *temp = get_head_lines();
	int line = linec(GET);

	while(temp->next != NULL && line > temp->next->new_line)
		temp = temp->next;
				
	return line + temp->diff_lines;
}
