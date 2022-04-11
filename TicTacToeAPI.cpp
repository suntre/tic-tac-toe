#include "TicTacToeAPI.hpp"
#include "ArduinoAPI.hpp"
#include <Arduino.h>

enum joypos
{
 joyLeft = 1023,
 joyRight = 0,
 joyTop = 1023,
 joyBottom = 0
};

const char* colors[]
{
  "1. black",
  "2. white",
  "3. red",
  "4. blue",
  "5. cyan",
  "6. yellow",
  "7. orange",
  "8. green"
};

displayColors colorSetup[] = 
{
  black,
  white, 
  cyan, 
  green, 
  red, 
  blue 
};

enum colorOrder
{
  bgColor = 0,
  txtColor = 1,
  p1Color = 2,
  p2Color = 3,
  mapColor = 4,
  cursorColor = 5
};

enum signs
{
  cross = 1,
  circle = 2
};

enum players
{
  player1 = 1,
  player2 = 2
};

enum botType
{
  easy = 1,
  medium = 2
};

int mapSize = 3;

int colorsSize = 8; 
int p1Sign = cross;
int p2Sign = circle; 
int roundTime = 15; 
double width;
double height;  
int dif = 1; 

int charToInt(char sign)
{
  return sign - '0';
}

char* intToChar(int digit)
{
  char* result;
  while(digit > 0)
  {
    char* tmp = digit % 10 + '0';
    strcat(tmp, result);
    digit = digit / 10;
  }
  return result;
}

void setScore(int *score)
{
  clearLCD();
  printLCD("Player 1  : ", score[player1]);
  printLCD("Player 2  : ", score[player2]);
}

void setScreenSize()
{
  height = getScreenHeight();
  width = getScreenWidth();
}

void setColors()
{
  setBackgroundColor(colorSetup[bgColor]);
  setTextColor(colorSetup[txtColor]);
}

void lightDiodes()
{
  for(int i = LED1; i <= LED8; i++)
  {
    setPinValue(i, HIGH);
    delayTime(300);
    setPinValue(i, LOW);
  }
}

void drawCursor(double x, double y, double width)
{
  for(int i = 0; i < 4; i++)
  {
    drawLine(x, y + i, x + width, y + i, colorSetup[cursorColor]);
    drawLine(x + i, y, x + i, y + width, colorSetup[cursorColor]);
    drawLine(x + width - i, y, x + width - i, y + width, colorSetup[cursorColor]);
    drawLine(x, y + width - i, x + width, y + width - i, colorSetup[cursorColor]);
  }
}

void findLeftCorner(double* leftCornerX, double* leftCornerY, double* squareWidth, int cursor)
{
  *squareWidth = width / mapSize;
  int yPointer = cursor / mapSize;
  int xPointer = cursor % mapSize;
  *leftCornerX = *squareWidth * xPointer;
  *leftCornerY = *squareWidth * yPointer;
}

void drawO(int cursor, displayColors color)
{
  double squareWidth, leftCornerX, leftCornerY;
  findLeftCorner(&leftCornerX, &leftCornerY, &squareWidth, cursor);
  double rightCornerX = leftCornerX + squareWidth;
  double rightCornerY = leftCornerY + squareWidth;
  double x = (leftCornerX + rightCornerX) / 2;
  double y = (leftCornerY + rightCornerY) / 2;
  double radius = squareWidth / 4;
  for(int i = 0; i < 4; i++) drawCircle(x, y, radius+i, color);
}

void drawX(int cursor, displayColors color)
{
  double squareWidth, leftCornerX, leftCornerY;
  findLeftCorner(&leftCornerX, &leftCornerY, &squareWidth, cursor);
  double topX = leftCornerX + squareWidth / 4;
  double topY = leftCornerY + squareWidth / 4;
  for(int i = 0; i < 4; i++) drawLine(topX + i, topY, topX + squareWidth/2 + i, topY + squareWidth / 2, color);
  topX += squareWidth / 2;
  for(int i = 0; i < 4; i++) drawLine(topX + i, topY, topX - squareWidth/2 + i, topY + squareWidth / 2, color);
}

void newMapSize()
{
  setColors();
  setTextSize(2);
  setDisplayCursor(0, 40);
  printLine("Click number to chose size NxN");
  printLine("Possible range between 2 and 9");
  char key = getKey();
  while(key < '2' || key > '9') key = getKey();
  mapSize = charToInt(key);
}

void setTime(unsigned long* interval, diodeState* state)
{
  *state = ST_WAIT;
  (*interval) = roundTime*1000 / 8;
}

