#include "hcsr04.h"
#include "delay.h"
#include "sys.h"
u16 msHcCount = 0;//ms计数
#define TRIG_Send  PBout(14) 
#define ECHO_Reci  PBin(15)


//定时器初始化
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //①使能 TIM3 时钟
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; //自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);// ②初始化定时器 TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //③允许定时器 3 更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器 3 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //响应优先级 3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// ④初始化 NVIC 
	TIM_Cmd(TIM3,DISABLE); //关闭定时器
}
/**
	HCSR04初始化
*/
void hcsr04_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//触发信号

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	
	//回响信号
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//输出功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	
	TIM3_Int_Init(1000-1,72-1);
}
//定时器 3 中断服务函数
void TIM3_IRQHandler(void)
{

	 if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
        {
                TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
                msHcCount++;
        }

}
/**
	打开定时器
*/
void openTime()
{
	TIM_Cmd(TIM3,0); //打开定时器
	msHcCount = 0;
	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
}
/**
	关闭定时器
*/
void closeTime()
{
	TIM_Cmd(TIM3, DISABLE);  //使能TIMx外设
}

/**
	测量距离
*/
float hcsr04_measure()
{

	u32 t = 0;
		int i = 0;
		float lengthTemp = 0;
		float sum = 0;
		while(i!=5)
		{
		TRIG_Send = 1;      //发送口高电平输出
		delay_us(10);
		TRIG_Send = 0;
		while(ECHO_Reci == 0);//等待接收口高电平输出
			openTime();        //打开定时器
			i = i + 1;
			while(ECHO_Reci == 1);
			closeTime();        //关闭定时器
			t = TIM_GetCounter(TIM2);
			// distance = measurement/2/1000*340 = measurement/59 (cm)  measurement-units:us
			lengthTemp = (t+msHcCount*1000)/58.8;
			sum = lengthTemp + sum ;
			
			TIM2->CNT=0; //将TIM2计数寄存器的计数值清零
			msHcCount=0; //中断溢出次数清零
	}
		lengthTemp = sum/5.0;
		return lengthTemp;
}