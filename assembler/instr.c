#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "../pre_assembler/strings.h"
#include "../pre_assembler/list_lines.h"
#include "symbols.h"
#include "code.h"
#include "instr.h"
#include "helped.h"

void oper(char* line, int* sour_addr,  char** sour_s, int* tar_addr, char** tar_s);

/*Parses the continuation of a command line.
and encodes the lines of code*/
int comm(char* line, char* label)
{
	char* temp , *source_oper, *target_oper;
	int val_ins, source_addr,  target_addr;
	Node_code* node = NULL;
 	temp =  source_oper = target_oper = NULL;
	source_addr = target_addr  = NO;

	NEW_CODE(node)

	if(!(line = aft_space(line)))/*If no more character after coomand*/
		print_error("No paramter", get_line());

	else if((temp = aft_word(line)))/*If there is more character entry '\0'*/
		{
			if(ispunct(*temp))
				print_error("Incorrect punctuation", get_line());	
			*temp++ = '\0';
		}

	/*Checks which instruction*/
	if((val_ins = which_ins(line)) == -1)
		print_error("wrong word", get_line());

	/*If there is more character sender to receive operators*/
	if(temp && (line = aft_space(temp)))
		oper(line, &source_addr,  &source_oper, &target_addr, &target_oper);

	/*Checks if operators match the instruction*/
	if(!ch_oper(val_ins, source_addr, target_addr))
		print_error("Operators do not match the command", get_line());

	/*if there is label adds symbol*/
	if(label)	
		add_sym(label, ic(GET));

	/*Encode the first line*/
	tobitsu((temp = &(node->val[SIZE_ARE])), target_addr, SIZE_TARGET_A);
	tobitsu((temp = temp + SIZE_TARGET_A), source_addr, SIZE_SOURCE_A);
	tobitsu((temp + SIZE_SOURCE_A), val_ins, SIZE_OPCODE);
	add_code(node);

	/*Sends the rest of the line to the coder*/
	operand_line(source_addr, source_oper, target_addr, target_oper);
	
		
	return 1;
}

/*Inserts into the appropriate variables the operands and their type*/
void oper(char* line, int* sour_addr,  char** sour_oper, int* tar_addr, char** tar_oper)
{
	char* temp = NULL;
	temp = aft_wordc((*tar_oper = line), ',');

	if((*tar_addr = get_addr(*tar_oper)) == -1)
		print_error("missin ']'", get_line());

	if(temp && (line = aft_space(temp)))
	{
		if((temp = aft_word(line)))
		{
			if(ispunct(*temp))
				print_error("Invalid punctuation mark", get_line());
			*temp++ = '\0';
			if(aft_space(temp))
				print_error("Too many arguments", get_line());
		}

		*sour_addr = *tar_addr;
		*sour_oper = *tar_oper;
		*tar_oper = line;
		if((*tar_addr = get_addr(*tar_oper)) == -1)
			print_error("missin ']'", get_line());
			
	}

}

/*Coded according to the type of operators*/
int operand_line(int sour_addr,  char* sour_s, int tar_addr, char* tar_s)
{
	Node_code* node = NULL;
	int sour_val, tar_val;

	/*entry the value of operators*/
	sour_val = get_oper(sour_s, sour_addr);
		if(tar_addr == REG)
		tar_val = get_oper(tar_s, tar_addr);

	/*If no operators*/
	if(sour_addr == NO && tar_addr == NO)
		return 1;

	/*If both operators are registers, one line of code is added*/
	if(sour_addr == REG && tar_addr == REG)
	{
		NEW_CODE(node)
		tobitsu(node->val, A, SIZE_ARE);
		tobitsu(&(node->val[SIZE_ARE]), tar_val, SIZE_TARGET);
		tobitsu(&(node->val[SIZE_ARE + SIZE_TARGET]), sour_val, SIZE_SOURCE);
		add_code(node);
		return 1;
	}

	/*An source operant staring coder*/
	switch(sour_addr)
	{
	case REG:
		NEW_CODE(node)
		tobitsu(node->val, A, SIZE_ARE);
		tobitsu(&(node->val[SIZE_ARE + SIZE_TARGET]), sour_val, SIZE_SOURCE);
		add_code(node);
		break;

	case IMM:
		NEW_CODE(node)
		tobitsu(node->val, A, SIZE_ARE);
		tobits(&(node->val[SIZE_ARE]), sour_val, SIZE_BIT);
		add_code(node);
		break;
	case DIRECT:
		NEW_CODE(node)
		if(!(node->label = malloc(strlen(sour_s))))
			return print_error("Memory is full", get_line());
		strcpy(node->label, sour_s);
		node->line = get_line();
		add_code(node);
		break;
	case IND:
		NEW_CODE(node)
		if(!(node->label = malloc(strlen(sour_s))))
			return print_error("Memory is full", get_line());
		strcpy(node->label, sour_s);
		node->line = get_line();
		add_code(node);
		NEW_CODE(node)
		tobitsu(node->val, A, SIZE_ARE);
		tobits(&(node->val[SIZE_ARE]), sour_val, SIZE_BIT);
		add_code(node);
	}

	if(tar_addr == REG)
	{
		NEW_CODE(node)
		tobitsu(node->val, A, SIZE_ARE);
		tobitsu(&(node->val[SIZE_ARE]), tar_val, SIZE_TARGET);
		add_code(node);
		return 1;
	}
	
	/*calls the method again for a target operator*/		
	operand_line(tar_addr, tar_s, NO, NULL);
	
	return 1;
}

