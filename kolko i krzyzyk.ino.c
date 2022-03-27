#include "ttt.hpp"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"


long long timeCounter = 0;

int counter = 0;

int board[9] = {0, 0, 2, 1, 2, 1, 0, 0, 1};
int setTime(int second);
int cursor;
int score[3];
bool joyPressed;
int player;
diodeState state;

byte sign0[8] = {
	0b00000,
	0b01110,
	0b10001,
	0b11111,
	0b10000,
	0b01110,
	0b00100,
	0b00010
};

const char* menuItems[]
{
    "1. Game",
    "2. Settings",
};
int menuSize = 2;

const char* settingsMenu[]
{
  "1. Set background   colour ",
  "2. Set text colour",
  "3. Set player one   colour",
  "4. Set player two   colour",
  "5. Set map colour",
  "6. Set cursor colour",
  "7. Set round time",
  "8. Set map size",
  "9. Set player one   sign",
  "0. Set player two   sign"
};
int settingsSize = 10;

void setup() 
{
  _initialize();
}

void loop() 
{
  _printMenu(menuItems, menuSize);
  char key = getKey();
  switch(key){
    case '1':
      _game();
      getKey();
      break;
    case '2':
      _settings(settingsMenu, settingsSize);
      break;
    default:
      key = getKey();
    break;
  }
}

