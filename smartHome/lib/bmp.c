#include "../include/bmp.h"

int bmp_show(char *pathname)
{
	int i,x,y;
	int bmp_fd;
	int lcdfd;
	int lcd_buffer[800*480];
	int tmp_buffer[800*480];
	char bmp_buffer[800*480*3];
	
	bmp_fd = open(pathname,O_RDONLY);
	if(bmp_fd == -1)
	{
		printf("open bmp failed!\n");
		return -1;
	}
	
	lcdfd = open("/dev/fb0",O_RDWR);
	if(lcdfd == -1)
	{
		printf("open lcd_fd failed!\n");
		return -1;
	}
	
	lseek(bmp_fd,54,SEEK_SET);
	read(bmp_fd,bmp_buffer,sizeof(bmp_buffer));
	
	for(i=0;i<800*480;i++)
		lcd_buffer[i] = bmp_buffer[3*i] | bmp_buffer[3*i+1]<<8 | bmp_buffer[3*i+2]<<16; 


	for(y=0;y<480;y++)
	{
	 	for(x=0;x<800;x++)
		{
			tmp_buffer[(479-y)*800+x] = lcd_buffer[y*800+x];
		}
	}	


	write(lcdfd,tmp_buffer,sizeof(tmp_buffer));
	
	close(bmp_fd);
	close(lcdfd);
	
	return 0;
	
}

//自定义函数，显示任意位置任意大小
/*
  坐标原点：（x，y）
  真实的高宽： （w，h）
  路径 ：const char *pathname
*/
int bmp_show_xy(int x,int y,int w,int h,const char *pathName)
{
  int lcd_fd; //屏幕描述符
	int bmp_fd;//图片文件描述符
	char bmpbuf[w*h*3]; //图片大小
	int lcdbuf[w*h];
	int i,j;
	int *lcdmmap;//内存映射的指针
  //准备lcd屏幕
  lcd_fd=open("/dev/fb0",O_RDWR);
  if(lcd_fd == -1)
  {
     perror("open lcd_fd false!\n");
	 return -1;
  }
  //准备图片 1.bmp
  bmp_fd=open(pathName,O_RDWR);
  if(bmp_fd == -1)
  {
	  perror("open bmp_fd false!\n");
	  return -1;
  }
  
  //将lcd屏幕的地址映射到用户空间
  lcdmmap=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd_fd,0);
    if(lcdmmap == NULL)
	{
	   perror("lcdmmap mmap false!\n");
	   return -1;
	}
	
  //读之前，先跳过前面54字节
  lseek(bmp_fd,54,SEEK_SET);
  //读取图片颜色值
  read(bmp_fd,bmpbuf,w*h*3);
  
  //将读取到的图片颜色3字节转化为4字节
  for(i=0;i<w*h;i++)
  {
	  //           B          G               R
     lcdbuf[i]=bmpbuf[3*i] | bmpbuf[3*i+1]<<8 | bmpbuf[3*i+2]<<16 | 0x00 <<24;
  }
  
for(i=0;i<w;i++)
  {
    for(j=0;j<h;j++)
	{
		//x,y屏幕起止坐标
		//i,j根据图片的宽高循环
		//w,h屏幕的宽高
		*(lcdmmap+(y+j)*800+x+i)=lcdbuf[(h-1-j)*w+i];
	}
  }

  //关闭文件
  close(lcd_fd);
  close(bmp_fd);
  //解除映射
  munmap(lcdmmap,800*480*4);
  return 0;
}