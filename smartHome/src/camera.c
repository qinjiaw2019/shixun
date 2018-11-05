#include "camera.h"

int camera_back = -1;


int getTimes()
{
	time_t t;
	t = time(NULL);
	int ii = time(&t);
	return ii;
}
//提示对话框
void *tip_dialog(void *arg)
{
	
	while(1)
	{
		bmp_show_xy(200,148,400,184,"../pic/ui/success.bmp");
		if(sam.x>=348 && sam.y<=445 && sam.y>=270 && sam.y<=310)break;//弹框确认
	}
}

//保存为视频 
int save_to_vedio(int filename)
{
	int count = 1;
	int fd = -1;
	int tmp = 20;
	char pic_name[50]={0};
	char cmd[500] = "";
	FrameBuffer freambuf;

	// 删除保存的图片
	system("rm -rf ../data/camera/tmp/*.jpg");//删除临时jpg文件
	system("rm -rf ../data/camera/video/*.jpg");//删除临时jpg文件
	system("rm -rf ../data/video.avi");//删除临时jpg文件
	while(tmp--)
	{	
		/* 获取摄像头数据      存放jpg文件流*/
		linux_v4l2_get_fream(&freambuf);
		
		/* 显示摄像头图像*/
		lcd_draw_jpg(80, 0, NULL, freambuf.buf, freambuf.length, 0);
		
		sprintf(pic_name, "../data/camera/tmp/%d.jpg", count++);
		printf("pic_name = %s\n", pic_name);
		
		/* 保存图像到文件*/
		fd = open(pic_name, O_RDWR|O_CREAT, 0777);
		write(fd, freambuf.buf, freambuf.length);
		close(fd);
	}
	
	// 转换视频   
	//stpcpy(cmd,"ffmpeg -f image2 -i ../data/camera/tmp/*.jpg ../data/camera/video/");
	//strcat(cmd,filename);
	//strcat(cmd,".avi");
	//sprintf(cmd, "ffmpeg -f image2 -i ../data/camera/tmp/*.jpg ../data/camera/video/%d.avi", filename);
	printf("cmd:%s\n",cmd);
	//system("ffmpeg -f image2 -i ../data/camera/tmp/%d.jpg ../data/camera/video/video.avi");
	system("ffmpeg -f image2 -i ../data/camera/tmp/%d.jpg ../data/video.avi");
	//system(cmd);
	
	// 删除保存的图片
	system("rm -rf ../data/camera/tmp/*.jpg");//删除临时jpg文件
	system("rm -rf ../data/camera/video/*.jpg");//删除临时jpg文件
}

//保存为jpg图片
int save_to_pic(int picname)
{
	char pic_name[20];
	int ret2;
	pthread_t threadid2;//创建线程号
	
	//获取数据
	FrameBuffer video_buf;
	//获取摄像头的画面
	linux_v4l2_get_fream(&video_buf);
	
	//将获取的该帧信息写入文件
	sprintf(pic_name,"../data/ablum/%d.jpg",picname);
	int jpg_fd = open(pic_name,O_RDWR|O_CREAT,0666);
	if(jpg_fd < 0)
		{
			printf (" create jpeg  failed !\n");
			return -1;		
		}

	int ret = write(jpg_fd,video_buf.buf,video_buf.length);
	if( ret != video_buf.length )
	{
		printf (" write jpeg  failed !\n");
		return -1;	
	}
	close(jpg_fd);
	
	//创建线程
	ret2=pthread_create(&threadid2,NULL,tip_dialog,NULL);
	if(ret2 != 0)
	{
		perror("pthread_create false!\n");
		return -1;//异常推出
	}

}

//播放控制
void camera_play()
{
	if(sam.x>=704 && sam.x<=787 && sam.y>=189 && sam.y<=251)//拍照按钮
	{
		save_to_pic(getTimes());
	
	}else if(sam.x>=0 && sam.x<=67 && sam.y>=0 && sam.y<=45)//返回按钮
	{
		camera_back=BACK;
	}else if(sam.x>=704 && sam.x<=787 && sam.y>=113 && sam.y<=165 )//保存为视频
	{
		save_to_vedio(getTimes());
	}
}

void *pthread_touch_camera(void *arg)//触摸屏子线程
{
	while(camera_back==-1)
	{
		ts_read(ts,&sam);
		camera_play();
		printf("sxt--(%d,%d,%d)\n",sam.x,sam.y,sam.pressure);
	}
	//退出子线程
	pthread_exit(NULL);
	
}
void camera_show()
{
	int ret;
	
	bmp_show(IMG_CAMERA_BG);
	sam.x = sam.y = -1;
	camera_back= -1;
	
	pthread_t threadid;//创建线程号
	//创建线程
	ret=pthread_create(&threadid,NULL,pthread_touch_camera,NULL);
	if(ret != 0)
	{
		perror("pthread_create false!\n");
		return ;//异常推出
	}

	//初始化lcd屏幕
	lcd_open();
	//映射内存
	mmap_lcd();
	
	//获取数据
	FrameBuffer video_buf;
	
	//初始化摄像头
	 linux_v4l2_device_init("/dev/video7");

	 //开启摄像头捕捉
	 linux_v4l2_start_capturing();
	while(camera_back==-1)
	{
		//获取摄像头的画面
	     linux_v4l2_get_fream(&video_buf);

         //摄像头显示画面
	     show_video_data(0,0,video_buf.buf,video_buf.length);
	}
	//摄像头暂停捕捉
	 linux_v4l2_stop_capturing();

	 //解除摄像头的初始化 
     linux_v4l2_device_uinit();
	 
	 //关闭设备
	 lcd_close();
	 //回收线程
	pthread_join(threadid,NULL);
	exploer(ABLUM_DATA);
}