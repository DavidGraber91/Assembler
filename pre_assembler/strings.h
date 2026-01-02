#define SOURCE ".as"
#define PRE ".am"
#define OBJECT ".ob"
#define ENTRIES ".ent"
#define EXTERNALS ".ext"

#define MAX_LINE 82
#define DEF 0

typedef enum {GET, ADD, RESET} act;
typedef enum {false, true} boolean;

int get_l(char *line, FILE *file);
char *pget_l(char *line, FILE* file);
char* aft_space(char* line);
char *aft_word(char *line);
char *aft_wordc(char* line, char c);
boolean isendmcr(char* line, int num_line);
boolean ismcr(char* line, char** name_mcr, int num_line);
boolean ch_label(char* label);
boolean is_regis(char* string);
int print_error(char *error, int line);
char *name_file(char* name, char *type);
int error(act _act);
int get_num(char* string);
