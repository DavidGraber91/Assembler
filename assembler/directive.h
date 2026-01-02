#define NUM_DIRECTIVE 5

#define ARR_F(temp) int(*temp[])(char* line, char* label) = {dataf, stringf, entryf, externf, definef};
#define ARR_S(temp) char *temp[] = {"data", "string", "entry", "extern", "define"};





int dataf(char *line, char *label);
int stringf(char *line, char *label);
int entryf(char *line, char *label);
int externf(char *line, char *label);
int definef(char *line, char *label);
