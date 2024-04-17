#pragma once
#ifndef COMPARE_H
#define COMPARE_H
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
#include "saveandread.h"
#include "GPA.h"
#include"filemodification.h"
int compareBySGPA(struct student a, struct student b);
int compareByStudentID(struct student a, struct student b);
int compareCourseNum(const void* a, const void* b);
#endif