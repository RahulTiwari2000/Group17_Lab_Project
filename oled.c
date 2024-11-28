#include "oled.h"
#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdio.h>
// Include your font header file here
#include "font.h"
uint8_t page;
uint8_t col;
uint8_t i;
uint8_t cursorX;
uint8_t cursorY;
static void I2C_WriteCommand(uint8_t command);
static void I2C_WriteData(uint8_t data);
void OLED_Init(void) {
    SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

    GPIO_PORTB_AFSEL_R |= 0x0C; // Enable alternate functions for PB2, PB3
    GPIO_PORTB_ODR_R |= 0x08;  // open-drain on SDA (PB3)
    GPIO_PORTB_DEN_R |= 0x0C;
    GPIO_PORTB_PCTL_R |= (3 << 8) | (3 << 12);
    I2C0_MCR_R = I2C_MCR_MFE;
    I2C0_MTPR_R = 7;          // Set clock speed (100 kHz)


    I2C_WriteCommand(0xAE); // Display OFF
    I2C_WriteCommand(0xD5); // Set display clock divide ratio/oscillator frequency
    I2C_WriteCommand(0x80); // Suggested ratio
    I2C_WriteCommand(0xA8); // Set multiplex ratio
    I2C_WriteCommand(0x3F); // 1/64 duty (height - 1)
    I2C_WriteCommand(0xD3); // Set display offset
    I2C_WriteCommand(0x00); // No offset
    I2C_WriteCommand(0x40); // Set start line address
    I2C_WriteCommand(0x8D); // Enable charge pump regulator
    I2C_WriteCommand(0x14);
    I2C_WriteCommand(0x20); // Set memory addressing mode
    I2C_WriteCommand(0x00); // Horizontal addressing mode
    I2C_WriteCommand(0xA1); // Set segment re-map (flip horizontal)
    I2C_WriteCommand(0xC8); // Set COM Output Scan Direction (flip vertical)
    I2C_WriteCommand(0xDA); // Set COM pins hardware configuration
    I2C_WriteCommand(0x12);
    I2C_WriteCommand(0x81); // Set contrast
    I2C_WriteCommand(0xCF);
    I2C_WriteCommand(0xD9); // Set pre-charge period
    I2C_WriteCommand(0xF1);
    I2C_WriteCommand(0xDB); // Set VCOMH de-select level
    I2C_WriteCommand(0x40);
    I2C_WriteCommand(0xA4); // Entire display ON
    I2C_WriteCommand(0xA6); // Set normal display (A7 for inverse)
    I2C_WriteCommand(0xAF); // Display ON

}
void OLED_Clear(void)
{
    for (page=0; page < 8; page++)
    {
        OLED_SetCursor(0, page);
        for (col=0; col < OLED_WIDTH; col++)
        {
            I2C_WriteData(0x00);
        }
    }
page=0;
col=0;
}
void OLED_SetCursor(uint8_t x, uint8_t y) {
    I2C_WriteCommand(0xB0 | y); // Set page address
    I2C_WriteCommand(0x00 | (x & 0x0F)); // Set lower column address
    I2C_WriteCommand(0x10 | (x >> 4)); // Set higher column address
}
void OLED_PrintChar(char c) {

        if (c < 32 || c > 126) {
            return;  // Invalid character, ignore
        }

        uint8_t i;
        for (i = 0; i < 5; i++) {

            I2C_WriteData(font[c - 32][i]);
        }


        cursorX += 6;

        if (cursorX >= 128) {
            cursorX = 0;
            cursorY += 8;

           if (cursorY >= 64) {
                cursorY = 0;
            }
        }

        OLED_SetCursor(cursorX, cursorY);

}
