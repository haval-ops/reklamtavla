#ifndef LCD_H
#define LCD_H

#include <string>
#include "ads.h"

void lcdInit();
void lcdClear();
void lcdSetCursor(int col, int row);
void lcdPrint(const std::string& text);

void showAdOnLcd(const AdMessage& ad, const std::string& customerName, int durationSeconds);

#endif
