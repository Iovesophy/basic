#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gettoken.h"
extern void bc_print(void);
extern void bc_input(void);
extern int  bc_for(int);
extern int  bc_next(int);
extern int  bc_if(int);
extern int  bc_elseif(int);
extern int  bc_else(int);
extern int  bc_endif(int);
extern double logic(void);
double hensuu[26];
int	for_ln  = -1;
int	next_ln = -1;
int	if_flag = -1;
char	*list[100];
int	last;

void main(int argc, char *argv[])
{
char	buff[256];
FILE	*fp;
int	now = 0;
int	valnum;

if(argc != 2) {
	printf("Error : Please indicate file name!\n");
	exit(1);
}

if((fp = fopen(argv[1], "r")) == NULL) {
	printf("Error : BASIC do not file open...\n");
	exit(1);
}

while(fgets(buff, 256, fp) != NULL) {
	list[now] = (char *)malloc(strlen(buff) + 1);
	if(list[now] == NULL) {
		printf("Error : There is not data room.\n");
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
	if(!strcmp("EXIT", token)){
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
		now = bc_if(now);
	else if(!strcmp("ELSEIF",token))
		now = bc_elseif(now);
	else if(!strcmp("ELSE",token))
		now = bc_else(now);
	else if(!strcmp("ENDIF",token))
		now = bc_endif(now);
	else if(!strcmp("#",token))
		continue;
	else if(!strcmp("SYSTEM",token))
		bc_system();
	else if(isalpha(*token)){
		valnum = *token - 'A';
		get_token();
		if(*token != '='){
			printf("Error : 代入分が正しくありません\n");
			exit(1);
		}
		get_token();
		hensuu[valnum] = logic();
		}
	else if(!strcmp("\n",token))
		continue;
	else
		printf("Error : Not order!\n");
	}
}
