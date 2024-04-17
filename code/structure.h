#pragma once
// structures.h
#ifndef STRUCTURES_H
#define STRUCTURES_H
#include<graphics.h>
#include<easyx.h>
typedef struct Button
{
    int x;
    int y;
    int w;
    int h;
    COLORREF color;
    char* text;
}BUTTON, * LPBUTTON;
struct GradeToGpa {
    double grade;
    double gpa;
};
struct course {
    char cnum[20];
    char name[20];
    double credit;
    char c[5];
};
struct coursegrades {
    struct course each;
    double GPA;
    double grades;
    char g[6];
};
//学生信息结构体
struct student
{
    char name[20];
    char num[20];
    struct coursegrades scourse[6];
    double sGPA;
    char password[20] = { "123456" };
    double eGPA;
};
//链表结构体
struct Node
{
    struct student data;
    struct Node* next;
};

// 其他结构体...

#endif // STRUCTURES_H
