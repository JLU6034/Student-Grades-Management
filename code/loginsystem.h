#pragma once
#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H
#include<graphics.h>
#include<easyx.h>
#include<stdio.h>
#include<assert.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include "structure.h"
#include "listopretor.h"
#include "visualization.h"
#include "compare.h"
#include "saveandread.h"
#include "GPA.h"
#include"filemodification.h"
int RegisterTea();
int LoginTea();
struct Node* searchDataBYnum_Account(struct Node* headNode, const char* num);
int Registerstu(struct Node* headNode, char* account);
int LoginStu();
void change();
void Loginmenu();
#endif