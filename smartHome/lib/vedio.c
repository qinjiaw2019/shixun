#include "../include/vedio.h"
#include <stdlib.h>
#include <stdio.h>

int back = -1;
int mplayer_state = VEDIO_STOP;
int is_mute = VEDIO_MUTE_Y;//是否静音

//重新播放视频
void replay(char *filename)
{
	if(filename!=NULL)
	{
		mplayer_tv(filename,"0","48","800","384");
		mplayer_state=VEDIO_PLAY;
	}
}

//音量控制
void vedio_mute(int x)
{

	int voice  = (x-628 );
	int i = 0;
	printf("\n mute:%d \n",voice);
	bmp_show_xy(628,455-20,164,40,"../pic/ui/vedio/mute.bmp");
	if(x<0)
	{
		bmp_show_xy(628,455-10,20,20,"../pic/ui/vedio/mute_k.bmp");
		mplayer_cmd("volume 500\n");
	}
	else{
		bmp_show_xy(x,455-10,20,20,"../pic/ui/vedio/mute_k.bmp");
		
		if(voice>=67)
			mplayer_cmd("volume 1000\n");
		else 
			mplayer_cmd("volume -1000\n");
	}
	
}



//视频控制
void play(char *filename)
{
	int i = 0;

	if(sam.y>=62 && sam.y<=418)//视频播放区域
	{
	
		if(mplayer_state==VEDIO_PAUSE)
		{
			mplayer_cmd("pause\n");
			mplayer_state=VEDIO_PLAY;
		}
	}
	else if(sam.x>=22 && sam.y>=441 && sam.x<=58 && sam.y<=480)//视频播放按钮区域
	{
		if(mplayer_state==VEDIO_PAUSE)
		{
			mplayer_cmd("pause\n");
			mplayer_state=VEDIO_PLAY;
		}

	}
	else if(sam.x>=81 && sam.y>=441 && sam.x<=91 && sam.y<=480)//视频暂停按钮区域
	{
		if(mplayer_state==VEDIO_PLAY)
		{
			mplayer_cmd("pause\n");
			mplayer_state=VEDIO_PAUSE;
		}
	}
	else if(sam.x>=117 && sam.y>=441 && sam.x<=135 && sam.y<=480)//停止按钮区域
	{
		mplayer_cmd("quit 0\n");
		back =BACK;
	}
	else if(sam.x>=15 && sam.y>=6 && sam.x<=31 && sam.y<=24)//返回
	{
		show();//返回首页
		printf("%s\n","back");
		back =BACK;
	}else if(sam.x>=628 && sam.y>=418 && sam.x<=768)//静音区域
	{	

		vedio_mute(sam.x);
	//	mplayer_cmd("mute 0\n");//静音控制
		printf("vedio mute--(%d,%d,%d)\n",sam.x,sam.y,sam.pressure);
	}
	else if(sam.x>=299 && sam.x<=338 && sam.y>=418)//快进
	{
		mplayer_cmd("seek 10\n");
		printf("++\n");
	}
	else if(sam.x>=349 && sam.x<=390 && sam.y>=418)//快退
	{
		mplayer_cmd("seek -10\n");
		printf("--\n");
	}
	else
	{
		printf("vedio--(%d,%d,%d)\n",sam.x,sam.y,sam.pressure);
	}
}



//视频界面显示
void vedio_show(char *filename)
{
	bmp_show(IMG_VEDIO_BG);
	vedio_mute(-1999);
	
	creat_fifo();
	mplayer_state = VEDIO_PLAY;
	replay(filename);
	
	sam.y = sam.x = -1;
	back = -1;

	while(back==-1)
	{
		ts_read(ts,&sam);
		
		play(filename);
	}
	mplayer_destroy();
	mplayer_state=VEDIO_STOP;
	exploer(APP_DATA);
}

