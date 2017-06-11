#include "iap.h"
#include "stmflash.h"
#include <string.h>
void IAP_FLASH_WriteFlag(u16 flag) 
{
	FLASH_Unlock();
	STMFLASH_Write(IAP_FLASH_FLAG_ADDR, &flag, 1);
	FLASH_Lock();
}

u32 IAP_FLASH_ReadFlag(void)
{
	return STMFLASH_ReadHalfWord(IAP_FLASH_FLAG_ADDR);   
}

void IAP_Init(void)
{
	u16 clearFlag = 0x0000;  //标志为运行状态
	IAP_FLASH_WriteFlag( clearFlag );//清除IAP升级标志
	NVIC_SetVectorTable(ApplicationAddress, IAP_FLASH_SIZE);//设置中断向量表
}

void IAP_Handle(u8 * cmd)
{
	if(strcmp((char *)cmd, "update") == 0)
	{
		IAP_FLASH_WriteFlag(UPDATE_FLAG_DATA);
		NVIC_SystemReset();
	}
	else if(strcmp((char *)cmd, "erase") == 0)
	{
		IAP_FLASH_WriteFlag(ERASE_FLAG_DATA);
		NVIC_SystemReset();		
	}
	else if(strcmp((char *)cmd, "menu") == 0)
	{
		IAP_FLASH_WriteFlag(INIT_FLAG_DATA);
		NVIC_SystemReset();	
	}
	else if(strcmp((char *)cmd, "runapp") == 0)//reset
	{
		NVIC_SystemReset();	
	}
	else
	{
		//printf("指令有误\r\n");
		NVIC_SystemReset();	
	}
}