void welcomeScreen()
{
  setDisplayCursor(50, 60);
  setTextSize(3);
  setTextColor(cyan);
  printLine("Welcome");
  setDisplayCursor(100, 100);
  printLine("in");
  setDisplayCursor(20, 140);
  setTextColor(red);
  printLine("Tic Tac Toe");
  setTextColor(cyan);
  setTextSize(2);
  setDisplayCursor(50, 200);
  printLine(VERSION);
  lightDiodes();
}

void drawMap()
{
  double w = width / mapSize;
  setBackgroundColor(colorSetup[bgColor]);
  for(int i = 1; i < mapSize; i++)
  { 
    for(int j = 0; j < 3; j++) drawLine(w * i + j, colorSetup[mapColor]);
  }
}

void fillMap(int* board)
{
  for(int i = 0; i < mapSize*mapSize; i++) 
  {
    if(board[i] == player1)
    {
     if(p1Sign == cross) drawX(i, colorSetup[p1Color]);
     else drawO(i, colorSetup[p1Color]);
    }
    else if(board[i] == player2)
    {
      if(p2Sign == cross) drawX(i, colorSetup[p2Color]);
      else drawO(i, colorSetup[p2Color]);
    }
  }
}

displayColors newColor()
{
  setColors();
  setDisplayCursor(0, 60);
  for(int i = 0; i < colorsSize; i++)
  {
    printLine(colors[i]);
  }
  char key = NULL;
  while(!key || key == 'X' || key == 'O' || key == '9' || key == '0')
  {
    key = getKey();
    switch(key){
      case '1':
        return black;
        break;
      case '2':
        return white;
        break;
      case '3':
        return red;
        break;
      case '4':
         return blue;
        break;
      case '5':
        return cyan;
        break;
      case '6':
        return yellow;
        break;
      case '7':
        return orange;
        break;
      case '8':
        return green;
        break;
      default:
        break;
    }
  }
}

int randPosition(int* board)
{
  int i = 0;
  while(board[i] != 0) i = randomNumber(0, mapSize * mapSize);
  return i;
}


void newTime()
{
  setColors();
  setTextSize(2);
  setDisplayCursor(0, 100);
  printLine("Enter new round time");
  printLine("Press 'X' to go back");
  printLine("Or 'O' to confirm");
  printLine("");
  char key;
  int newTime = 0;
  int i = 0;
  do
  {
    key = getKey();
    if(key != 'X' && key != 'O')
    {
      
      newTime = newTime * 10 + charToInt(key);
      printSingleChar(key);
    }
  } while(key != 'X' && key != 'O');
  if(key == 'O') roundTime = newTime;
}
signs newSign()
{
  setColors();
  setDisplayCursor(0, 100);
  printLine("1. Circle");
  printLine("2. Cross");
  char key;
  do{
    key = getKey();
  }while(key != '1' && key != '2');
  (key == 1) ? circle : cross;
}

bool checkMove(int pos, int* board)
{
  if(board[pos] == 0) return true;
  else return false;
}

int almostWon(int* board, int player)
{
  int counter;
  int target = mapSize - 1;
  for(int i = 0; i < mapSize; i++)
  {
    counter = 0;
    for(int j = 0; j < mapSize; j++)
    {
      if(board[mapSize * i + j] == player) counter++;
      else if(counter < j) break;
    }
    if(counter == target)
      for(int j = 0; j < mapSize; j++)
        if(board[mapSize * i + j] == 0) return mapSize * i + j;
  }

  for(int i = 0; i < mapSize; i++)
  {
    counter = 0;
    for(int j = 0; j < mapSize; j++)
    {
      if(board[i + mapSize * j] == player) counter++;
      else if(counter < j) break;
    }
    if(counter == target) 
      for(int j = 0; j < mapSize; j++)
        if(board[i + mapSize * j] == 0) return i + mapSize * j;
  }

  counter = 0;
  for(int i = 0; i < mapSize; i++)
  {
    if(board[(mapSize + 1) * i] == player) counter++;
    else if(counter < i) break;
  }
  if(counter == target) 
    for(int i = 0; i < mapSize; i++)
      if(board[(mapSize + 1) * i] == 0) return (mapSize + 1) * i;

  counter = 0;
  for(int i = 1; i <= mapSize; i++)
  {
    if(board[(mapSize - 1) * i]) counter++;
    else if(counter < i - 1) break;
  }
  if(counter == target)
    for(int i = 1; i <= mapSize; i++)
      if(board[(mapSize - 1) * i] == 0) return (mapSize - 1) * i;

  return -1;
}


