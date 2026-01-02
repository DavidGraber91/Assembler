#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbols.h"
#include "../pre_assembler/strings.h"
#include "../pre_assembler/list_lines.h"
#include "code.h"

/*Returns the head of the symbol list*/
Node_sym *get_head_sym()
{
	static Node_sym head = {NULL};
	return &head;
}

/*Returns the head of the entry list*/
Node_sym* get_head_entry()
{
	static Node_sym head = {NULL};
	return &head;
}

/*Returns the head of the extern list*/
Node_sym* get_head_extern()
{
	static Node_sym head = {NULL};
	return &head;
}

/*make new node sym*/
Node_sym* add_node(char* label, int val)
{
	Node_sym* temp = calloc(1, sizeof(Node_sym));
	if(!temp)
		return (void*)print_error("Memmory if full", get_line());

	if(!(temp->label = malloc(strlen(label))))
		print_error("Memory is full", get_line());
	strcpy(temp->label, label);
	temp->value = val;
	return temp;
}

/*Adds new node entry to the end with the zero value*/
Node_sym* add_entry(char* label)
{
	static Node_sym* end = NULL;
	if(!(get_head_entry()->next))
		end = get_head_entry();

	end->next = add_node(label, DEF);
	end = end->next;
	return end;
}

/*Adds new node entry to the end*/
Node_sym* add_extern(char* label, int val)
{
	static Node_sym* end = NULL;
	if(!(get_head_extern()->next))
		end = get_head_extern();

	end->next = add_node(label, val);
	end = end->next;
	return end;
}

/*find label in the symbol list.
Return the node of the label and NULL if not found*/
Node_sym *find_sym(char* label)
{
	Node_sym *temp = (get_head_sym())->next;
	
	while(temp && strcmp(temp->label, label))
		temp = temp->next;

	return temp;
} 

/*Adds new node entry to the end if the label not exists*/
Node_sym* add_sym(char* label, int val)
{
	static Node_sym* end = NULL;
	if(!(get_head_sym()->next))
		end = get_head_sym();

	if(!ch_label(label))
		print_error("Invalid label name", get_line());

	else if(find_sym(label))
		print_error("The label name is already defined", get_line());

	if((end->next = add_node(label, val)))
		end = end->next;
	return end;
}

/*Adds counter code line to the symbols of data*/
void adding_data()
{
	Node_sym* node = get_head_sym()->next;
	int _ic = ic(GET);
	
	while(node)
	{
		if(node->data)
			node->value += _ic;
		node = node->next;
	}
	return;
}

/*free list*/
void free_sym(Node_sym* node)
{
	if(node == NULL)
		return;
	free_sym(node->next);
	free(node->next);
	free(node->label);
	node->next = NULL;
	node->label = NULL;
	return;
}
