#include "sys.h"
#include "timer.h"

//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!边沿对齐，向上计数
/*******************************************/
//函数功能：定时器2输入捕获初始化及中断配置
//入口参数：自动重装载值arr，预分频系数psc
//返 回 值：无
/******************************************/
void TIM2_Int_Init(u16 arr,u16 psc)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC->APB1ENR|=1<<0;	//TIM2时钟使能    
 	TIM2->ARR=arr;  	//设定计数器自动重装值 
	TIM2->PSC=psc;  	//预分频器设置
	TIM2->DIER|=1<<0;   //允许更新中断	
	TIM2->CR1|=0x80;    //自动重装载预装载允许位置1，TIM2_ARR中的值被装入缓冲器
	//TIM2->CR1|=0x01;    //使能定时器2
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
  //	MY_NVIC_Init(1,3,TIM2_IRQn,2);//抢占1，子优先级3，组2		
	
	TIM2->CR1|=0x01;
	
}

void TIM2_IRQHandler(void)
{/**/	
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)//判断是否发生了更新(溢出)中断
    {
			 timer2_handler(TIMER_INT);
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除溢出中断标志位
    }

	timer2_handler(TIMER_RUN);
		
}

