#include "ArduinoAPI.hpp"

#pragma region keypad

char keys[ROWS][COLS] = {
  { '1', '2', '3'},
  { '4', '5', '6'},
  { '7', '8', '9'},
  { 'X', '0', 'O'}
};

Keypad keypad = Keypad(makeKeymap(keys), PadRows, PadCols, ROWS, COLS);



char getKey()
{
  char key;
  while(!(key = keypad.getKey()));
  return key;
}

#pragma endregion keypad


#pragma region LCD 

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void initLCD()
{
  lcd.begin(16,2);    
}

void printLCD(char* text, int digit)
{
  lcd.print(text);
  lcd.print(digit);
  lcd.setCursor(0,1);
}

void clearLCD()
{
  lcd.clear();
}

#pragma endregion LCD 

#pragma region Buzzer
void turnBuzzer(int freq, int duration){
  tone(9, freq, duration);
}
#pragma endregion Buzzer

#pragma region ardu

void delayTime(double time)
{
  delay(time);
}

long getMS(void)
{
  return millis();
}

void setPinValue(int pin, int value)
{
  digitalWrite(pin, value);
}

int getAPinValue(int pin)
{
  return analogRead(pin);
}

int getDPinValue(int pin)
{
  return digitalRead(pin);
}

void initRandom()
{
  randomSeed(analogRead(A7));
}

int randomNumber(int minValue, int maxValue)
{
  return random(minValue, maxValue);
}
#pragma endregion ardu



#pragma region joystick

void initJoystick()
{
  pinMode(VERT, INPUT);
  pinMode(HORZ, INPUT);
  pinMode(JOYB, INPUT_PULLUP);
}
#pragma endregion joystick

#pragma region ILI9341

Adafruit_ILI9341 display = Adafruit_ILI9341(display_CS, display_DC);

void printSingleChar(char sign)
{
  display.print(sign);
}

void drawLine(double x, displayColors color)
{  
  drawLine(x, 1, x, display.width()-2, color);  
  drawLine(1, x, display.width()-2, x, color); 
}

double getScreenWidth()
{
  return display.width();
}

double getScreenHeight()
{
  return display.height();
}

void drawCircle(double centerX, double centerY, double radius, displayColors color)
{
  display.drawCircle(centerX, centerY, radius, color);
}

void drawLine(double xStart, double yStart, double xEnd, double yEnd, displayColors color)
{
  display.drawLine(xStart, yStart, xEnd, yEnd, color); 
}

void setDisplayCursor(int x, int y)
{
  display.setCursor(x, y);
}

void setTextColor(displayColors color)
{
  display.setTextColor(color);
}

void setTextSize(double size)
{
  display.setTextSize(size);
}

void printLine(char* text)
{
  display.println(text);
}

void initDisplay()
{
  display.begin();
}
 
void setBackgroundColor(displayColors color)
{
  display.fillScreen(color);
}
#pragma endregion ILI9341