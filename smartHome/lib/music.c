#include "../include/music.h"

int music_static = MUSIC_UP;//判断是增还是减

//音乐播放及音量控制
int madplay_music(char *pathName, char *cmd)
{
	int ret;
	char str[100]={0};
	//命令拼接
	stpcpy(str,"../ext/madplay ");
	strcat(str,pathName);//音乐文件
	//判断是增还是减
	if(music_static == 0)
	{
		strcat(str, " --attenuate= ");//减音量
	}
	if(music_static == 1)
	{
		strcat(str, " --amplify= ");//增音量
	}
	
	strcat(str,cmd);//分贝数值
	strcat(str," &");//后台播放
	printf("%s\n",str);
	//执行命令
	ret=system(str);
   if(ret == -1)
   {
	   perror("madplay_music system false!\n");
	   return -1;
   }
   return 0;
}

//音乐，暂停，播放，停止
int madplay_controller(char *cmd)
{
	int ret;
	char str[100]={0};
	//命令拼接
	stpcpy(str,"killall -");
	strcat(str,cmd);//命令
	strcat(str," madplay");//分隔
	//printf("kkkk:%s\n",str);
	//执行
	ret=system(str);
   if(ret == -1)
   {
	   perror("madplay_controller system false!\n");
	   return -1;
   }
   return 0;
}
/*
int main()
{
	madplay_music("sss","45");
	//madplay_controller("ssss");
   return 0;
}
*/