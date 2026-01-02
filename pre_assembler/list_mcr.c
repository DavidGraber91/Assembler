#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "strings.h"
#include "list_mcr.h"
#include "list_lines.h"

Node_name* new_Node_name(char* name);

/*Returns the head of the list of macros*/
Node_name *get_head_mcr()
{
	static Node_name head = {NULL};
	return &head;
}

/*Adds a macro to the end of the list*/
Node_name* add_mcr(char* name)
{
	static Node_name *end_list = NULL;/*Saves the end of the list*/
	if(!(get_head_mcr()->next))
		end_list = get_head_mcr();

	if(find_mcr(name))/*If a macro already exists*/
		print_error("The macro name already exists", source_linec(GET));
	

	if(!(end_list->next = new_Node_name(name)))
		print_error("Memory is full", source_linec(GET));
	else end_list = end_list->next;
	
	return end_list;
}

/*Looking for a macro.
Returns the node if found and returns NULL if not*/
Node_name *find_mcr(char *name)
{
	char temp_c;
	char *p_temp = NULL;
	Node_name *temp = get_head_mcr()->next;

	/*Inserts a '\0' at the end of the word*/
	if((p_temp = aft_word(name))){
		temp_c = *p_temp;
		*p_temp = '\0';
		}


	while(temp != NULL && strcmp(name, temp->name))
		temp = temp->next;

	if(p_temp) *p_temp = temp_c; /*return the character*/

	return temp;
}


/*adds new node of macro with the value 'name'*/
Node_name* new_Node_name(char* name)
{
	Node_name* temp = malloc(sizeof(Node_name));
	temp->name = malloc(strlen(name) + 1);
	strcpy(temp->name, name);
	temp->next = NULL;
	temp->list_mcr = NULL;
	return temp;
}	

/*Frees the list of macro moles with the macros*/
void free_list_mcr(Node_name* Node)
{
	if(Node == NULL)
		return;
	
	free_list_mcr(Node->next);
	free(Node->next);
	free_mcr(Node->list_mcr);
	free(Node->name);
	Node->name = NULL;
	Node->next = NULL;
	return;
}

/*Frees the macros*/
void free_mcr(Node_mcr* Node)
{
	if(Node == NULL)
		return;
	free_mcr(Node->next);
	free(Node->line_mcr);
	free(Node);
	return;
}




/*Adds node of line of macro*/
Node_mcr* new_Node_mcr(char* line)
{
	Node_mcr* temp;
	if(!(temp = malloc(sizeof(Node_mcr))))
		return NULL;
	temp->line_mcr = malloc(strlen(line) + 1);
	strcpy(temp->line_mcr, line);
	temp->next = NULL;
	return temp;
}
