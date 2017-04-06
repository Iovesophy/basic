#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "gettoken.h"
/*関数プロトタイプ宣言*/
double logic(void);
double expression(void);
double term(void);
double factor(void);
double number(void);
void errorx(char *, char *);
/*グローバル変数　外部参照*/
extern double hensuu[26];

double logic(void)
{
	double ans;
	
	ans = expression();
	get_token();
	while(1){
		if(*token == '<'){
			get_token();
			if(*token == '='){
				get_token();
				if(ans <= expression())
					ans = 1;
				else
					ans = 0;
			}else if(*token == '>'){
				get_token();
				if(ans != expression())
					ans = 1;
				else
					ans = 0;
			}else{
				if(ans < expression())
					ans = 1;
				else
					ans = 0;
			}
		}else if(*token == '>'){
			get_token();
			if(*token == '='){
				get
