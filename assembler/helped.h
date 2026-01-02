#define BIT 1
#define SIZE_ARE 2
#define SIZE_SOURCE_A 2
#define SIZE_TARGET_A 2
#define SIZE_OPCODE 4
#define SIZE_SOURCE 3
#define SIZE_TARGET 3

#define arr_ins_s(temp) temp = {"mov", "cmp", "add", "sub", "not", "clr", \
"lea", "inc", "dec", "jmp", "bne", "red", "prn", "jsr" , "rts", "hlt"}

typedef enum {NO = -1, IMM, DIRECT, IND, REG}addr; 
typedef enum {MOV, CMP, ADDING, SUB, NOT, CLR, LEA, INC, DEC, JMP, BNE, RED, PRN,\
JSR, RTS, HLT, NUM_INS} instruction;

int which_dir(char * dir);
int which_ins(char* ins);
int pow2(int);
int tobits(char* arr, int val, int size);
void tobitsu(char* arr, int val, int size);
int get_addr(char* string);
int get_oper(char* string, int addr);
boolean ch_oper(int val_ins, int source_addr, int target_addr);
int frombits(char*);

