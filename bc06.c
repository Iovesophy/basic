#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gettoken.h"
/* グローバル変数 */
extern double  hensuu[26];      /* 変数用(A～Z) */
void bc_print(void)
{
        if(!isalpha(*get_token())){
                printf("Var is only alpha");
                exit(1);
        }
        char val = *token;
        printf("%f\n", hensuu[val - 'A']);
}
void bc_input(void)
{
        char    buff[256];
        char val = *get_token();
        if(!isalpha(val)){
                printf("Var is only alpha...\n");
                exit(1);
        }
	printf("\x1b[35m");
        printf("➤ ~ ");
	printf("\x1b[37m");
        gets(buff);
        hensuu[*token - 'A'] = atof(buff);
	printf("\x1b[0m");
}

