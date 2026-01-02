#include <stdio.h>
#include <stdlib.h>
#include "../pre_assembler/strings.h"
#include "../pre_assembler/list_lines.h"
#include "code.h"
#include "helped.h"


/*Return the head list data*/
Node_code* get_head_data()
{
	static Node_code head = {{0}};
	return &head;
}

/*Return the head list code*/
Node_code* get_head_code()
{
	static Node_code head = {{0}};
	return &head;
}

/*couonter the data line/
for parameter ADD, Adds one for counter.
for parameter GET, return the counter.
for parameter RESET, Resets the counter to zero*/
int dc(int act)
{
	static int _dc = 0;
	switch(act)
	{
		case ADD:
			return ++_dc;
		case GET:
			return _dc;
		case RESET:
			return _dc = 0;
	}
	
	return -1;
}

/*couonter the code line/
for parameter ADD, Adds one for counter.
for parameter GET, return the counter.
for parameter RESET, Resets the counter to default line value*/
int ic(int act)
{
	static int _ic = ST_IC;
	switch(act)
	{
		case ADD:
			return ++_ic;
		case GET:
			return _ic;
		case RESET:
			return _ic = ST_IC;
	}
	
	return -1;
}

/*Adds node to the end data list, And adds one to the data counter*/ 
int add_data(int value)
{
	static Node_code* end = NULL;
	if(!(get_head_data()->next))/*If the list is reset*/
		end = get_head_data();

	NEW_CODE(end->next)/*add new node*/
	end = end->next;

	dc(ADD);

	/*entry in bits to the arry for node the value*/
	return  tobits(end->val, value, ALL_BIT);
	
}

/*Adds the paranter node to the end code list, And adds one to the code counter*/
void add_code(Node_code* node)
{
	static Node_code* end = NULL;
	if(!(get_head_code()->next))/*If the list is reset*/
		end = get_head_code();
	
	end->next = node;
	ic(ADD);
	end = end->next;
	return;
}

/*free the code list*/
void free_code(Node_code* node)
{
	if(node == NULL)
		return;
	free_code(node->next);
	free(node->next);
	free(node->label);
	node->next = NULL;
	node->label = NULL;
	return;
}	
