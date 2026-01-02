p_assembler: main.o pre_assembler/*.o assembler/*.o
	gcc -ansi -Wall -pedantic -o p_assembler main.o pre_assembler/*.o assembler/*.o
main.o: main.c
	gcc -ansi -Wall -pedantic -c main.c
