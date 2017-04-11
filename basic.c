#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gettoken.h"
extern void bc_print(void);
extern void bc_input(void);
extern double expression(void);
double hensuu[26];
void main(int argc, char *argv[])
{
char	*list[100];
char	buff[256];
FILE	*fp;
int	now = 0;
int	last;
int	valnum;

if(argc != 2) {
	printf("please indicate file name!\n");
	exit(1);
}

if((fp = fopen(argv[1], "r")) == NULL) {
	printf("I do not file open...\n");
	exit(1);
}

while(fgets(buff, 256, fp) != NULL) {
	list[now] = (char *)malloc(strlen(buff) + 1);
	if(list[now] == NULL) {
		printf("there is not data room.\n");
		exit(1);
	}
	strcpy(list[now], buff);
	++ now;
}
last = now;
fclose(fp);
for(now = 0; now < last; ++now){
	strcpy(gt_line, list[now]);
	get_token();
	if(!strcmp("END", token)){
		printf("\x1b[37m");
		printf("✔ \n");
		printf("\x1b[0m");
		exit(1);
	}
	else if(!strcmp("INPUT",token))
		bc_input();
	else if(!strcmp("PRINT",token))
		bc_print();
	else if(!strcmp("FOR",token))
		printf("FOR order\n");
	else if(!strcmp("NEXT",token))
		printf("NEXT order\n");
	else if(!strcmp("IF",token))
		printf("IF order\n");
	else if(!strcmp("ELSEIF",token))
		printf("ELSEIF order\n");
	else if(!strcmp("ELSE",token))
		printf("ELSE order\n");
	else if(!strcmp("ENDIF",token))
		printf("ENDIF order\n");
	else if(!strcmp("REM",token))
		printf("REM order");
	else if(isalpha(*token)){
		valnum = *token - 'A';
		get_token();
		if(*token != '='){
			printf("代入分が正しくありません\n");
			exit(1);
		}
		get_token();
		hensuu[valnum] = expression();
	}else
		printf("do not order!\n");

	}
}
