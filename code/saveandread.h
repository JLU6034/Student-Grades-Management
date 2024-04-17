#pragma once
#ifndef SAVEANDREAD_H
#define SAVEANDREAD_H
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
#include "GPA.h"
#include"filemodification.h"
void saveToFile(struct Node* headNode, const char* fileName, int a, int n1);
void readFromFile(struct Node* headNode, const char* fileName, int mode);
void readCoursesFromFile(struct course* courses, const char* fileName);
void readGPAFromFile(struct Node* headNode, const char* fileName);
void saveGPAToFile(struct Node* headNode, const char* fileName);
void saveToFilea_account(struct Node* headNode, const char* fileName);
void readFromFile_account(struct Node* headNode, const char* fileName);
void shiftRightFromPosition(char arr[], int length, int length2, int position, int shift);
void shiftLeftFromPosition(char arr[], int length, int length2, int position);
#endif