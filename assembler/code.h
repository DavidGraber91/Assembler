#define ALL_BIT 14
#define ST_IC 100
#define SIZE_BIT 12


#define NEW_CODE(node) node = calloc(sizeof(Node_code), 1);\
	if(!node)\
		return print_error("Memory is full", get_line());

typedef struct Node{
		char val[ALL_BIT];
		char* label;
		int line;
		struct Node* next;
		}Node_code;

typedef enum{A, E, R}ARE;

Node_code* get_head_data();
Node_code* get_head_code();
int add_data(int);
void add_code(Node_code*);
int dc(int act);
int ic(int act);
void free_code(Node_code* node);

