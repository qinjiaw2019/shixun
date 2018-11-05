### 智能家居

```
项目源码结构:
    |--bin            脚本目录
        |--tar.sh     项目打包脚本
    |--data           数据目录
    |--include        头文件
        |--beep.h     蜂鸣器模块
        |--bmp.h      BMP图模块
        |--config.h   项目配置文件
        |--file.h     文件操作模块
        |--jpeg.h     JPG图模块
        |--led.h      LED模块
        |--mp3.h      音频模块
        |--mplayer.h  音频库模块
        |--res.h      资源配置文件
        |--tslib.h    触摸模块
        |--ui.h       UI模块
        |--vedio.h    视频模块
    |--lib            库文件
    |--pic            资源图片
        |--icon       应用图标
        |--ui         UI文件
    |--shortcut       项目效果图
    |--ext            第三方库
        |--driver     驱动
        |--lib        第三方库
    |--src            代码目录
        |--main.c     主程序
        |--Makfile    自动编译脚本
```

 ## 项目安装 ##
 ```
 1.下载smart.tar.gz到CRT中，解压
 2.执行install.sh安装相应的驱动，和项目的初始化
 3.执行run.sh 运行项目
 ```