struct node
{
	int lineno = 0;
	struct node *next;
};

struct TrieNode
{
	struct TrieNode *children[26];
	bool isEndOfWord;
	node *line_num;
	int iscap;
	int visited;
};
struct TrieNode *getNode(void);
void get_lines(FILE *, char *);
int leng(char *);
void remove_words(char *, char *);
node* addLineno(node*, int);
char *lentostr(char *, int);
void insert(struct TrieNode *, char *, int, int, int);
int check_new(char *);
char* chop(char *);
void print(node *, FILE *);
void display(struct TrieNode*, char[], int, FILE *);

