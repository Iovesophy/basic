#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gettoken.h"
extern void bc_print(void);
extern void bc_input(void);
extern int  bc_for(int);
extern int  bc_next(int);
extern double logic(void);
double hensuu[26];
int	for_ln  = -1;
int	next_ln = -1;
void main(int argc, char *argv[])
{
char	*list[100];
char	buff[256];
FILE	*fp;
int	now = 0;
int	last;
int	valnum;

if(argc != 2) {
	printf("Please indicate file name!\n");
	exit(1);
}

if((fp = fopen(argv[1], "r")) == NULL) {
	printf("BASIC do not file open...\n");
	exit(1);
}

while(fgets(buff, 256, fp) != NULL) {
	list[now] = (char *)malloc(strlen(buff) + 1);
	if(list[now] == NULL) {
		printf("There is not data room.\n");
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
		now = bc_for(now);
	else if(!strcmp("NEXT",token))
		now = bc_next(now);
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
		hensuu[valnum] = logic();
		}
	else if(!strcmp("\n",token))
		continue;
	else
		printf("do not order!\n");
	}
}
