#include "../include/mplayer.h"
//创建管道
int creat_fifo()
{
	int ret;
	int fifo_fd;
		//2.判断文件是否存在
		if(access("/tmp/fifo", F_OK))
		{
			//1.创建管道
			ret = mkfifo("/tmp/fifo", 0777);
			if(ret < 0)
			{
				perror("mkfifo /tmp/fifo false!\n");
				return -1;
			}
		
		}
		//3.打开管道文件
		fifo_fd = open("/tmp/fifo", O_RDWR);
		if(fifo_fd == -1)
		{
			perror("open false!\n");
			return -1;
		}
	return 0;
}


//自定义视频播放
int mplayer_tv(char *pathName, char *x, char *y, char *w, char *h)
{	int ret;
	char str[100]={0};
	//命令拼接
	stpcpy(str,"../ext/mplayer -slave -quiet -input file=/tmp/fifo ");
	strcat(str,"-geometry ");
	strcat(str,x);
	strcat(str,":");
	strcat(str,y);
	strcat(str," -zoom -x ");
	strcat(str,w);
	strcat(str," -y ");
	strcat(str,h);
	strcat(str," ");
	strcat(str,pathName);
	strcat(str," &");//后台播放
	printf("%s \n",str);
	
	//执行命令
	ret=system(str);
	if(ret == -1)
   {
	   perror("system false!\n");
	   return -1;
   }
	return 0;
}


//视频控制
int mplayer_cmd(char *cmd)
{	char file;
	int ret;
	//打开文件管道
	file=open("/tmp/fifo",O_RDWR);
	//写入管道
	ret=write(file,cmd,strlen(cmd));
	if(ret == -1)
	{
		printf("write lcd_fd fails!\n");
		return -1;
	}
   return 0;
}
void mplayer_destroy()
{
	system("killall -9 mplayer");
}
/**测试
int main()
{
	creat_fifo();
	mplayer_tv("shuosanjiusan.avi","12","45","100","100");
	sleep(10);
	mplayer_cmd("pause\n");
	creat_fifo();
	sleep(10);
	mplayer_cmd("pause\n");
	//sleep(10);
	

	return 0;
}*/