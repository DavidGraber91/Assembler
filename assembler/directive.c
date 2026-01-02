#include <stdio.h>
#include <string.h>
#include "../pre_assembler/strings.h"
#include "../pre_assembler/list_lines.h"
#include "directive.h"
#include "symbols.h"
#include "code.h"

/*Encodes the values in the list and adds to the data table.
Return 1 in success and 0 else*/
int dataf(char *line, char* label)
{
	int suc = true;
	char* temp = NULL;
	Node_sym* node = NULL;

	if(!(line = aft_space(line)))/*if the line is empty*/
		suc = print_error("No parameters", get_line());

	if(label)/*If there is a label*/
		if((node = add_sym(label, dc(GET))))
			node->data = true;

	while(line)/*while there is more parameters*/
	{
		if(!(line = aft_space(line)))
			print_error("',' at the end of a line", get_line());
		else
		{
			(line = aft_wordc((temp = line), ','));
			add_data(get_num(temp));/*Encodes and adds*/
		}	
	}

	return suc;
}

/*Encodes the values in the list and adds to the data table.
Return 1 in success and 0 else*/
int stringf(char *line, char *label)
{
	char* temp = NULL;
	Node_sym* node = NULL;
	int suc = true;
                       
	temp = line + strlen(line);/*Pointer to the end of the line*/

	if(!(line = aft_space(line)))/*if the line is empty*/
		suc = print_error("No parameters", get_line());

	if(line && *line != '"')
		suc =  print_error("Extra characters before '\"'", get_line());

	while(*(--temp) != '"' && temp != line)/*Pointer to the end of the string*/
	;
	if(temp == line)
		suc = print_error("Missing '\"'", get_line());

	if(aft_space(temp + 1))
		suc = print_error("Extra characters after '\"'", get_line());

	if(label)
		if((node = add_sym(label, dc(GET))))
			node->data = true;

	while(++line != temp)/*Adds all the characters between the extreme decimals*/
		add_data(*line);

	add_data('\0');/*Adds end string*/
 	
	return suc;

}

/*Adds the label to the entry table*/
int entryf(char *line, char *label)
{
	char* temp = NULL;

	if(label)
		fprintf(stderr, "Warning: in line %d: Label in entry\n", get_line());
	if(!(line = aft_space(line)))
		return print_error("No parameters", get_line());

	if((temp = aft_word(line)))
	{
		*temp = '\0';
		if(aft_space(++temp))
			return print_error("Extra characters after label", get_line());
	}
	add_entry(line);

	
	return 1;
}

/*Adds the label with the default value zero to the symbol table*/
int externf(char *line, char *label)
{
	char* temp = NULL;
	Node_sym* node = NULL;

        if(label)
                fprintf(stderr,"Warning: in line %d: Label in entry\n", get_line());

        if(!(line = aft_space(line)))
                return print_error("No parameters", get_line());

        if((temp = aft_word(line)))
	{
                *temp = '\0';
		if(aft_space(++temp))
			return print_error("Extra characters after label", get_line());
	}

        if((node = add_sym(line, DEF)))
		node->_extern = true;
	
	return 1;

}

/*Adds to the symbol table define*/
int definef(char *line, char *label)
{
	char* temp = NULL;
	char* num = NULL;
	Node_sym* node = NULL;

	if(label)
		print_error("label in the define line", get_line());

	if(!(line = aft_space(line)))/*line holds the definition name*/
		print_error("No parameters", get_line());

	else if(!(temp = aft_wordc(line, '=')) || !(num = aft_space(temp)))
		return print_error("No value", get_line());
	/*num holds the string value*/

	if((temp = aft_word(num)))
	{
		*temp++ = '\0';
		if(aft_space(temp))
			 print_error("Extra characters in the end line", get_line());
	}

	if((node = add_sym(line, get_num(num))))
		node->define = true;

	return 1;
}
