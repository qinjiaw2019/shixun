#include "jpeg.h"

int jpg_back = -1;

void jpeg_show(char *filename)
{
	char s[100];
	if(filename==NULL)return;
	//lcd_draw_jpg(0,0,filename);
	sprintf(s,"../ext/jpeg_show %s",filename);
	system(s);
	jpg_back = -1;
	sam.x = sam.y = -1;
	
	while(jpg_back==-1)
	{
		ts_read(ts,&sam);
		if(sam.x>=642)jpg_back=BACK;
		printf("sxt--(%d,%d,%d)\n",sam.x,sam.y,sam.pressure);
	}
	exploer(ABLUM_DATA);
}