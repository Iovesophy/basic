#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gettoken.h"
/* グローバル変数 */
extern double expression(void); /* eval.c */
extern double  hensuu[26];      /* 変数用(A～Z) */
void bc_print(void)
{
	while(1){
		get_token();
		if(*token == '"')
			printf("%s", &token[1]);
		else if(*token == '\n')
			break;
		else
			printf("%f", expression());
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
                printf("Var is only alpha...\n");
                exit(1);
        }
        gets(buff);
        hensuu[val - 'A'] = atof(buff);
}
