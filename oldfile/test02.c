#include <stdio.h>
#include <string.h>
#include "gettoken.h"

void main(void)
{
	char	buff[256];

	printf("character : ");
	gets(buff);

	strcpy(gt_line, buff);
	while(*get_token() != '\0')
		printf("(%s)", token);
}
