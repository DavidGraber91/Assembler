all: Pre_assembler.o list_mcr.o list_lines.o strings.o

Pre_assembler.o: Pre_assembler.c
	gcc -ansi -Wall -pedantic -c Pre_assembler.c
list_mcr.o: list_mcr.c
	gcc -ansi -Wall -pedantic -c list_mcr.c
list_lines.o: list_lines.c
	gcc -ansi -Wall -pedantic -c list_lines.c
strings.o: strings.c
	gcc -ansi -Wall -pedantic -c strings.c
clear:
	rm -r *.o
