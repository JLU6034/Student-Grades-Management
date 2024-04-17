#pragma once
#ifndef FILEMODIFICATION_H
#define FILEMODIFICATION_H
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
void insertDataAtSpecificPosition(char* target, char* replacement);
void deleteDataAtSpecificPosition(char* linec, char* target);
void addCourseToFile(const char* cnum, const char* cname, const double ccre, const char* fileName);
void modifyCourseInFile(const char* cnum, const char* newCname, const char* fileName);
char* getCourseNameByCnum(const char* cnum, const char* fileName);
double getCourseCreditByCnum(const char* cnum, const char* fileName);
#endif