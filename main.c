#include "oled.h"
#include <stdio.h>
#include "font.h"
int main(void) {
    OLED_Init();
    OLED_Clear();
    OLED_SetCursor(0, 0);
    OLED_PrintString(" 28/11/2024 ");
    while (1);
}