bool hasDrawn(int* board)
{
  int draw = 1;
  for(int i = 0; i < mapSize*mapSize; i++) if(board[i] == 0) draw = 0;
  if(draw == 0) return false;
  return true;
}

int gameType()
{
  setColors();
  setDisplayCursor(0, 100);
  printLine("Choose game type");
  printLine("1.Player vs Computer");
  printLine("2.Player vs Player");
  char key;
  do
  {
    key = getKey();
  }while(key != '1' && key != '2');
  return charToInt(key);
}

void nextTurn(int* player, int* counter, long long* timeCounter, diodeState* state)
{
  *player == player1 ? *player = player2 : *player = player1;
  if(*counter >= 8)
  {
    turnBuzzer(60, 100);
  }
  *counter = 0;
  for(int i = LED1; i< 9; i++) setPinValue(i, HIGH);
  *state = ST_WAIT;
  *timeCounter = getMS();
}


int dificulty()
{
  setColors();
  setDisplayCursor(0, 100);
  printLine("Choose dificulty");
  printLine("1. Easy");
  printLine("2. Medium");

  char key;
  do{
    key = getKey();
  }while(key < '1' && key > '2');
  return charToInt(key);
}

void drawWinner(int start, int stop)
{
    double squareWidth, leftCornerX, leftCornerY;
    findLeftCorner(&leftCornerX, &leftCornerY, &squareWidth, start);
    double leftCornerXEnd, leftCornerYEnd;
    findLeftCorner(&leftCornerXEnd, &leftCornerYEnd, &squareWidth, stop);
    for(int i = 0; i < 10; i++)
      drawLine(squareWidth / 2 + leftCornerX + i , squareWidth / 2 + leftCornerY + i, squareWidth / 2 + leftCornerXEnd + i , squareWidth / 2 + leftCornerYEnd + i, purple);
}


bool hasWon(int* board, int position, int player)
{
  int row = position / mapSize;
  int counter = 0;
  for(int i = 0; i < mapSize; i++)
    if(board[mapSize * row + i] == player) counter++;  
  if(counter == mapSize)
  {
   drawWinner(mapSize * row + 0, mapSize * row + mapSize - 1);
   return true;
  }
  int col = position % mapSize;
  counter = 0;
  for(int i = 0; i < mapSize; i++)
    if(board[col + mapSize * i] == player) counter++;
  if(counter == mapSize)
  {
    drawWinner(col, col + mapSize * (mapSize - 1));
    return true;
  }
  if(position % (mapSize + 1) == 0)
  {
    counter = 0;
    for(int i = 0; i < mapSize; i++)
      if(board[(mapSize + 1) * i] == player) counter++;
  }
  if(counter == mapSize)
  {
    drawWinner(0, mapSize * mapSize - 1);
    return true;
  }
  if(position % (mapSize - 1) == 0) 
  {
    counter = 0;
    for(int i = 1; i <= mapSize; i++)
      if(board[(mapSize - 1) * i] == player) counter++;
    
  }
  if(counter == mapSize)
  {
    drawWinner(mapSize - 1, mapSize * (mapSize - 1));
    return true;
  }
  return false;
}

void getPosition(int* cursor, bool* joyPressed)
{
  if(getAPinValue(HORZ) == joyLeft) if(*cursor > 0) (*cursor)--; else *cursor = (mapSize*mapSize)-1;
  
  else if(getAPinValue(HORZ) == joyRight) if(*cursor < mapSize*mapSize - 1) (*cursor)++; else *cursor == 0; 
  else if(getAPinValue(VERT) == joyTop)
  {
    if(*cursor == 0 ) *cursor = mapSize * mapSize - 1;
    else if(*cursor < mapSize) *cursor = (*cursor - 1) %mapSize + mapSize*mapSize - mapSize;
    else *cursor -= mapSize;
  }
  else if(getAPinValue(VERT) == joyBottom)
  {
    if(*cursor >= mapSize*mapSize - mapSize) *cursor = (*cursor % mapSize + 1) % mapSize;
    else *cursor += mapSize;
  }
  if(getDPinValue(JOYB) == LOW) *joyPressed = true;
}

int botMove(int* board)
{
  if(dif == 1)
  {
    int i = randPosition(board);
    board[i] = player2;
    return i;
  }
  else
  {
    int value = almostWon(board, player2);
    if(value != -1)
    { 
      board[value] = player2;
      return value;
    }
    else
    {
      value = almostWon(board, player1);
      if(value != -1)
      {
        board[value] = player2;
        return value;
      }
      else
      {
        int i = randPosition(board);
        board[i] = player2;
        return i;
      }
    }
  }
}

