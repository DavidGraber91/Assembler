#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "strings.h"
#include "list_mcr.h"
#include "list_lines.h"
#include "Pre_assembler.h"




Node_name* read_line(FILE* filein, FILE* fileout);
Node_mcr* read_mcr(FILE* file, Node_name* node); 
void write_mcr(FILE* fileout, Node_mcr* list_mcr);



/*Interprets the macros into a file '.am'*/
int pre_assembler(char* nameFile)
{
	FILE* filein = NULL;
	FILE* fileout = NULL;
	Node_name* new_list = NULL;
	Node_mcr* list_mcr = NULL;
	char* temp = NULL;

	/*Open the source file*/
	if(!(filein = fopen((temp = name_file(nameFile, SOURCE)), "r")))
	{
		fprintf(stderr, "Could not open file\n");
		return 0;
	}

	free(temp);

	/*Open the new file*/
	fileout = fopen((temp = name_file(nameFile, PRE)), "w");
	if(fileout == NULL)
	{
		fprintf(stderr, "Could not open file\n");
		return 0;
	}
	

	do
	{
		new_list = read_line(filein, fileout);	
		
		list_mcr = read_mcr(filein, new_list);

		 /*If read macro that puts the line difference in the list*/
		if(list_mcr == NULL)
			add_node_line(source_linec(GET) - new_linec(GET));

		/*If will write a macro that puts the line difference in the list*/
		else
			add_node_line(new_list->line_beg - new_linec(GET));


		write_mcr(fileout, list_mcr);
	
		/*If writed a macro that puts the line difference in the list*/
		if(list_mcr != NULL)
			add_node_line(source_linec(GET) - new_linec(GET));
	
	}
	while(new_list);

	if((error(GET)))
		remove(temp);/*Remove the new file*/

	free(temp);
	free_list_mcr(get_head_mcr());
	new_linec(RESET);

	fclose(fileout);
	fclose(filein);
	return !error(GET);
}

/*read the line from the source file into the new file.
Retrurn new node of name of macro if there is new define macro.
	And a node of a macro if it is a call to macro.
	And NULL at the end of the file*/
Node_name* read_line(FILE* filein, FILE* fileout)
{
	int mcr;
	char line[MAX_LINE];
	char* name_mcr = NULL;
	Node_name*  p_mcr = NULL;



	while(!p_mcr && (fgets(line, MAX_LINE, filein)))
	{
				
		source_linec(ADD);/*Adds to the counter source line*/

		mcr = ismcr(line, &name_mcr, source_linec(GET));


		if(name_mcr)	
			/*If is new macro adds name macro in the list.
				else find if is exists such a macro*/
			p_mcr = (mcr)? add_mcr(name_mcr): find_mcr(name_mcr);
		/*If the line is empty or the name macro is illegal*/ 
		else p_mcr = NULL;
		
		/*If is'nt macro*/
		if(!p_mcr)
		{	
			fputs(line, fileout);
			new_linec(ADD);
		}
	
	}	
	return p_mcr;
}

/*read the macro from the source file into the list.
Returns NULL when it finishes.
And return NULL if node is NULL
And return node macro if that it is'nt new*/
Node_mcr* read_mcr(FILE* file, Node_name* node)
{
	Node_mcr* list = NULL;
	char line[MAX_LINE];
	
	/*If it is the end file*/
	if(!node)
		return NULL;

	/*If it is macro such exists*/
	if(node->list_mcr != NULL)
		return node->list_mcr;

	/*Save the source line in the node of macro*/
	node->line_beg = source_linec(GET);
	source_linec(ADD);

	
	if(isendmcr(fgets(line, MAX_LINE, file), source_linec(GET)))
		return NULL;

	
	if(!(node->list_mcr = new_Node_mcr(line)))
		return (void*)print_error("Memory is full", source_linec(GET));
	list = node->list_mcr;


	while(!isendmcr(fgets(line, MAX_LINE, file), source_linec(GET)))
	{

		source_linec(ADD);
		if(!(list->next = new_Node_mcr(line)))
			return (void*)print_error("Memory is full", source_linec(GET));	
	
		list = list->next;
	}

	source_linec(ADD);
	return NULL;
}


/*write  macro from the list into the new file*/
void write_mcr(FILE* fileout, Node_mcr* list)
{

	while(list != NULL)
	{
		fputs(list->line_mcr, fileout);
		new_linec(ADD);

		list = list->next;
	}

	return;
}








