# basic
My basic programming language.

この言語は基本的なBASICを学習目的で開発するためのもの。  

# order list

``` 
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
```

# 字句解析  
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
char *gt_line; 一行分の文字列を格納しておく  

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
# 処理フロー  
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
＊最初の文字が  ”　 の場合、次の”　の文字が現れるまで  
＊最初の文字が  ’　 の場合、次の’　の文字が現れるまで  
１文字ずつ変数tokenに格納し、上記以外の文字（記号）の場合は、  
その１文字だけを変数tokenに格納する。  
「void get_token(void) トークン取り出し　」は、void,get,_,token,(,void,),/,*,トークン取り出し,*,/.\n,\0  
に分解されて順次格納される。  
数式を処理するだけのためであれば、数値と演算子に分解出来るだけでよい。  
