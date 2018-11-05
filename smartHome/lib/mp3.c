#include "../include/mp3.h"


int music_state = MUSIC_STOP;
int back_mp3 = -1;

//音量调节
void mp3_mute()
{
	
}

//播放控制
void mp3_play(char *filename)
{
	if(sam.y>=62 && sam.y<=418)//播放区域
	{
		madplay_controller("18");
		if(music_state==MUSIC_PAUSE)
		{
			
			music_state=MUSIC_PLAY;
		}
	}
	else if(sam.x>=22 && sam.y>=441 && sam.x<=58 && sam.y<=480)//播放按钮区域
	{
		madplay_controller("18");
		if(music_state==MUSIC_PAUSE)
		{
			
			music_state=MUSIC_PLAY;
		}

	}
	else if(sam.x>=81 && sam.y>=441 && sam.x<=91 && sam.y<=480)//暂停按钮区域
	{
		madplay_controller("19");
		if(music_state==MUSIC_PLAY)
		{
			
			music_state=MUSIC_PAUSE;
		}
	}
	else if(sam.x>=117 && sam.y>=441 && sam.x<=135 && sam.y<=480)//停止按钮区域
	{
		madplay_controller("9");
		back_mp3 =BACK;
	}
	else if(sam.x>=15 && sam.y>=6 && sam.x<=31 && sam.y<=24)//返回
	{
		show();//返回首页
		printf("%s\n","back");
		back_mp3 =BACK;
	}else if(sam.x>=582 && sam.y>=468 && sam.x<=612 && sam.y<=480)//静音区域
	{
		//madplay_controller("mute 0\n");//静音控制
	}
	else
	{
		printf("MUSIC--(%d,%d,%d)\n",sam.x,sam.y,sam.pressure);
	}
}

void mp3_show(char *filename)
{
	sam.y = sam.x = -1;
	back_mp3 = -1;
	bmp_show(IMG_MP3_BG);
	
	
	if(filename!=NULL)
	{
		music_state==MUSIC_PLAY;
		madplay_music(filename,"10");
	}
	while(back_mp3==-1)
	{
		ts_read(ts,&sam);
		mp3_mute();
		mp3_play(filename);
	}
	madplay_controller("9");
	music_state = MUSIC_STOP;
	exploer(APP_DATA);
}