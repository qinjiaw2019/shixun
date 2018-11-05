#include "../include/ui.h"
#include "../src/led_m.h"
#include "../src/ablum.h"
#include "../src/camera.h"
#include "../src/sxt.h"
#include "../src/welcom.h"
#include "../src/help.h"

//首页UI
void home_ui()
{
	if(is_login==LOGINOUT)
		welcom_show();
	bmp_show(IMG_HOME_BG);	
}

//首页菜单
void menu()
{
	bmp_show_xy(ICON_STAR_X,ICON_STAR_Y,ICON_WIDTH,ICON_HEIGHT,"../pic/icon/mp3.bmp");//mp3播放器
	bmp_show_xy(ICON_STAR_X+ICON_WIDTH+ICON_INTERVAL_X,ICON_STAR_Y,ICON_WIDTH,ICON_HEIGHT,"../pic/icon/video.bmp");	//视频播放器
    bmp_show_xy(ICON_STAR_X+ICON_WIDTH*2+ICON_INTERVAL_X*2,ICON_STAR_Y,ICON_WIDTH,ICON_HEIGHT,"../pic/icon/exploer.bmp"); //文件浏览器图标
	bmp_show_xy(ICON_STAR_X+ICON_WIDTH*3+ICON_INTERVAL_X*3,ICON_STAR_Y,ICON_WIDTH,ICON_HEIGHT,"../pic/icon/sxt.bmp"); //摄像头
	bmp_show_xy(ICON_STAR_X+ICON_WIDTH*4+ICON_INTERVAL_X*4,ICON_STAR_Y,ICON_WIDTH,ICON_HEIGHT,"../pic/icon/camera.bmp"); //led
	bmp_show_xy(ICON_STAR_X+ICON_WIDTH*5+ICON_INTERVAL_X*5,ICON_STAR_Y,ICON_WIDTH,ICON_HEIGHT,"../pic/icon/ablum.bmp"); //相册
	bmp_show_xy(ICON_STAR_X+ICON_WIDTH*6+ICON_INTERVAL_X*6,ICON_STAR_Y,ICON_WIDTH,ICON_HEIGHT,"../pic/icon/led.bmp"); //led
	bmp_show_xy(ICON_STAR_X+ICON_WIDTH*7+ICON_INTERVAL_X*7,ICON_STAR_Y,ICON_WIDTH,ICON_HEIGHT,"../pic/icon/help.bmp"); //简介
}

/*
首页应用点击按钮处理
*/
int button()
{
	if(sam.x>=ICON_STAR_X && sam.y>=ICON_STAR_Y 
			&& sam.x<=ICON_STAR_X+ICON_WIDTH+ICON_INTERVAL_X && sam.y<=ICON_STAR_Y+ICON_HEIGHT)
		return MP3_PLAY;
	else if(sam.x>=ICON_STAR_X+ICON_WIDTH+ICON_INTERVAL_X && sam.x<=ICON_STAR_X+ICON_WIDTH*2+ICON_INTERVAL_X*2 && 
		sam.y>=ICON_STAR_Y && sam.y<=ICON_STAR_Y+ICON_HEIGHT)
		return VEDIO_PLAY;
	else if(sam.x>=ICON_STAR_X+ICON_WIDTH*2+ICON_INTERVAL_X*2 && sam.x<=ICON_STAR_X+ICON_WIDTH*3+ICON_INTERVAL_X*3 && 
		sam.y>=ICON_STAR_Y && sam.y<=ICON_STAR_Y+ICON_HEIGHT)
		return EXPOLER;
	else if(sam.x>=ICON_STAR_X+ICON_WIDTH*3+ICON_INTERVAL_X*3 && sam.x<=ICON_STAR_X+ICON_WIDTH*4+ICON_INTERVAL_X*4 && 
		sam.y>=ICON_STAR_Y && sam.y<=ICON_STAR_Y+ICON_HEIGHT)
		return CAMERA;
	else if(sam.x>=ICON_STAR_X+ICON_WIDTH*4+ICON_INTERVAL_X*4 && sam.x<=ICON_STAR_X+ICON_WIDTH*5+ICON_INTERVAL_X*5 && 
		sam.y>=ICON_STAR_Y && sam.y<=ICON_STAR_Y+ICON_HEIGHT)
		return PHOTO;
	else if(sam.x>=ICON_STAR_X+ICON_WIDTH*5+ICON_INTERVAL_X*5 && sam.x<=ICON_STAR_X+ICON_WIDTH*6+ICON_INTERVAL_X*6 && 
		sam.y>=ICON_STAR_Y && sam.y<=ICON_STAR_Y+ICON_HEIGHT)
		return ABLUM;
	else if(sam.x>=ICON_STAR_X+ICON_WIDTH*6+ICON_INTERVAL_X*6 && sam.x<=ICON_STAR_X+ICON_WIDTH*7+ICON_INTERVAL_X*7 && 
		sam.y>=ICON_STAR_Y && sam.y<=ICON_STAR_Y+ICON_HEIGHT)
		return LED;
	else if(sam.x>=ICON_STAR_X+ICON_WIDTH*7+ICON_INTERVAL_X*7 && sam.x<=ICON_STAR_X+ICON_WIDTH*8+ICON_INTERVAL_X*8 && 
		sam.y>=ICON_STAR_Y && sam.y<=ICON_STAR_Y+ICON_HEIGHT)
		return JIANJIE;
	else return HOME;
}

void show()
{
	pos_index = button();
	if(pos_index==WELCOM)
	{
		
		welcom_show();
	}
	else if(pos_index==HOME)
	{
		home_ui();//首页UI
		menu();
	}
	else if(pos_index==VEDIO_PLAY){
		//vedio_show(NULL);
		exploer(APP_DATA);
	}else if(pos_index==MP3_PLAY)
	{
		//mp3_show(NULL);
		exploer(APP_DATA);
	}else if(pos_index==EXPOLER)
	{
		exploer(APP_DATA);
	}else if(pos_index==ABLUM)
	{
		ablum_show(NULL);
	}else if(pos_index==PHOTO)
	{
		camera_show();
	}else if(pos_index==CAMERA){
		//sxt_show();
		camera_show();
	}
	else if(pos_index==LED){
		led_show();
	}
	else if(pos_index==JIANJIE){
		show_help();
	}
	
	printf("btn:%d",pos_index);
}