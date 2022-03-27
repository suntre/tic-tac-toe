#ifndef API_HPP

#define API_HPP
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <ctype.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
const uint8_t PadRows[] = { 14, 15, 16, 17 };
const uint8_t PadCols[] = { 18, 19, 20};

#define ROWS 4
#define COLS 3
#define display_CS 53
#define display_DC 49
#define COLON 30

#define VERT A0
#define HORZ A1
#define JOYB 13

#define LCD_RS 45
#define LCD_E 44
#define LCD_D4 43
#define LCD_D5 42
#define LCD_D6 41
#define LCD_D7 40

enum diodes{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3,
  LED5 = 4,
  LED6 = 5,
  LED7 = 6,
  LED8 = 7
};


enum displayColors{
  white = ILI9341_WHITE,
  green = ILI9341_GREEN,
  red = ILI9341_RED,
  blue = ILI9341_BLUE,
  cyan = ILI9341_CYAN,
  yellow = ILI9341_YELLOW,
  orange = ILI9341_ORANGE,
  black = ILI9341_BLACK,
  purple = ILI9341_PURPLE
};

void printSS(int score);

void initSS();

void printLCD(char* text, int digit);

void turnBuzzer(int freq, int duration);

void clearLCD();

void delayTime(double time);

long getMS(void);

void setPinValue(int pin, int value);

int getAPinValue(int pin);

int getDPinValue(int pin);

void initLCD();

void initDisplay();

void setDisplayCursor(int x, int y);

void setTextColor(displayColors color);

void setTextSize(double size);

void printLine(char* text);

void setBackgroundColor(displayColors color);

char getKey();

void printSingleChar(char sign);

void drawLine(double x, displayColors color);

void drawSingleLine(double x, double y, double x2, double y2, displayColors color);

double getScreenWidth();

double getScreenHeight();

void drawCircle(double centerX, double centerY, double radius ,displayColors color);

void drawLine(double xStart, double yStart, double xEnd, double yEnd, displayColors color);

int randomNumber(int minValue, int maxValue);

void initRandom();

void initJoystick();

#endif