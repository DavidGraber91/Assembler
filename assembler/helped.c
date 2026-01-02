#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pre_assembler/strings.h"
#include "../pre_assembler/list_lines.h"
#include "directive.h"
#include "helped.h"

/*Check which directive*/
int which_dir(char * dir)
{
	ARR_S(s_dir)/*Array of strings for directives*/
	int i;
	for(i = 0; i < NUM_DIRECTIVE && strcmp(dir, s_dir[i]); i++)
       	;
	if(i >= NUM_DIRECTIVE)/*If you did not suitable instruction*/
		return -1;
	return i;
}

/*Check which instruction*/
int which_ins(char* ins)
{
	arr_ins_s(char* arr_ins[]);
	int i;
	for(i = 0; i < NUM_INS && strcmp(arr_ins[i], ins); i++)
	;
	
	if(i == NUM_INS)/*If there is no such instruction*/
		return -1;
	return i;
}

/*Powers up 2 in number*/
int pow2(int num)
{
	if(num == 0)
		return 1;

	return 2 * pow2(num - 1);
}

/*Inserts into the array 'arr' the number 'val' in binary base so that the number of bits are 'size', using the two's complement method*/
int tobits(char * arr, int val, int size)
{
	char* p = NULL;
	int i;
	int max = pow2(size - 1);/*The largest number that can enter in size*/

	if(val > (max - 1) || val < (-1 * max))
	{
		if(!(p = malloc(40)))
			return print_error("The number is out of range", get_line());
		sprintf(p, "The number %d is out of range", val);
		print_error(p, get_line());
		free(p);
		return 0;
	}

	
	for(i = 0; i < size; i++){
		arr[i] = val & BIT;/*Enters 1 if the rightmost bit is on else enter zero*/
		val >>= BIT;
	}

	return 1;
}

/*Inserts into the array 'arr' the number 'val' in binary base so that the number of bits are 'size', unsign*/
void tobitsu(char * arr, int val, int size)
{
	int i;
	if(val > 0)
		for(i = 0; i < size; i++)
		{
			/*Enters 1 if the rightmost bit is on else enter zero*/
			arr[i] = val & BIT;
			val >>= BIT;
		}

	return;
}

/*Gets an array with a number in binary base and converts two cells to int*/
int frombits(char* arr)
{
	int num = 0;
	num |= *(arr + 1);
	num <<= BIT;
	num |= *arr;
	return num;
}

/*Accepts a string and returns the addressing method*/
int get_addr(char* string)
{
	int addr;
	if(*string == '#')
		return IMM;
	
	if(is_regis(string))
		return REG;

	while(*(++string) != '[' && *string)
	;
	if(!*string)/*If is only string*/
		addr = DIRECT;

	else {
		 while(*(++string) != ']' && *string)
		;

		if(!*string || *(++string))
			addr = -1;
		else {
			*--string = '\0';
			addr = IND;
		     }
	     }

	return addr;
}

/*Accepts a string and an address method.
And if is immediate returns the immediate value.
If is register return the register number.
If is index return the index*/
int get_oper(char* string, int addr)
{
	switch(addr)
	{
		case IMM:
			return get_num(++string);
		case REG:
			return *++string - '0';
		case IND:
			
			while(*(++string) != '[' && *string)
			;
			*string = '\0';
			return get_num(++string);
	}
	return 0;
}
		
/*Checks if the addressing methods of the operands match the instruction*/
boolean ch_oper(int val_ins, int source, int target)
{
	boolean error = false;
	switch(val_ins)
	{
		case NOT:
		case CLR:
		case INC:
		case DEC:
		case JMP:
		case BNE:
		case RED:
		case PRN:
		case JSR:
		case RTS:
		case HLT:
			if(source != NO)
				error = true;
			break;
		case MOV:
		case CMP:
		case ADDING:
		case SUB:
			if(source == NO)
				error = true;
			break;
		case LEA:
			if(source != DIRECT && source != IND)
				error = true;
			break;
	}

	switch(val_ins)
	{
		case HLT:
		case RTS:
			if(target != NO)
				error = true;
			break;
		case CMP:
		case PRN:
			if(target == NO)
				error = true;
			break;
		case MOV:
		case ADDING:
		case SUB:
		case LEA:
		case NOT:
		case CLR:
		case INC:
		case DEC:
		case RED:
			if(target == NO || target == IMM)
				error = true;
			break;
		case JMP:
		case BNE:
		case JSR:
			if(target != DIRECT && target != REG)
				error = true;
			break;		
	}
	return !error;
}
