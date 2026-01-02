


typedef struct Node_mcr
{
	char* line_mcr;
	struct Node_mcr* next;
}Node_mcr;


typedef struct Node_name
{
	char* name;
	int line_beg;
	Node_mcr* list_mcr;
	struct Node_name* next;
}Node_name;

Node_name *get_head_mcr();
Node_name* add_mcr(char* name_mcr);
Node_name *find_mcr(char *name);
Node_mcr* new_Node_mcr(char* line);
void free_list_mcr(Node_name* Node);
void free_mcr(Node_mcr* Node);

