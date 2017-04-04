/* gettoken.h - head file for gettoken library */
#define STR_MAX 256
extern char	gt_line[STR_MAX];
extern char	token[STR_MAX];
/*prototype */
extern char *get_token(void);
extern void unget_token(char *);
int iskanji(int, unsigned char);
