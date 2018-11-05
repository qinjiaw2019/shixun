#include "../include/str.h"

int last_index_of(char *s,char c)
{
	int i = 0;
	while(s[i]!='\0')
	{
		if(s[i]==c)return i;
		i++;
	}
}