## 智能家居
# 项目开发环境
Linux+Arm53+C语言

# 项目需求
   功能类别 功能名称 描述 家电控制模块
1、空调控制模块 信息显示 显示当前室内温度 自动控制 设置空调在某温度下自动开、关 
2、风扇控制模块 状态显示 风扇开、关 自动控制 设置风扇的档数
3、灯光控制模块 状态控制 灯光的开/关控制 亮度 正常、节能 
4、窗帘控制模块 自动开/关 根据室外的亮度自动开启/关闭窗帘 手动开/关 读取当前窗帘状态，手动开启/关闭 监控模块 
1、烟感监控 自动控制 超过限量烟雾浓渡报警 
2、红外监控 自动控制 有人非法闯进报警 
3、报警功能 自动控制 打开、关闭 
4、GPRS模块 信息收发 当有报警信息的时候，系统会自动将警报信息发送到指定的手机号码。
信息设定 设定接收信息的手机号 
5、访客视频对讲 状态显示 观察访客信息、自定义门锁开、关 娱乐模块 
1、收音机 状态控制 开、关 自定义 更换频道 自动调节声音 增大、减小 
2、家庭影院 灯光控制 亮度效果调节 自动调节声音 增大、减小 
3、音频播放 状态控制 开、关 自动调节声音 增大、减小 自定义模式 选择播放、随机播放、顺序播放、列表循环 
4、数码相册 状态控制 开、关 自定义模式 选择播放、随机播放、顺序播放、列表循环 场景切换 
1、在家模式 状态控制 家居电器开关、灯光亮度、监控状态 
2、离家模式 
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
 
# 效果图
1.主界面

![主界面][1]


2.登录界面

![登录界面][2]

3.应用首页

![应用首页][3]

4.文件浏览器

![文件浏览器][4]

5.音频/视频播放器

![音频/视频播放器][5]

6.视频播放示例

![视频播放示例][6]

7.摄像头

![摄像头][7]

8.摄像头抓拍

![摄像头抓拍][8]


  [1]: https://github.com/qinjiaw2019/shixun/blob/master/smartHome/shortcut/1.jpg
  [2]: https://github.com/qinjiaw2019/shixun/blob/master/smartHome/shortcut/2.jpg
  [3]: https://github.com/qinjiaw2019/shixun/blob/master/smartHome/shortcut/3.jpg
  [4]: https://github.com/qinjiaw2019/shixun/blob/master/smartHome/shortcut/4.jpg
  [5]: https://github.com/qinjiaw2019/shixun/blob/master/smartHome/shortcut/5.jpg
  [6]: https://github.com/qinjiaw2019/shixun/blob/master/smartHome/shortcut/6.jpg
  [7]: https://github.com/qinjiaw2019/shixun/blob/master/smartHome/shortcut/7.jpg
  [8]: https://github.com/qinjiaw2019/shixun/blob/master/smartHome/shortcut/8.jpg
