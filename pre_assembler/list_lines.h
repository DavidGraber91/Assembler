#define new_linec linec





typedef struct Node_line
{
	int new_line;
	int diff_lines;
	struct Node_line* next;
}Node_line;


int add_node_line(int diff);
void free_list_lines(Node_line* Node);
int source_linec(act);
int linec(act);
Node_line *get_head_lines();
int get_line();
