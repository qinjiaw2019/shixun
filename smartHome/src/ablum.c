#include "ablum.h"

char ablum_array[30]={0};
char ablum_picture[200][30]={0};

int ablum_count = 0;//文件计数器
int ablum_back = -1;
int is_auto_play = 0;//是否自动播放

int j = 0;//计数器
//读取相册
int read_ablum_dir(char *dirpath)
{
	int i = 0;
	DIR* dir;
	struct dirent *bmp;
	ablum_count = 0;
	
	
	//打开目录
	dir  = opendir(dirpath);
	if(dir == NULL)
	{
		
		printf("open dir failed!\n");
		return -1;
	}
	//读目录
	while((bmp = readdir(dir))!=NULL)
	{
		//判断读取的文件中是否是BMP图片
		if(strstr(bmp->d_name,".bmp")!=NULL)
		{
			//字符串拼接
			sprintf(ablum_array,"%s/%s",dirpath,bmp->d_name);
			
			strcpy(ablum_picture[i],ablum_array);
			
			i++;
			ablum_count=ablum_count+1;
		}
	}

	return 0;
	
}

void auto_play()
{
	int i ;
	for(i = 0 ;i<ablum_count;i++)
	{
		
		bmp_show(ablum_picture[i]);
		sleep(3);//三秒延时
	}
	
}
//播放控制
void ablum_play()
{
	

	if(sam.x>=712 && sam.x<=787 && sam.y>=4&& sam.y<=78)//自动播放
	{
		auto_play();
		sleep(3);//三秒延时
		bmp_show(IMG_ABLUM_BG);//播放完成后返回封面页
	}
	else if(sam.x>=666 )//下一张
	{
			bmp_show(ablum_picture[j]);
			j++;
			if(j>=ablum_count)j=0;
			
			printf("%s\n",ablum_picture[j]);
	}else if(sam.x<=95 && sam.y>=119 )//上一张
	{
		bmp_show(ablum_picture[j]);
		j--;
		if(j<=0)j=ablum_count-1;
	}else if(sam.x>=2&&sam.x<=95 && sam.y<119)//返回
	{
		ablum_back=BACK;
	}


}

void ablum_show(char *dir)
{
	bmp_show(IMG_ABLUM_BG);
	sam.y = sam.x = -1;
	read_ablum_dir(ABLUM_DATA);
	ablum_back = -1;

	while(ablum_back==-1)
	{
		ts_read(ts,&sam);
		ablum_play();
		printf("ablum--(%d,%d,%d)\n",sam.x,sam.y,sam.pressure);
	}
	exploer(ABLUM_DATA);
	
}