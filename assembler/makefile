all: symbols.o instr.o helped.o directive.o code.o assembler.o
	
symbols.o: symbols.c
	gcc -ansi -Wall -pedantic -c symbols.c
instr.o: instr.c
	gcc -ansi -Wall -pedantic -c instr.c
helped.o: helped.c
	gcc -ansi -Wall -pedantic -c helped.c
directive.o: directive.c
	gcc -ansi -Wall -pedantic -c directive.c
code.o: code.c
	gcc -ansi -Wall -pedantic -c code.c
assembler.o: assembler.c
	gcc -ansi -Wall -pedantic -c assembler.c

clear:
	rm -r *.o
