#include "sxt.h"


int sxt_back=-1;

//触屏控制
void sxt_play()
{
	if(sam.x>=0 && sam.x<=67 && sam.y>=0 && sam.y<=45)//返回按钮
	{
		sxt_back=BACK;
	}
}

void *pthread_touch(void *arg)//触摸屏子线程
{
	while(sxt_back==-1)
	{
		ts_read(ts,&sam);
		printf("sxt--(%d,%d,%d)\n",sam.x,sam.y,sam.pressure);
	}
	//退出子线程
	pthread_exit(NULL);
}
void sxt_show()
{
	int ret;
	int fd = -1;
	int tmp = 200;
	char pic_name[50]={0};
	
	bmp_show(IMG_BLACK_BG);
	sam.x = sam.y = -1;
	sxt_back= -1;
	
	
	FrameBuffer freambuf;
	/* 打开LCD屏幕*/
	lcd_open();
	
	/* 初始化摄像头设备*/
	linux_v4l2_device_init("/dev/video7");
	
	/* 启动摄像头*/
	linux_v4l2_start_capturing();
	
	int count = 1;
	
	// 删除保存的图片
	system("rm video/pic/*");
	
	// 删除转换的视频
	system("rm video/sp/video.avi");
	
	while(sxt_back==-1)
	{
		while(tmp--)
		{	
			/* 获取摄像头数据      存放jpg文件流*/
			linux_v4l2_get_fream(&freambuf);
			
			/* 显示摄像头图像*/
			lcd_draw_jpg(80, 0, NULL, freambuf.buf, freambuf.length, 0);
			
			sprintf(pic_name, "video/pic/%d.jpg", count++);
			printf("pic_name = %s\n", pic_name);
			
			/* 保存图像到文件*/
			fd = open(pic_name, O_RDWR|O_CREAT, 0777);
			write(fd, freambuf.buf, freambuf.length);
			close(fd);
		}
		// 转换视频                      
		system("ffmpeg -f image2 -i video/pic/%d.jpg video/sp/video.avi");
	}
	
	
	
	/* 停止摄像头*/
	linux_v4l2_stop_capturing();
	
	/* 卸载摄像头*/
	linux_v4l2_device_uinit();

	lcd_close();

	

}