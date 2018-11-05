#include "login.h"

//返回控制变量
int login_back = -1;



//按键控制,获取按键值
int login_play()
{
	if(sam.pressure>=0)
		if(sam.x>=252 && sam.x<=341 && sam.y>=156 && sam.y<=226)// 1
			return BTN_NUMBER_1;
		else if(sam.x>=370 && sam.x<=434 && sam.y>=156 && sam.y<=226)//2
			return BTN_NUMBER_2;
		else if(sam.x>=471 && sam.x<=519 && sam.y>=156 && sam.y<=226)//3
			return BTN_NUMBER_3;
			
		else if(sam.x>=252 && sam.x<=341 && sam.y>=253 && sam.y<=294)//4
			return BTN_NUMBER_4;
		else if(sam.x>=370 && sam.x<=434 && sam.y>=253 && sam.y<=294)//5
			return BTN_NUMBER_5;
		else if(sam.x>=471 && sam.x<=519 && sam.y>=253 && sam.y<=294)//6
			return BTN_NUMBER_6;
			
		else if(sam.x>=252 && sam.x<=314 && sam.y>=317 && sam.y<=371)//7
			return BTN_NUMBER_7;
		else if(sam.x>=370 && sam.x<=434 && sam.y>=317 && sam.y<=371)//8
			return BTN_NUMBER_8;
		else if(sam.x>=471 && sam.x<=519 && sam.y>=317 && sam.y<=371)//9
			return BTN_NUMBER_9;
			
		//else if(sam.x>=252 && sam.x<=341 && sam.y>=382 && sam.y<=460)//del
			//return BTN_NUMBER_DEL;
		else if(sam.x>=370 && sam.x<=434 && sam.y>=382 && sam.y<=460)//0
			return BTN_NUMBER_0;
		else if(sam.x>=471 && sam.x<=519 && sam.y>=382 && sam.y<=460)//cancel
			return BTN_NUMBER_CANCEL;
		else 
			return BTN_NUMBER_ERROR;
	else 
			return BTN_NUMBER_ERROR;
}

//显示密码提示字符
void show_pass_flag(int i)
{
	if(i==0)//密码字符为0时
		bmp_show_xy(353,94,100,36,"../pic/ui/pass_0.bmp");
	else if(i==1 || i==2)//密码字符为1时
		bmp_show_xy(353,94,100,36,"../pic/ui/pass_1.bmp");
	else if(i==3 || i==4)//密码字符为2时
		bmp_show_xy(353,94,100,36,"../pic/ui/pass_2.bmp");
	else if(i==5 || i==6)//密码字符为3时
		bmp_show_xy(353,94,100,36,"../pic/ui/pass_3.bmp");
	else if(i==7 || i==8)//密码字符为4时
		bmp_show_xy(353,94,100,36,"../pic/ui/pass_4.bmp");
	else if(-1)//密码错误
		bmp_show_xy(353,94,100,36,"../pic/ui/pass_err.bmp");
}

int check_pass(char *s)
{
	int i=0;//0 1 2 3 4 5 6 7
	int j=0;
	int k = 0;
	while(i<8)
	{
		if(system_pass[j]==s[i])
		{
			k++;
		}
		i+=2;j++;
	}
	if(k==4)//登录成功
	{
		is_login = LOGINED;
		login_back = BACK;
		return 0;
	}
		
	else //登录失败
	{
		show_pass_flag(-1);//密码错误提示

	
		return -1;
	}
	
}

void show_login()
{
	char password[9] = {0};//临时存储按键输入的密码
	
	int pass_len = 0;//密码输入个数
	int pass_err = 0;//密码错误次数
	int i=0,k=1;
	bmp_show(IMG_LOGIN_BG);	
	sam.x = sam.y = -1;
	login_back = -1;
	show_pass_flag(0);
	while(login_back==-1)
	{
		
		ts_read(ts,&sam);
		
		int btn_num = login_play();

		if(btn_num!=BTN_NUMBER_ERROR )//如果按键有效
		{

	
				if(btn_num==BTN_NUMBER_CANCEL)//取消
				{
					pass_len = 0;
					password[0] = '\0';
					stpcpy(password,"");
					show_pass_flag(0); //12 34 56 78  
				}else {
					if(pass_len<8)
					{
						password[pass_len] = btn_num+'0';
						show_pass_flag(pass_len+1);
						pass_len+=1;
						
					}	
				}
	
		}
		if(pass_len>=7)	
			pass_err = check_pass(password);
		
	/*
		if(pass_err==-1){
					printf("err-----%d \n",pass_err);
					sleep(5);
					show_pass_flag(0);
					pass_err = 0;
					
			}
			*/
		
	}
}