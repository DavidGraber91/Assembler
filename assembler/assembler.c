#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../pre_assembler/strings.h"
#include "../pre_assembler/list_lines.h"
#include "assembler.h"
#include "symbols.h"
#include "instr.h"
#include "directive.h"
#include "code.h"
#include "helped.h"

/*First pass over the file, parses line by line*/
int tranA(char* name)
{
	ARR_F(f_dir)/*Array of functions for directives*/
	char* temp = NULL ,*label = NULL, *p_line = NULL, cerror[12] = "illegal ' '";
	char line[MAX_LINE] = {0};
	FILE* file = NULL;
	int end_file, dir;

	if(!(file = fopen((temp = name_file(name, PRE)), "r")))
	{
		fprintf(stderr, "Could not open file\n");
		error(true);
		return 0;
	}

	free(temp);
	
	/*While the line is space*/
	while((end_file = (int)pget_l(line, file)) && (!(temp = aft_space(line)) || *temp == ';'))
		linec(ADD);
	
	while(end_file)
	{
		label = NULL;
		linec(ADD);
		p_line = aft_word(temp);
		
		if(p_line && *p_line  == ':')/*If it is a label*/
		{

			label = temp;	
			*p_line++ = '\0';
			/* If the line is empty after the label*/
			if(!(temp = aft_space(p_line)))
				print_error("A label without a command", get_line());

			p_line = aft_word(temp);
		}
	
		/*temp == the first word after label*/
		if(temp && *temp == '.')/*If it is a directive sentence*/
		{
			if(p_line)
			{
				if(ispunct(cerror[9] = *p_line))
					print_error(cerror, get_line());
				*p_line++ = '\0';
			}

			/*Checking which prompt*/
			if((dir = which_dir(temp + 1)) == -1)
				print_error("Invalid instruction", get_line());
			else f_dir[dir](p_line, label);
		}
		/*If it is not a directive send it to a command function*/
		else comm(temp, label);

		/*next line*/
		while((end_file = (int)pget_l(line, file)) && (!(temp = aft_space(line)) || *temp == ';'))
		linec(ADD);
	}/*end while*/
	
	adding_data();/*Adds couter code to the data symbols*/
	fclose(file);

	return 1;
}

/*A second pass adds encoding to the labels, and fills in the extern list*/
int tranB()
{
	Node_code* node_c = get_head_code()->next;
	Node_sym* sym = NULL;

	while(node_c)
	{
		
		if(node_c->label)
		{
			/*Searches for the label in the label table*/
			if(!(sym = find_sym(node_c->label)) || sym->define)
				return print_error("The label does not exist", node_c->line);
			if(sym->_extern)
			{
				add_extern(node_c->label, ic(GET));
				tobitsu(node_c->val, E, SIZE_ARE);
			}else {
				tobitsu(node_c->val, R, SIZE_ARE);
				tobits(&(node_c->val[SIZE_ARE]), sym->value, SIZE_BIT);
			       }		
		}
		node_c = node_c->next;
		ic(ADD);
	}

	return 1;
}

/*Creates a object file*/
int file_ob(char* name)
{
	Node_code* node = get_head_code()->next;
	int i, cun = ST_IC;
	FILE* file = NULL;
	char* temp = NULL;   
	char encoded[] = {'*', '#', '%', '!'};

                                                           
	file = fopen((temp = name_file(name, OBJECT)), "w");
	if(!file)
	{
		fprintf(stderr, "Could not create object file\n");
		return 0;
	}

	free(temp);
	/*print numbers of code lines and data lines*/
	fprintf(file, "%d %d\n", ic(GET) - ST_IC, dc(GET));

	while(node)
	{
		fprintf(file, "%d\t", cun++); /*print number line*/
		for(i = ALL_BIT - 2; i >= 0; i -= 2)
			putc( encoded[frombits(&node->val[i])], file);/*print code*/
		putc('\n', file);
		
		node = node->next;
	}

	node = get_head_data()->next;
	
	/*print code data*/
	while(node)
        {
                fprintf(file, "%d\t", cun++);
                for(i = ALL_BIT - 2; i >= 0; i -= 2)
                        putc( encoded[frombits(&node->val[i])], file);
                putc('\n', file);

                node = node->next;
        }
	
	fclose(file);
	return 1;
}

/*creates file to entry*/
int file_ent(char* name)
{
	Node_sym *sym, *node = get_head_entry()->next;
	FILE* file = NULL;
	char* temp = NULL;   

	file = fopen((temp = name_file(name, ENTRIES)), "w");
	if(!file)
	{
		fprintf(stderr, "Could not create object file");
		return 0;
	}

	free(temp);

	while(node)
	{
		/*find symbol of label entry*/
		if(!(sym = find_sym(node->label)) || sym->define)
			print_error("The label does not exist", node->value);
		else{
			if(sym->_extern)
			print_error("The label is extern", node->value);

			/*print label of entry and line code*/
                       fprintf(file, "%s\t%d\n", node->label, sym->value);
		      }

		node = node->next;
	}

	return 1;
}

/*creates file to extern*/
int file_ext(char* name)
{
	Node_sym *node = get_head_extern()->next;
	FILE* file = NULL;
	char* temp = NULL;   

	file = fopen((temp = name_file(name, EXTERNALS)), "w");
	if(!file)
	{
		fprintf(stderr, "Could not create object file");
		return 0;
	}

	free(temp);

	/*print the label and the line that is used*/
	while(node)
	{

		fprintf(file, "%s\t%d\n", node->label, node->value);

		node = node->next;
	}

	return 1;
}


