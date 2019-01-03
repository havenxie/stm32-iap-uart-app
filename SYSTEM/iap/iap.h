#ifndef __IAP_H_
#define __IAP_H_
#include "sys.h"

/* Define if use bkp save flag  -------------------------------*/
#define USE_BKP_SAVE_FLAG     1

#if (USE_BKP_SAVE_FLAG == 1)
  #define INIT_FLAG_DATA      0x0000  //默认标志的数据(空片子的情况)
#else
  #define INIT_FLAG_DATA      0xFFFF   //默认标志的数据(空片子的情况)
#endif
#define UPDATE_FLAG_DATA      0xEEEE   //下载标志的数据
#define UPLOAD_FLAG_DATA      0xDDDD   //上传标志的数据
#define ERASE_FLAG_DATA       0xCCCC   //擦除标志的数据
#define APPRUN_FLAG_DATA      0x5A5A   //APP不需要做任何处理，直接运行状态

#if (USE_BKP_SAVE_FLAG == 1)
  #define IAP_FLAG_ADDR    BKP_DR1
#else
  #define IAP_FLAG_ADDR   (uint32_t)(ApplicationAddress - 1024 * 2)//App区域和Bootloader区域共享信息的地址(暂定大小为2K)
#endif

#define IAP_FLASH_SIZE  0x3000//Bootloader区域大小
#define ApplicationAddress  (FLASH_BASE + IAP_FLASH_SIZE)//应用程序地址

void IAP_WriteFlag(uint16_t flag);
uint16_t IAP_ReadFlag(void);
void IAP_Init(void);
void IAP_Handle(u8 * cmd);
#endif
