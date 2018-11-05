#include "../include/file.h"
#include "../src/jpeg.h"

char bmp_array[30]={0};
char bmp_picture[200][30]={0};

int file_count = 0;//文件计数器
int file_back =-1;
int current_page = 1;//当前页数
int toatal = 0;//总页数
int read_dir(char *dirpath)
{
	int i = 0;
	DIR* dir;
	struct dirent *bmp;
	file_count = 0;
	
	printf("open dir :%s\n",dirpath);
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
		/*
		//判断读取的文件中是否是BMP图片
		if(strstr(bmp->d_name,".bmp")!=NULL)
		{
			//字符串拼接
			sprintf(bmp_array,"%s%s",dirpath,bmp->d_name);
			//printf("bmp_array = %s\n",bmp_array);
			strcpy(bmp_picture[i],bmp_array);
			i++;
			file_count=file_count+1;
		}	
		*/
		//字符串拼接
		if(strcmp(bmp->d_name,".")!=0)//去掉. 目录
		{
			sprintf(bmp_array,"%s/%s",dirpath,bmp->d_name);
			 
			strcpy(bmp_picture[i],bmp_array);
			i++;
			file_count=file_count+1;
		}
	}

	return 0;
	
}


//填充文件信息
void fill_item(int x,int y,char *filename)
{
	
	Display_characterX(x,          //x坐标起始点
						   y,          //y坐标起始点
						   filename,   //GB2312 中文字符串
						   0x454545,     //字体颜色值
						   1);	
}

//获取父路径
void get_parent_path(char *path)
{
	int i = strlen(path)-1;
	while(path[i]!='\0')
	{
		if(path[i]=='/')
		{
			path[i]='\0';
			break;
		}
		i--;
	}
	
}

//选择文件
void select_file()
{
	int y = sam.y;
	int index  = -1;
	struct stat s_buf;
	if(y>=65 && y<=410)//文件区域
	{
		index = (y - 65) /60 + (current_page-1) * 5;//(current_page-1) * 5 + index
		stat(bmp_picture[index],&s_buf);
		if(strstr(bmp_picture[index],".avi")!=NULL)//视频文件
		{
			vedio_show(bmp_picture[index]);
		}else if(strstr(bmp_picture[index],".mp3")!=NULL)//音频文件
		{
			mp3_show(bmp_picture[index]);
		}
		else if(strstr(bmp_picture[index],".jpg")!=NULL)//音频文件
		{
			jpeg_show(bmp_picture[index]);
		}
		else if(S_ISDIR(s_buf.st_mode))//文件夹
		{	
			//exploer(bmp_picture[index]);
		}
		printf("current file:%s\n",bmp_picture[index]);
	}
	else if(sam.x>=245 && sam.x<=283 && sam.y>=422)//首页
	{
		current_page = 1;
	}
	else if(sam.x>=283 && sam.x<=341 && sam.y>=422)//下一页
	{
		current_page +=1;
		
		if(current_page>toatal)current_page=toatal;
	}
	else if(sam.x>=341 && sam.x<=396 && sam.y>=422)//上一页
	{
		current_page -=1;
		if(current_page<1)current_page=1;
	}
	else if(sam.x>=396 && sam.x<=472 && sam.y>=422)//最后一页
	{
		current_page =toatal;
	}
	else if(sam.x>=25 && sam.y>=21 && sam.x<=71 && sam.y<=65)
	{
		file_back = BACK;
		printf("back \n");
		
	}
}

void load(int start)
{
	int i = 0;
	bmp_show(IMG_EXPLOER_BG);
	bmp_show_xy(0,480-60,800,60,IMG_EXPLOER_BOTTOM);
	for( i = 0;i<5 && (start+i)< file_count;i++)
	{
		//show_shape(men_fd,180,20,600,440,bmp_picture[i]);
		bmp_show_xy(0,65+60*i,800,60,FILE_DIR_ITEM);
		fill_item(50,65+60*i+30,bmp_picture[start+i]);
	}
}

void exploer(char *path)
{
	int i ,k;

	for( i=0;i<200;i++)
		for( k= 0;k<30;k++)
			bmp_picture[i][k]=0;
	read_dir(path);
	
	
   
	//计算总页数
	toatal= file_count/5;
	if(toatal*5<file_count)toatal+=1;
	
	sam.x = sam.y = -1;
	bmp_show(IMG_EXPLOER_BG);
	bmp_show_xy(0,480-60,800,60,IMG_EXPLOER_BOTTOM);
	file_back = -1;
	Init_Font();//字体库初始化
	while(file_back==-1)
	{
		ts_read(ts,&sam);
		load((current_page-1)*5);
		select_file();
		printf("(%d,%d,%d)\n",sam.x,sam.y,sam.pressure);
	}
	//UnInit_Font();
}

