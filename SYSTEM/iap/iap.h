#ifndef __IAP_H_
#define __IAP_H_
#include "sys.h"

#define APPRUN_FLAG_DATA      0x0000   //APP不需要做任何处理，直接运行状态
#define INIT_FLAG_DATA        0xFFFF   //默认标志的数据(空片子的情况)
#define UPDATE_FLAG_DATA      0xEEEE   //下载标志的数据
#define UPLOAD_FLAG_DATA      0xDDDD   //上传标志的数据
#define ERASE_FLAG_DATA       0xCCCC   //擦除标志的数据

#define IAP_FLASH_SIZE  0x3000//Bootloader区域大小
#define IAP_FLASH_FLAG_ADDR  0x8002800//标志数据存放地址，存放在Bootloader区域内
#define ApplicationAddress  (FLASH_BASE + IAP_FLASH_SIZE)//应用程序地址

void IAP_FLASH_WriteFlag(u16 flag);
u32 IAP_FLASH_ReadFlag(void);
void IAP_Init(void);
void IAP_Handle(u8 * cmd);
#endif
