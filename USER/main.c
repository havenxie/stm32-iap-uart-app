#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "stmflash.h"
#include "usmart.h"
//ALIENTEK战舰STM32开发板实验34
//FLASH模拟EEPROM 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

//要写入到STM32 FLASH的字符串数组
const u8 TEXT_Buffer[]={"STM32 FLASH TEST"};
#define SIZE sizeof(TEXT_Buffer)	 			  	//数组长度
#define FLASH_SAVE_ADDR  0X08070000 				//设置FLASH 保存地址(必须为偶数)


 int main(void)
 {	 
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
	 
	u16 clearFlag = 0x0000;//app run state
	NVIC_SetVectorTable(0X8000000, 0X3000);//设置中断向量表
	STMFLASH_Write(IAP_FLASH_FLAG_ADDR, &clearFlag, 1);//清除IAP升级标志
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART
	 
 	LED_Init();			     //LED端口初始化
	LCD_Init();	         //初始化LCD
	KEY_Init();	 		 //初始化KEY
		
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"FLASH EEPROM TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2012/9/13");  
	LCD_ShowString(60,130,200,16,16,"WK_UP:Write KEY1:Read");
	POINT_COLOR=BLUE;
	//显示提示信息
	POINT_COLOR=BLUE;//设置字体为蓝色
	//FLASH_SetLatency(FLASH_ACR_LATENCY_2);	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY_UP)//WK_UP按下,写入STM32 FLASH
		{
			LCD_Fill(0,150,239,319,WHITE);//清除半屏    
 			LCD_ShowString(60,150,200,16,16,"Start Write FLASH....");
			STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
			LCD_ShowString(60,150,200,16,16,"FLASH Write Finished!");//提示传送完成
		}
		if(key==KEY_DOWN)//KEY1按下,读取字符串并显示
		{
 			LCD_ShowString(60,150,200,16,16,"Start Read FLASH.... ");
			STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
			LCD_ShowString(60,150,200,16,16,"The Data Readed Is:  ");//提示传送完成
			LCD_ShowString(60,170,200,16,16,datatemp);//显示读到的字符串
		}
		i++;
		delay_ms(10);  
		if(i==20)
		{
			LED0=!LED0;//提示系统正在运行	
			i=0;
		}		   
	}   	   
}


