#ifndef TTT_HPP

#define TTT_HPP
#include <time.h>
#include "api.hpp"
#include <string.h>
#define VERSION "Version: 0.75"
#define LOW 0
#define HIGH 1

enum diodeState{
  ST_COUNT,
  ST_WAIT
};

void _printMenu(char** menuItems, int menuSize);

void _settings(char** settings, int settingsSize);

void _initialize();

void _game();

#endif

