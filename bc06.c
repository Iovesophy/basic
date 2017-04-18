#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gettoken.h"
/* グローバル変数 */
extern double	logic(void); /* eval.c */
extern double	hensuu[26];      /* 変数用(A～Z) */
extern int	for_ln;
extern int	next_ln;

int bc_for(int ln)
{
	char	val;
	double	d1, d2, d3;

	val = *get_token();
	if(!isalpha(val)){
		printf("Error : 変数名は英字のみです\n");
		exit(1);
	}
	if(*get_token() != '='){
		printf("Error : FOR syntax error[=]\n");
		exit(1);
	}
	get_token();
	d1 = logic();
	get_token();
	if(token[0] != 'G' || token[1] != 'O'){
		printf("Error : FOR syntax error[TO]\n");
		exit(1);
	}
	get_token();
	d2 = logic();
	get_token();
	if(!strcmp(token, "STEP")){
		get_token();
		d3 = logic();
	}else if(*token == '\n')
		d3 = 1;
	else{
		printf("Error : FOR syntax error[STEP]\n");
		exit(1);
	}

	val = val - 'A';
	if(for_ln == -1){
		for_ln = ln;
		hensuu[val] = d1;
	}else{
		hensuu[val] = hensuu[val] + d3;
		if(d1 <= d2 && d2 < hensuu[val] || d1 > d2 && d2 > hensuu[val]){
			ln = next_ln;
			for_ln = next_ln = -1;
		}
	}
	return(ln);
}
int bc_next(int ln)
{
	if(for_ln == -1){
		printf("Error : not relate order [FOR]\n");
		exit(1);
	}
	next_ln = ln;
	ln = for_ln - 1;
	return(ln); 
}

void bc_print(void)
{
	while(1){
		get_token();
		if(*token == '"')
			printf("%s", &token[1]);
		else if(*token == '\n')
			break;
		else
			printf("%f", logic());
		get_token();
		if(*token == ',')
			printf("%s"," ");
		else if(*token == ';')
			;
		else if(*token == '\n')
			break;
		else{
			printf("Error : PRINT syntax error!\n");
			exit(1);
		}
	}
	printf("\n");
}
void bc_input(void)
{
	char	val;	/* var name (number)*/
        char    buff[256];
	
	if(*get_token() == '"'){
		printf("%s", &token[1]);
		if(*get_token() == ',')
			;
		else if(*token == ';'){
			printf("\x1b[35m");
			printf("➤ ~ ");
			printf("\x1b[0m");
		}else{
			printf("Error : syntax of input error.");
			exit(1);
		}
		val = *get_token();
	}else{
		val = *token;
		printf("\x1b[35m");
		printf("➤ ~ ");
		printf("\x1b[0m");
	}
        if(!isalpha(val)){
                printf("Error : Var is only alpha...\n");
                exit(1);
        }
        fgets(buff,256,stdin);
        hensuu[val - 'A'] = atof(buff);
}
