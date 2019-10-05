#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
void get_lines(FILE *ptr, char *s)
{
	char c; int i = 0;
	c = fgetc(ptr);
	while (c != EOF)
	{
		s[i] = c;
		c = fgetc(ptr);
		i++;
	}
	s[i] = '\0';
}
int leng(char *s)
{
	int c = 0;
	for (int i = 0; s[i] != '\0'; i++)
		c++;
	return c;
}

void remove_words(char *str, char *toRemove)
{
	int i, j, stringLen, toRemoveLen;
	int found;

	stringLen = strlen(str);
	toRemoveLen = strlen(toRemove);


	for (i = 0; i <= stringLen - toRemoveLen; i++)
	{
		found = 1;
		for (j = 0; j < toRemoveLen; j++)
		{
			if (str[i + j] != toRemove[j])
			{
				found = 0;
				break;
			}
		}
		if (str[i + j] != ' ' && str[i + j] != '\t' && str[i + j] != '\n' && str[i + j] != '\0')
		{
			found = 0;
		}
		if (found == 1)
		{
			for (j = i; j <= stringLen - toRemoveLen; j++)
			{
				str[j] = str[j + toRemoveLen];
			}

			stringLen = stringLen - toRemoveLen;
			i--;
		}
	}
}

node* addLineno(node* root, int lno)
{
	if (root == NULL)
	{
		root = (node*)malloc(sizeof(node));
		root->lineno = lno;
		root->next = NULL;
		return root;
	}
	if (root->lineno == lno)
		return root;
	node *t = (node*)malloc(sizeof(node));
	t->lineno = lno;
	t->next = root;
	root = t;
	return root;
}
struct TrieNode *getNode(void)
{
	struct TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;
	pNode->line_num = NULL;
	for (int i = 0; i < 26; i++)
		pNode->children[i] = NULL;

	return pNode;
}
char *lentostr(char *str, int line)
{
	int len, is = 0, n = line, c = line, i = 0;

	if (str == NULL)
	{
		is = 1;
		len = 0;
	}
	else
	{
		len = leng(str);
	}
	while (c != 0)
	{
		n = line % 10;
		if (str == NULL)
			str[i] = n + '0';
		else
			str[len + i + 1] = n + '0';
		c = c / 10;
		i++;
	}
	if (is){
		str[i] = ',';
		str[i + 1] = '\0';
	}
	else
	{
		str[len + i + 1] = ',';
		str[len + i + 2] = '\0';
	}return str;
}
void insert(struct TrieNode *root, char *key, int line, int iscap, int visit)
{
	struct TrieNode *pCrawl = root;

	for (int i = 0; key[i] != '\0'; i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}
	pCrawl->visited = visit;
	pCrawl->isEndOfWord = true;
	if (line)
		pCrawl->line_num = addLineno(pCrawl->line_num, line);
	pCrawl->iscap = iscap;
}
char* chop(char *string)
{
	int i, len;
	len = strlen(string);
	char *newstring;

	newstring = (char *)malloc(len - 1);

	int ind = 0;
	for (i = 0; i <= strlen(string) - 1; i++)
	{
		if (string[i] == '\n'){
			ind;
			// ind++;
		}
		else
		{
			newstring[ind] = string[i];
			ind++;
		}
	}
	newstring[ind] = '\0';
	return newstring;
}
void print(node *root, FILE *fp)
{
	if (!root)
		return;
	char num[10];
	_itoa(root->lineno, num, 10);
	fputs(num, fp);
	if (root->next != NULL)
		fputc(',', fp);
	print(root->next, fp);
}
void display(struct TrieNode* root, char str[], int level, FILE *fp)
{
	if (root->isEndOfWord != 0)
	{
		str[level] = '\0';
		if (root->visited == 0){
			fputs(str, fp);
			fputs(":", fp);
		}
		char *lno = (char*)malloc(sizeof(char) * 150);
		if (root->visited == 0)
		{
			print(root->line_num, fp);
			fputs("\n", fp);
		}
	}
	int i;
	for (i = 0; i < 26; i++)
	{
		if (root->children[i])
		{
			str[level] = i + 'a';
			display(root->children[i], str, level + 1, fp);
		}
	}
}
int check_new(char *s)
{
	int count = 0;
	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '\n')
			count++;
	}
	return count;
}