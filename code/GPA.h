#pragma once
#ifndef GPA_H
#define GPA_H
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
#include"filemodification.h"
double GPACaleach(double grade);
double sGPACaleach(struct student* s1);
void sGPAcalculate(struct Node* headNode);
double GPAextra();
#endif