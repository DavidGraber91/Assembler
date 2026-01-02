#include <stdio.h>
#include <stdlib.h>
#include "pre_assembler/Pre_assembler.h"
#include "pre_assembler/strings.h"
#include "pre_assembler/list_lines.h"
#include "pre_assembler/list_mcr.h"
#include "assembler/assembler.h"
#include "assembler/symbols.h"
#include "assembler/code.h"

/*Free all lists*/
void free_all()
{
	free_list_mcr(get_head_mcr());
	free_list_lines(get_head_lines());
	free_sym(get_head_sym());
	free_sym(get_head_entry());
	free_sym(get_head_extern());
	free_code(get_head_code());
	free_code(get_head_data());

	ic(RESET);
	dc(RESET);
	source_linec(RESET);
	linec(RESET);
	error(RESET);
}

/*remove files of object*/
void remove_file(char *name)
{
	char* temp = NULL;
	remove((temp = name_file(name, OBJECT)));
	free(temp);
	remove((temp = name_file(name, ENTRIES)));
	free(temp);
	remove((temp = name_file(name, EXTERNALS)));
	free(temp);
	temp = NULL;
}


int main(int argc, char* argv[])
{	
	int ob, ent, ext, i = 1;
	
	for(; i < argc; i++)
	{
	
		
		if(pre_assembler(argv[i]))/*if is'nt fail in pre assembler*/
		{
			linec(RESET);
			tranA(argv[i]);
			ic(RESET);
			tranB();

			ob = file_ob(argv[i]);
		}

		
		if(get_head_entry()->next)
			ent = file_ent(argv[i]);
		if(get_head_extern()->next)
			ext = file_ext(argv[i]);

		/*if is fail remove all*/
		if(error(GET) || !ob || !ent || !ext)
			remove_file(argv[i]);

		free_all();

	}

	return 1;
}
