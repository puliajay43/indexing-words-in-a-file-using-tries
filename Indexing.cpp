#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CHAR_SIZE 26
#include "Header.h"
int main()
{
	FILE *fp = fopen("Bohemia.txt", "r");
	FILE *rp = fopen("stopWordsCleaned.txt", "r");
	FILE *wp = fopen("result.txt", "w");
	char *sp = "a"; int i;
	char *re = (char *)malloc(sizeof(char) * 50000);
	char *he = (char *)malloc(sizeof(char) * 600);
	char *te = (char *)malloc(sizeof(char) * 600);
	get_lines(fp, re);
	get_lines(rp, he);
	int line = 1,k;
	int iscap;
	TrieNode *head=getNode();
	char *buf=(char *)malloc(100);
	char *temp = (char *)malloc(100);
	buf = strtok(re, ".,-' \"?!@#$%^&*(<>)/|;:=+_`~\n");
	char *s = (char *)malloc(25);
	while (buf != NULL){
		if (buf[0] >= '0' && buf[0] <= '9'){
			buf = strtok(NULL, ".,-' \"?!@#$%^&*(<>)/|;:=+_`~");
		}
		else{
			if (k = check_new(buf)){
				buf = chop(buf);
				temp = "h i";
				if (buf[0] =='\0' ){ //&&buf[1] == '\0'){
					buf = strtok(NULL, ".,-' \"?!@#$%^&*(<>/)|;:=+_`~");
					line = line + k;
				}
				else{
					for (i = 0; i <= strlen(buf); i++){
						if (buf[i] >= 65 && buf[i] <= 90)
						{
							buf[i] = buf[i] + 32;
							iscap = 1;
						}
					}
					insert(head, buf, line, iscap, 0);
				}
			}
			else{
				iscap = 0;
				//buf = strtok(NULL, ".,-' \"?!@#$%^&*(<>/)|;:=+_`~");
				for (i = 0; i <= strlen(buf); i++){
					if (buf[i] >= 65 && buf[i] <= 90)
					{
						buf[i] = buf[i] + 32;
						iscap = 1;
					}
				}
				insert(head, buf, line, iscap, 0);
				//head->visited = 0;
				buf = strtok(NULL, ".,-' \"?!@#$%^&*(<>/)|;:=+_`~");
			}
		}
	}
	
	char *buf1 = (char *)malloc(100);
	buf1 = strtok(he, ".,-' \n");
	char *s1 = (char *)malloc(25);
	iscap = 0;
	while (buf1 != NULL){
		insert(head, buf1, line, iscap,1);
		//head->visited = 0;
		buf1 = strtok(NULL, ".,-' \n\"");

	}
	display(head, s, 0,wp);
	getchar();
	system("pause");
}