#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "strings.h"
#include "list_mcr.h"
#include "list_lines.h"
#include "../assembler/symbols.h"
#include "../assembler/helped.h"

/*getting a line
If there are too many characters return 0 else return 1*/
int get_l(char *line, FILE* file)
{
        if(fgets(line , MAX_LINE, file) && line[MAX_LINE - 2] && line[MAX_LINE - 2] != '\n')
		return 0;
	return 1;
}

/*Accepts lines until a valid line is received and advances the line counter accordingly*/
char *pget_l(char *line, FILE * file)
{
	char *temp = NULL;
	line[MAX_LINE - 1] = 0;

	temp = fgets(line , MAX_LINE, file);
	
	/*If the line is invalid*/
	if(temp && line[MAX_LINE - 2] && line[MAX_LINE - 2] != '\n')
	{
		linec(ADD);
		if(!(temp  = aft_space(line)) || *temp != ';')
			print_error("The line is more than 80 characters", get_line());
		line[MAX_LINE - 2] = '\0';/*Resets the cell for retesting*/

		/*Continues to the end of the line*/
		while(!get_l(line, file))
			line[MAX_LINE - 2] = '\0';

		
		return pget_l(line, file);/*Recursive call to the next line*/
	}
	
	return temp;/*retrun the line*/
}

/*Returns a pointer to the first character after the space*/
char* aft_space(char* line)
{
	line--;

	while(isspace(*(++line)))
        ;

	return (*line)? line: NULL;
}

/*Returns a pointer to the first character after the word*/
char *aft_word(char* line)
{
	line--;
	while(!isspace(*(++line)) && *line != ',' && *line != ';' && *line != ':')
	;

	return (*line)? line: NULL;	
}

/*Returns a pointer to the first character after the character c
And print error if missing character c*/
char *aft_wordc(char* line, char c)
{
	char temp[11] = "missing ' '";
	char k = 0;

	line = aft_word(line);
	
	if(line)/*if there is nore character*/
	{
		k = *line;
		*line = '\0';
	}/*else, k == 0*/

	if(isspace(k))
		k = (line = aft_space(++line))? *line: 0;
	if(k == 0)/*it is end line*/
		return NULL;
	if(k != c)/*if there more characters*/
	{
		temp[9] = c;
		print_error(temp, get_line());

	}

	return ++line;/*Return the next character*/
}	
	
/*Checks if the first word in the line is 'mcr'
lucrative name of macro into name_mcr
Return if is macro*/
boolean ismcr(char* line, char** name_mcr, int num_line)
{
	int mcr = false;
	
	/*if the first word is 'mcr'*/
        if((line = aft_space(line)) && strncmp(line, "mcr", 3) == 0)
        {
		mcr = true;
                *name_mcr = aft_space(line + 3);
		
		if((line = (aft_word(*name_mcr))))
		{
			if(!isspace(*line))
				line++;

			*line = '\0';
		}

		if(!ch_label(*name_mcr))
			mcr = (int)(*name_mcr = (void*)print_error("Illegal Macro name", num_line));
		if((aft_space(++line)))/*If there is more character after define macro*/
			mcr = (int)(*name_mcr = (void*)print_error("characters after a macro statement", num_line));

        }/*If is empty line entry NULL. 
	   If is'nt macro, entry the first worde to chack if is macro*/
	else *name_mcr = line; 

	return mcr;
}


/*Checks if the first word in the line is 'mcr'*/
boolean isendmcr(char* line, int num_line)
{
	boolean endmcr;
	line = aft_space(line);
	endmcr = (strncmp(line , "endmcr", 6) == 0)? true: false;
	if(endmcr && aft_space(line + 6))
		print_error("characters after 'endmcr'", num_line);
	return endmcr;
}


/*print error and changes the flag error to true*/
int print_error(char *_error, int line)
{
	fprintf(stderr, "Error: in line %d: %s\n", line, _error);
	
	error(true);
	return 0;
}




/*Returns the filename if the appropriate extension*/
char *name_file(char* name, char* type)
{
	char *temp = NULL;
	if(!(temp = malloc(strlen(name) + strlen(type) +1 )))
		fprintf(stderr, "The memory is full\n");

	else{
		strcpy(temp, name);
		strcat(temp, type);
	}
	
	return temp;
}

/*checking if the name of label is legal*/
boolean ch_label(char* label)
{
	int i = 0;
	
	if(isalpha(label[i]))
		while(label[++i] && isalnum(label[i]) && i < 31)
		;
	if(!label[i] && !is_regis(label))/*If arrived to '\0'*/
		if(which_dir(label) == -1 && which_ins(label) == -1)
			return true;
		
	return false;
}

/*Checks if string it is the name of a register*/
boolean is_regis(char* string)
{
	char *r[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "PC"};
	int i = 0;

	for(i = 0 ;i < 8 && strncmp(string, r[i], 2); i++)
	;
	if(i >= 8)
		return false;
		
	return true;
}

/*flag error*/
int error(act _act)
{
	static int error = 0;

	switch (_act)
	{
		case true:  return error = true;

		case GET:  return error;

		case RESET: return error = false;
	}
	
	return -1;
}

/*Returns the number of string*/
int get_num(char *string)
{
	char* p= NULL;
	Node_sym* node = NULL;
	int num;
	
	if(!(*string))/*The string is empty*/
		return print_error("numberless", get_line());

	if(!isdigit(*string) && (*string) != '-' && (*string) != '+')/*Is define*/
	{
		if((node = find_sym(string)) && node->define)
			return node->value;
		else return print_error("define does not exist" , get_line());
	}
		
	num = strtol(string, &p, 10);


	if(*p)/*there is more character after digit*/
	{
		if(!(p = malloc(strlen(string) + 20)))
			return print_error("invalid number", get_line());
		sprintf(p, "%s is an invalid number", string);
		print_error(p, get_line());
		free (p);
	}

	
	return num;
}
	


