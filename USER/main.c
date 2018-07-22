#include "led.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "stmflash.h"
#include "usmart.h"
#include "iap.h"

int main(void)
{	 
	u16 i=0;
	IAP_Init();
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	 //串口初始化为9600
 	LED_Init();			     //LED端口初始化
	LCD_Init();	             //初始化LCD
	usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART
	   
	printf("\r\n 输入:help查询指令\r\n");	
	while(1)
	{
		i++;
		delay_ms(10);  
		if(i==20)
		{
			LED0=!LED0;//提示系统正在运行	
			i=0;
		}		   
	}   	   
}