void displayCursor(int cursor, int* board)
{
  setColors();
  drawMap();
  fillMap(board);
  double squareWidth, leftCornerX, leftCornerY;
  int yPointer, xPointer;
  findLeftCorner(&leftCornerX, &leftCornerY, &squareWidth, cursor);
  drawCursor(leftCornerX + 4, leftCornerY + 4, squareWidth - 8);
}

void setDiode(diodeState* state, int* counter, unsigned long interval, long long* timeCounter)
{
    switch (*state) {
    case ST_COUNT:
      setPinValue(*counter,LOW);
      (*counter)++;
      *state = ST_WAIT;
      break;
    case ST_WAIT:
      if(getMS() - *timeCounter  > interval)
      {
        *state = ST_COUNT;
        *timeCounter = getMS();
      }
      break;
  }
} 

bool nextRound()
{
  delayTime(1500);
  setColors();
  setDisplayCursor(0, 100);
  printLine("Next Round?");
  printLine("X = NO O = YES");
  char key;
  do
  {
    key = getKey();
  }while(key != 'X' && key != 'O');
  if(key == 'O') return true;
  return false;
}

void newRound(int* cursor, int* board, int* score)
{
  *cursor = 0;
  for(int i = 0; i < mapSize*mapSize; i++) board[i] = 0;
  setScore(score);
}

void result(int player){
  setColors();
  setDisplayCursor(50, 100);
  if(player == player1) printLine ("Player 1 Win");
  else if(player == player2) printLine("Player 2 Win");
  else printLine("Draw");
  setDisplayCursor(0, 160);
  printLine("Press Any key...");
  getKey();
}


void _initialize()
{
  initRandom();
  initDisplay();
  welcomeScreen();
  delayTime(2000);
  setScreenSize();
  initJoystick();
  initLCD();
}

void _printMenu(char** menuItems, int menuSize)
{
  setColors();
  setTextSize(3);
  setDisplayCursor(0, 80);
  for(int i = 0; i < menuSize; i++) printLine(menuItems[i]);
  setTextSize(2);
  setDisplayCursor(0,250);
  printLine("Press number to");
  printLine("choose option");
}

void _settings(char** settings, int settingsSize)
{
  char key;
  do
  {
    setColors();
    setDisplayCursor(0,0);
    printLine("Settings:");
    setTextSize(2);
    for(int i = 0; i < settingsSize; i++) printLine(settings[i]);
    setDisplayCursor(0, 280);
    printLine("Press 'X' to go back");
    key = getKey();
    if('1' <= key && key < '7') colorSetup[charToInt(key) - 1] = newColor();
    else if(key == '7') newTime();
    else if(key == '8') newMapSize();
    else if(key == '9') p1Sign = newSign();
    else if(key == '0') p2Sign = newSign();
  } while(key != 'X');
}

void _game()
{
  int cursor = 0;
  int* board = new int[mapSize*mapSize]();
  int* score = new int[3];
  unsigned long interval;
  int counter = 0;
  diodeState state;
  int player = player2;
  setTime(&interval, &state);
  int type = gameType();
  if(type == 1) dif = dificulty();
  long long time_stop = 0;
  bool joyPressed = false;
  long long timeCounter = getMS();
  do
  {
    newRound(&cursor, board, score);
    displayCursor(cursor, board);
    while(!hasWon(board, cursor, player) && !hasDrawn(board))
    {
      joyPressed = false;
      nextTurn(&player, &counter, &timeCounter, &state);
      while(!joyPressed && counter < 8)
      {
        if(player == player2 && type == 1)
        {
          cursor = botMove(board);
          displayCursor(cursor, board);
          break;
        }
        else
        {
          setDiode(&state, &counter, interval, &timeCounter);
          int tmp = cursor;
          getPosition(&cursor, &joyPressed);
          if(tmp != cursor){
            time_stop = getMS();
            displayCursor(cursor, board);
            timeCounter += getMS() - time_stop;
          }
          if(joyPressed)
          {
            if(checkMove(cursor, board)) board[cursor] = player;
            else
            {
              turnBuzzer(160, 10);
              joyPressed == false;
            }  
          }
        }
      }
      displayCursor(cursor, board);
      delayTime(500);
    }
    delayTime(1000);
    if(!hasDrawn(board))
    {
      ++score[player];
      setScore(score);
      result(player);
    }
    else result(0);
    
  }while(nextRound());
  
}

