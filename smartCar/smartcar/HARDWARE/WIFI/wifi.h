#ifndef __WIFI_H
#define __WIFI_H 	
#include "sys.h"


typedef int bool;

#define OK 0
#define ERROR 1

#define u32 unsigned int 
#define u16 unsigned short
#define u8 unsigned char
void WifiChek_Init(u32 bound);
void usrc210_send(char *str);
char * usrc210_response();	
void usrc210_send_ch(u8 ch);
extern void usart_handler(int usartx,int state);
#endif