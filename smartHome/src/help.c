#include "help.h"

int help_back = -1;

void show_help()
{
	bmp_show("../pic/ui/help.bmp");	
	sam.x = sam.y = -1;
	help_back = -1;
	
	while(help_back==-1)
	{
		ts_read(ts,&sam);
		if(sam.x>=0 && sam.x<=80 && sam.y>=0 &&sam.y<=70)help_back=BACK;
		printf("welcom--(%d,%d,%d)\n",sam.x,sam.y,sam.pressure);
	}
}