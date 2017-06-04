#include "led.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "stmflash.h"
#include "usmart.h"

int main(void)
{	 
	u16 i=0;
	u16 clearFlag = 0x0000;  //标志为运行状态
	NVIC_SetVectorTable(0X8000000, 0X3000);//设置中断向量表
	STMFLASH_Write(IAP_FLASH_FLAG_ADDR, &clearFlag, 1);//清除IAP升级标志
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	 //串口初始化为9600
 	LED_Init();			     //LED端口初始化
	LCD_Init();	             //初始化LCD
	usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART
	 
 	POINT_COLOR=RED;         //设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"STM32-IAP-APP");	
	LCD_ShowString(60,90,200,16,16,"Haven Xie");
	LCD_ShowString(60,110,200,16,16,"2017/6/4");  
	 
    printf("输入:help查询指令\r\n");	
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


