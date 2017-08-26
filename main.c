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
extern int	if_flag;
extern int	last;
extern char	*list[100];

int bc_if(int ln)
{
    double      ans;
    int         n;

    if(if_flag != -1){      /* 二重if文の禁止 */
    }
    get_token();            /* 次のトークン(条件)取得 */
    ans = logic();          /* 条件式の計算 */
    if(ans == 1.0)          /* 条件 真 */
        if_flag = 1;
    else{                   /* 条件 偽 */
        if_flag = 0;
        /* 次のESLEIF, ELSEまたはENDIFまで飛ばす */
        for(n = ln + 1; n < last; ++n){     /* 次の行から最終行まで調べる */
            strcpy(gt_line, list[n]);
            get_token();            
            if(!strcmp(token, "ELSEIF") || !strcmp(token, "ELSE") ||
               !strcmp(token, "ENDIF")){
                ln = n - 1;         
                break;
            }
        }
        if(n == last){          /* 最終行までELSE等がない */
            printf("対応するELSEIF, ELSE, ENDIFがありません\n");
            exit(1);
        }
    }
    return(ln);
}
int bc_elseif(int ln)
{
    double      ans;
    int         n;
    
    if(if_flag == -1){      /* IF-ENDIFブロック外 */
        printf("IF-ENDIFブロックの外にELSEIF文があります\n");
        exit(1);
    }
    if(if_flag == 1){       /* if,elseifが真の時、次のENDIFまで飛ばす */
        for(n = ln + 1; n < last; ++n){     /* 次の行から最終行まで調べる */
            strcpy(gt_line, list[n]);
            get_token();                /* 先頭のトークン取得 */
            if(!strcmp(token, "ENDIF")){
                ln = n;             /* 現在行をENDIFの行番号-1に設定 */
                break;
            }
        }
        if(n == last){          /* 最終行までENDIDがない */
            printf("対応するENDIFがありません\n");
            exit(1);
        }
    }else{                  /* 偽の時、条件を判定 */
        get_token();            /* 次のトークン(条件)取得 */
        ans = logic();          /* 条件式の計算 */
        if(ans == 1.0)          /* 条件 真 */
            if_flag = 1;
        else{                   /* 条件 偽 */
            if_flag = 0;
            /* 次のESLEIF, ELSEまたはENDIFまで飛ばす */
            for(n = ln + 1; n < last; ++n){     /* 次の行から最終行まで調べる */
                strcpy(gt_line, list[n]);
                get_token();            /* 先頭のトークン取得 */
                if(!strcmp(token, "ELSEIF") || !strcmp(token, "ELSE") ||
                   !strcmp(token, "ENDIF")){
                    ln = n;         /* 現在行をELSE等の行番号に設定 */
                    break;
                }
            }
            if(n == last){          /* 最終行までELSE等がない */
                printf("対応するELSEIF, ELSE, ENDIFがありません\n");
                exit(1);
            }
        }
    }
    return(ln);
}
int bc_else(int ln)
{
    int         n;
    
    if(if_flag == -1){      /* IF-ENDIFブロック外 */
        printf("IF-ENDIFブロックの外にELSE文があります\n");
        exit(1);
    }
    if(if_flag == 1){       /* if,elseifが真の時、次のENDIFまで飛ばす */
        for(n = ln + 1; n < last; ++n){     /* 次の行から最終行まで調べる */
            strcpy(gt_line, list[n]);
            get_token();                /* 先頭のトークン取得 */
            if(!strcmp(token, "ENDIF")){
                ln = n;             /* 現在行をENDIFの行番号-1に設定 */
                break;
            }
        }
        if(n == last){          /* 最終行までENDIDがない */
            printf("対応するENDIFがありません\n");
            exit(1);
        }
    }else                   /* 偽の時 */
        if_flag = 1;
    return(ln);
}
int bc_endif(int ln)
{
    if(if_flag == -1){      /* IF-ENDIFブロック外 */
        printf("IF-ENDIFブロックの外にENDIF文があります\n");
        exit(1);
    }
    if_flag = -1;
    return(ln);
}

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
	if(token[0] != 'T' || token[1] != 'O'){
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
void bc_system(void)
{
char sbuff[100000];
int buff_length = strlen(sbuff);
	//memset(sbuff,'\0',buff_length);
        while(1){
		get_token();
		strcat(sbuff,token);
		//get_token();
		if(*token == '\n')
			break;
		else if(*token == '-')
			;//sbuff[strlen(sbuff)-1] = '\0';
		else
			strcat(sbuff," ");

        }
	printf("%s",sbuff);
	system(sbuff);
	memset(sbuff,'\0',buff_length);
	
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
