#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "gettoken.h"       /* gettoken.c */
/* 関数プロトタイプ宣言 */
double logic(void);             /* 論理式     */
double expression(void);        /* 式         */
double term(void);              /* 項         */
double factor(void);            /* 因子       */
double number(void);            /* 数値・変数 */
void errorx(char *, char *);    /* エラー終了 */
/* グローバル変数 外部参照 */
extern double  hensuu[26];      /* 変数用 A - Z */

double logic(void)
{
    double  ans;

    ans = expression();
    get_token();
    while(1){
        if(*token == '<'){          /* <>,<=,< */
            get_token();
            if(*token == '='){          /* 以下 */
                get_token();
                if(ans <= expression())
                    ans = 1;
                else
                    ans = 0;
            }else if(*token == '>'){    /* 等しくない */
                get_token();
                if(ans != expression())
                    ans = 1;
                else
                    ans = 0;
            }else{                      /* より小さい */
                if(ans < expression())
                    ans = 1;
                else
                    ans = 0;
            }
        }else if(*token == '>'){    /* >=,> */
            get_token();
            if(*token == '='){          /* 以上 */
                get_token();
                if(ans >= expression())
                    ans = 1;
                else
                    ans = 0;
            }else{                      /* より大きい */
                if(ans > expression())
                    ans = 1;
                else
                    ans = 0;
            }
        }else if(*token == '='){    /* 等しい */
            get_token();
            if(ans == expression())
                ans = 1;
            else
                ans = 0;
        }else if(*token == '!'){   /* not equal*/
		get_token();
		if(ans != expression())
			ans = 1;
		else
			ans = 0;
	}else
            break;
    }
    unget_token(token);
    return(ans);
}
double expression(void)
{
    double  ans;

    ans = term();
    while(1){
        if(*token == '+'){
            strcpy(token, &token[1]);
            if(*token == '\0')
                get_token();
            ans = ans + term();
        }else if(*token == '-'){
            strcpy(token, &token[1]);
            if(*token == '\0')
                get_token();
            ans = ans - term();
        }else
            break;
    }
    unget_token(token);
    return(ans);
}
double term(void)
{
    double  ans, x;

    ans = factor();
    while(1){
        if(*token == '*'){
            get_token();
            ans = ans * factor();
        }else if(*token == '/'){
            get_token();
            x = factor();
            if(x == 0)
                errorx("0では割れない", "0");
            ans = ans / x;
        }else
            break;
    }
    return(ans);
}
double factor(void)
{
    double  ans;

    if(*token == '('){
        get_token();
        ans = expression();
        get_token();
        if(*token != ')'){
            printf(")がない\n");
            exit(1);
        }
        get_token();
        return(ans);
    }else
        return(number());
}
double number(void)
{
    double  ans;
    char    sign;

    if(*token == '+' || *token == '-'){     /* 符号判定 */
        sign = *token;
        strcpy(token, &token[1]);
        if(*token == '\0')
            get_token();
    }
    if(isalpha(*token))         /* 先頭英字 */
        ans = hensuu[toupper(*token) - 'A'];    /* 変数の内容取得 */
    else if(isdigit(*token))    /* 先頭数字 */
        ans = atof(token);          /* 数字を実数値に変換 */
    else
        errorx("数字または変数名でなければならない", token);
    get_token();
    if(sign == '-')
        return(-ans);
    return(ans);
}
void errorx(char *s1, char *s2)
{
    printf("%s <%s>\n", s1, s2);
    exit(1);
}
