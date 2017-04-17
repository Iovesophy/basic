#include <stdio.h>
#include "gettoken.h"       /* gettoken.c */
/* 関数プロトタイプ宣言 */
extern double expression(void);    /* 式 */
/* グローバル変数 */
double  hensuu[26];         /* 変数用 A - Z */

void main(void)
{
    while(1){
        printf("式(リターンのみで終了) : ");
        gets(gt_line);
        get_token();
        if(*token == '\0')  /* 空入力 */
            break;
        printf("答え=%f\n", expression());
    }
}
