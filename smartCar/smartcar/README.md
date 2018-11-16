# 嵌入式实训之 智能小车超声波壁障
# 开发环境
kei5 + webstorm
# 开发语言
C + nodejs

# 基本功能
1.电机驱动
控制小车，前进、后退、停止、左转、右转等等。
2.超声波测距
测量出小车与障碍物之间的距离，进而让小车自动避开障碍物继续前进。
3.语音播报（JQ8400）
播报指定的语音，达到人机交互与娱乐。
4.WIFI模块
实时显示小车的当前的运行状态。


# 整体架构
   通过超声波车距和电机驱动判断小车当前所处的状态(前进，后退，左转弯，右转弯等。通过WIFI透传讲小车状态数据送到WEB界面(客户端等)进行实时查看

![此处输入图片的描述][1]


# 项目使用的模块和技术
1. STM32F4 C语言编程
2. 电机驱动
3. 语音模块(行进提示)
4. wifi模块透传功能(数据传输)
5. 串行化技术(数据格式  len1.state1,len2.state2,...lenN.stateN)
6. nodejs 开发web客户端
len1,len2...lenN.stateN 表示 障碍物距离.小车当前的状态

# 工程源码结构
```
    |--CORE
    |--PWLIB
    |--HARDWARE 模块封装
        |--HCSR04 超声波模块
        |--HMI    液晶屏模块
        |--JQ8400 语音模块
        |--KEY    按键模块
        |--LED    LED模块
        |--MOTOR  电机模块
        |--PATH   小车壁障算法
        |--WIFI   wifi模块
        |--TIMER  定时器模块
    |--web        WEB界面
```

# 小车PCB图

![此处输入图片的描述][2]


# 壁障算法 原理

1.向右转判断

![此处输入图片的描述][3]

2.向左转判断

![此处输入图片的描述][4]

1.记录小车进入安全区临界点与障碍物的距离L1
2.小车试探性向左转一定的角度记录距离L2
3.两次的位移差记录为L3
4.由于转换角度很小，并且在很短的时间内完成因此
可以忽略小车变化的位移.
5.若L1>L2则表示小车左转试探出错，因右转
6.若L1<L2则表示小车左转试探正确

电路分析：请查看博客[https://blog.csdn.net/qq_39188039/article/details/84131633][5]


  [1]: https://github.com/qinjiaw2019/shixun/blob/master/smartCar/smartcar/shotcut/1.png
  [2]: https://github.com/qinjiaw2019/shixun/blob/master/smartCar/smartcar/shotcut/2.png
  [3]: https://github.com/qinjiaw2019/shixun/blob/master/smartCar/smartcar/shotcut/3.png
  [4]: https://github.com/qinjiaw2019/shixun/blob/master/smartCar/smartcar/shotcut/4.png
  [5]: https://blog.csdn.net/qq_39188039/article/details/84131633