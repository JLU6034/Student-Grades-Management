#define _CRT_SECURE_NO_WARNINGS
#include<graphics.h>
#include<easyx.h>
#include<stdio.h>
#include<assert.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include "structure.h" // �������� student ���͵�ͷ�ļ�
#include "listopretor.h"
#include "visualization.h"
#include "compare.h"
#include "saveandread.h"
#include "GPA.h"
#include"filemodification.h"
//�ȽϺ���
int compareBySGPA(struct student a, struct student b) {
    double sub = a.sGPA - b.sGPA;
    if (sub > 0)return 1;
    else if (sub < 0)return -1;
    else return 0;
}
int compareByStudentID(struct student a, struct student b) {
    char* p = a.num;
    char* q = b.num;
    while (*p && *q) {
        if (*p != *q) {
            return *p - *q;
        }
        p++;
        q++;
    }
}
int compareCourseNum(const void* a, const void* b) {
    struct coursegrades* courseA = (struct coursegrades*)a;
    struct coursegrades* courseB = (struct coursegrades*)b;
    return strcmp(courseA->each.cnum, courseB->each.cnum);
}
