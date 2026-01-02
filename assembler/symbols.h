

typedef struct Node_sym{
	char *label;
	int value;
	unsigned int _extern: 1;
	unsigned int define: 1;
	unsigned int data: 1;
	struct Node_sym *next;
	}Node_sym;


Node_sym* get_head_entry();
Node_sym* get_head_sym();
Node_sym* get_head_extern();
Node_sym* add_sym(char* label, int val);
Node_sym* add_entry(char* label);
Node_sym* add_extern(char* label, int val);
Node_sym* find_sym(char* label);
void free_sym(Node_sym *head);
void adding_data();
