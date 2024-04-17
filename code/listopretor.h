#pragma once
#ifndef LISTOPRETOR_H
#define LISTOPRETOR_H
#include<graphics.h>
#include<easyx.h>
#include<stdio.h>
#include<assert.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include "structure.h"
#include "visualization.h"
#include "compare.h"
#include "saveandread.h"
#include "GPA.h"
#include"filemodification.h"
typedef int(*CompareFunc)(struct student, struct student);
struct Node* createHead();
struct Node* createNode(struct student data);
void insertData(struct Node* headNode, struct student data);
void deleteList(struct Node* headNode);
void deleteDataBYnum(struct Node* headNode, const char* num);
struct Node* split(struct Node* head, int size);
int getLength(struct Node* head);
struct Node* mergeSort(struct Node* head, CompareFunc compare);
struct Node* merge(struct Node* a, struct Node* b, CompareFunc compare);
//≤È’“ ˝æ›
struct Node* searchDataBYName(struct Node* headNode, const char* name);
struct Node* searchDataBYnum(struct Node* headNode, const char* num);
void print(struct Node* headNode);
void printList(struct Node* headNode);
#endif