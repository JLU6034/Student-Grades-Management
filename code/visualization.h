#pragma once
#ifndef VISUALIZATION_H
#define VISUALIZATION_H
#include<graphics.h>
#include<easyx.h>
#include<stdio.h>
#include<assert.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include "structure.h"
#include "listopretor.h"
#include "compare.h"
#include "saveandread.h"
#include "GPA.h"
#include"filemodification.h"
LPBUTTON createButton(int x, int y, int w, int h, const char* str);
void drawButton(LPBUTTON button);
void DrawSTMenu();
void DrawMenu();
void DrawReturn();
void DrawPage();
#endif