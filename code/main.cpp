#define _CRT_SECURE_NO_WARNINGS
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
#include "loginsystem.h"
#include "keydown.h"

IMAGE img;
IMAGE test[2];
ExMessage msg;
int q = 0;
int w = 0;
int currentActiveButton = -1;
int ButtonResult = -1;
char Account[20];
//GPA与成绩关系
struct Node* list;
// 创建查找表
GradeToGpa lookupTable[] = {
    {90, 4.0},
    {87, 3.7},
    {84, 3.3},
    {80, 3.0},
    {77, 2.7},
    {74, 2.3},
    {70, 2.0},
    {67, 1.7},
    {64, 1.3},
    {60, 1.0},
    {0,0.0}
};
//主函数
int main()
{
    initgraph(1600, 800);
    setbkcolor(WHITE);
    cleardevice();
    loadimage(&img, "./picture/back.png", 1600, 800);
    putimage(0, 0, &img);
    list = createHead();
    readFromFile(list, "student.txt", 1);
    readGPAFromFile(list, "GPA.txt");
    Loginmenu();//1660
    system("pause");
    system("cls");
}