/*
字句解析
単語に分解して取り出す関数と取り出した単語を元に戻す関数作成。

関数の書式。
char *get_token(void);

void unget_token(char *word);

関数名
get_token

unget_token

引数
none

char *word;
（戻す単語を格納）

返却値
取り出した単語の先頭アドレス

none

その他
グローバル変数
char *gt_line;一行分の文字列を格納しておく
(MAX=256文字)
char *token;取り出した単語が格納される

none

for example 
次の1行を変数gt_lineに格納する。
2.1 + 3 + 4.33 + 5e2
最初にget_token()を呼び出すと、変数tokenには、
2.1が格納される。
次に呼び出すと空白は無視されて+が格納される。
次に3、+、4.33、+、5e2と順に格納
最後にnill値が格納

処理フロー
１、ポインタ変数pの内容が数字である
なので、数字以外の文字が現れるまで一文字ずつ変数tokenに格納しながら進める。

２、数字以外の文字が現れた時点で変数tokenの最後に\0を付加し、
変数gt_lineにはポインタ変数p以降の文字列を新たに変数gt_lineに格納する。

３、配列gt_line,tokenはこのような状態で、関数の呼び出し側に戻る。
次に関数get_token()が呼ばれると、最初の空白は無視されポインタ変数p
は記号の位置に進む。記号の場合は、その一文字だけを変数tokenに格納する。
これを繰り返して単語に分解
＊最初の文字が数字の場合、数字ピリオドE以外の文字が現れるまで。
＊最初の文字が英字の場合、英字数字以外の文字が現れるまで。
＊最初の文字が漢字の場合、漢字以外の文字が現れるまで。
＊最初の文字が”　 の場合、次の”　の文字が現れるまで
＊最初の文字が’　 の場合、次の’　の文字が現れるまで
１文字ずつ変数tokenに格納し、上記以外の文字（記号）の場合は、
その１文字だけを変数tokenに格納する。

「void get_token(void) トークン取り出し　」は、void,get,_,token,(,void,),/,*,トークン取り出し,*,/.\n,\0
に分解されて順次格納される。
数式を処理するだけのためであれば、数値と演算子に分解出来るだけでよい。
*/
//[gettoken.c]
/*
	//gettoken.c - 字句解析関数群　Ver 1.2
	//2017.4 (c) kazuya yuda
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STR_MAX 256
#define EUC	1
#define SJIS1	2
#define SJIS2	3
#ifdef UNIX
	#define KANJI1	EUC
	#define KANJI2	EUC
#else
	#define KANJI1	SJIS1
	#define KANJI2	SJIS2
#endif

char	gt_line[STR_MAX];
char	token[STR_MAX];

char	*get_token(void);
void	unget_token(char *);
int iskanji(int, unsigned char);

char	*get_token(void)
{
	char	*p, *ptk, ch;

	p   = gt_line;
	ptk = token;
	while(*p == ' ' || *p == '\t')
		++p;
	if(*p == '\0') {
		token[0] = '\0';
		return(token);
	}
	/* ---漢字--- */
	if(iskanji(KANJI1, *p)){
		do{
		*ptk++ = *p++;
		if(!iskanji(KANJI2, *p)){
			printf("漢字コードが不正です\n");
			exit(1);
		}
		*ptk++ = *p++;
	  }while(iskanji(KANJI1, *p) && *p != '\0');
	/* --- 英字　英数字--- */
	}else if(isalpha(*p)){
		do{
			*ptk++ = *p++;
		}while(isalnum(*p) && *p !='\0');
	/* --- 数字 ---*/
	}else if(isdigit(*p)){
		do{
			*ptk++ = *p++;
		}while((isdigit(*p) || *p == '.' || toupper(*p) == 'E') && *p !='\0');
	/* --- 文字・文字列定数 --- */
	}else if(*p == '\'' || *p == '"'){
		ch = *p;
		*ptk++ = *p++;
		do{
			if(*p == '\\'){
				*ptk++ = *p++;
				*ptk++ = *p++;
			}else if(*p != '\n')
				*ptk++ = *p++;
		}while(*p != ch);
		++p;
	/* --- その他の文字 --- */
	}else
		*ptk++ = *p++;
	*ptk = '\0';
	strcpy(gt_line, p);
	return(token);
}
void unget_token(char *t)
{
	char	work[STR_MAX];

	strcpy(work, t);
	if(*t == '\'' || *t == '"'){
	   	t[1] = '\0';
		strcat(work, t);
	}
	strcat(work, gt_line);
	strcpy(gt_line, work);
}
int iskanji(int type, unsigned char code)
{
	int	ret = 0;
	switch(type){
		case EUC:
			if((code >= 0xa1 && code <= 0xfe))
				ret = code;
			break;
		case SJIS1:
			if((code >= 0x81 && code <= 0x9F) || (code >= 0xe0 && code <= 0xfc))
				ret = code;
			break;
		case SJIS2:
			if((code >= 0x40 && code <= 0x7e) || (code >= 0x80 && code <= 0xfc))
				ret = code;
			break;
		default:
			printf("iskanji:unknown Kanji code type.\n");
			exit(1);
		}
		return(ret);
}

#ifdef TEST
void main(void)
{
	FILE	*bf;
	char	file[80];

	printf("please input file name : ");
	gets(file);
	if((bf = fopen(file, "r")) == NULL){
		printf("not open the file...\n");
		exit(1);
	}
	while(fgets(gt_line, STR_MAX, bf) != NULL){
		while(1){
			get_token();
			if(*token == '\0')
				break;
			if(*token == '\n')
				printf("(\\n)");
			else
				printf("(%s) ", token);
			}
			printf("\n");
		}
		fclose(bf);
}
#endif			
