#pragma once
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

const int MAP_MAXSIZE = 1000;

struct MAP_t {
  bool RED;
  bool GREEN;
  bool BLUE;
};

void init(int HEIGHT, int WIDTH);
void render();
void draw_pixel(int HEIGHT, int WIDTH, bool RED, bool GREEN, bool BLUE);
void draw_pixel_tmp(int HEIGHT, int WIDTH, bool RED, bool GREEN, bool BLUE);
void reset_map();
void reset_pixel(int HEIGHT, int WIDTH);
void load_map();
void fill_map(bool RED, bool GREEN, bool BLUE);

MAP_t MAP[MAP_MAXSIZE][MAP_MAXSIZE];
MAP_t MAP_TMP[MAP_MAXSIZE][MAP_MAXSIZE];

_COORD coord;
HANDLE hConsole;
WORD saved_attributes;

int MAP_HEIGHT;
int MAP_WIDTH;


void init(int HEIGHT, int WIDTH) {

  for (int i = 0; i < MAP_MAXSIZE; i++) {
    for (int j = 0; j < MAP_MAXSIZE; j++) {
      MAP[i][j].RED=false;
      MAP[i][j].GREEN=false;
      MAP[i][j].BLUE=false;
      MAP_TMP[i][j].RED=false;
      MAP_TMP[i][j].GREEN=false;
      MAP_TMP[i][j].BLUE=false;
    }
  }

  system("@echo off");
  system("cls");

  MAP_HEIGHT = HEIGHT+1;
  MAP_WIDTH = WIDTH+1;

  coord.X = HEIGHT;
  coord.Y = WIDTH;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
  CONSOLE_CURSOR_INFO cinfo;

  GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
  saved_attributes = consoleInfo.wAttributes;

  _SMALL_RECT Rect;
  Rect.Top = 0;
  Rect.Left = 0;
  Rect.Bottom = HEIGHT;
  Rect.Right = WIDTH*2;

  cinfo.dwSize = 100;
  cinfo.bVisible = false;

  SetConsoleCursorInfo(hConsole, &cinfo);

  ShowCursor(false);

  SetConsoleScreenBufferSize(hConsole, coord);
  SetConsoleWindowInfo(hConsole, TRUE, &Rect);

  coord.X = 0;
  coord.Y = 0;
}

void render() {
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      if (MAP[i][j].RED==false && MAP[i][j].GREEN==false && MAP[i][j].BLUE==false) {SetConsoleTextAttribute(hConsole, saved_attributes);}
      if (MAP[i][j].RED==false && MAP[i][j].GREEN==false && MAP[i][j].BLUE==true) {SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);}
      if (MAP[i][j].RED==false && MAP[i][j].GREEN==true && MAP[i][j].BLUE==false) {SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);}
      if (MAP[i][j].RED==false && MAP[i][j].GREEN==true && MAP[i][j].BLUE==true) {SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_BLUE);}
      if (MAP[i][j].RED==true && MAP[i][j].GREEN==false && MAP[i][j].BLUE==false) {SetConsoleTextAttribute(hConsole, BACKGROUND_RED);}
      if (MAP[i][j].RED==true && MAP[i][j].GREEN==false && MAP[i][j].BLUE==true) {SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_BLUE);}
      if (MAP[i][j].RED==true && MAP[i][j].GREEN==true && MAP[i][j].BLUE==false) {SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN);}
      if (MAP[i][j].RED==true && MAP[i][j].GREEN==true && MAP[i][j].BLUE==true) {SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);}
      printf("  ");
      SetConsoleTextAttribute(hConsole, saved_attributes);
    }
    printf("\n");
  }
  SetConsoleCursorPosition(hConsole, coord);
}

void draw_pixel(int HEIGHT, int WIDTH, bool RED, bool GREEN, bool BLUE) {
  if (HEIGHT < 0 || HEIGHT > MAP_HEIGHT || WIDTH < 0 || WIDTH > MAP_WIDTH) {return;}
  MAP[HEIGHT][WIDTH].RED=RED;
  MAP[HEIGHT][WIDTH].GREEN=GREEN;
  MAP[HEIGHT][WIDTH].BLUE=BLUE;
}

void draw_pixel_tmp(int HEIGHT, int WIDTH, bool RED, bool GREEN, bool BLUE) {
  if (HEIGHT < 0 || HEIGHT > MAP_HEIGHT || WIDTH < 0 || WIDTH > MAP_WIDTH) {return;}
  MAP_TMP[HEIGHT][WIDTH].RED=RED;
  MAP_TMP[HEIGHT][WIDTH].GREEN=GREEN;
  MAP_TMP[HEIGHT][WIDTH].BLUE=BLUE;
}

void reset_map() {
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      MAP[i][j].RED=false;
      MAP[i][j].GREEN=false;
      MAP[i][j].BLUE=false;
    }
  }
}

void reset_pixel(int HEIGHT, int WIDTH) {
  if (HEIGHT < 0 || HEIGHT > MAP_HEIGHT || WIDTH < 0 || WIDTH > MAP_WIDTH) {return;}
  MAP[HEIGHT][WIDTH].RED=false;
  MAP[HEIGHT][WIDTH].GREEN=false;
  MAP[HEIGHT][WIDTH].BLUE=false;
}

void load_map() {
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      MAP[i][j].RED=MAP_TMP[i][j].RED;
      MAP[i][j].GREEN=MAP_TMP[i][j].GREEN;
      MAP[i][j].BLUE=MAP_TMP[i][j].BLUE;
    }
  }
}

void fill_map(bool RED, bool GREEN, bool BLUE) {
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      MAP[i][j].RED=RED;
      MAP[i][j].GREEN=GREEN;
      MAP[i][j].BLUE=BLUE;
    }
  }
}
