#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <stdint.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_I2C_ADDRESS 0x3C

void OLED_Init(void);
void OLED_Clear(void);
void OLED_SetCursor(uint8_t x, uint8_t y);
void OLED_PrintChar(char c);
void OLED_PrintString(const char *str);
void OLED_PrintNumber(int num);
#endif
