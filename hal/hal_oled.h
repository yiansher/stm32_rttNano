#ifndef __HAL_OLED_H__
#define __HAL_OLED_H__

#include "main.h"
#include "u8g2.h"
#include "spi.h"

#define MD_OLED_RST_Clr() HAL_GPIO_WritePin(RESET_GPIO_Port,RESET_Pin,GPIO_PIN_RESET) //oled ��λ�˿ڲ���
#define MD_OLED_RST_Set() HAL_GPIO_WritePin(RESET_GPIO_Port,RESET_Pin,GPIO_PIN_SET)

void draw(u8g2_t *u8g2);
void u8g2Init(u8g2_t *u8g2);
void screen_task(void);

#endif
