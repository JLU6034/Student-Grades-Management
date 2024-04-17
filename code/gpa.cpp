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
extern GradeToGpa lookupTable[11];
extern ExMessage msg;
//绩点计算
double GPACaleach(double grade)
{
    for (int i = 0; i < sizeof(lookupTable) / sizeof(GradeToGpa); i++) {
        if (grade >= lookupTable[i].grade) {
            return lookupTable[i].gpa;
        }
    }
    return 0.0;  // 如果分数低于10，返回0.0
}
double sGPACaleach(struct student* s1) {
    struct coursegrades* pri = s1->scourse;
    double sum1 = 0;
    double sum2 = 0;
    while (pri->each.cnum[0] != '\0')
    {
        sum1 += pri->GPA * pri->each.credit;
        sum2 += pri->each.credit;
        pri++;
    }if (sum1 != 0 && sum2 != 0) {
        return sum1 / sum2;
    }
    else {
        return 0;
    }
}
double GPAextra() {
    IMAGE img;
    loadimage(&img, "./picture/back.png", 1600, 800);
    putimage(0, 0, &img);
    LPBUTTON Button4111 = createButton(650, 150, 300, 100, "科研成果");
    LPBUTTON Button4112 = createButton(650, 550, 300, 100, "竞赛成绩");
    LPBUTTON Button4121 = createButton(650, 150, 300, 100, "创业项目");
    LPBUTTON Button4122 = createButton(650, 350, 300, 100, "学术论文");
    LPBUTTON Button4123 = createButton(650, 550, 300, 100, "顶级期刊论文");
    LPBUTTON Button4131 = createButton(650, 150, 300, 100, "负责人");
    LPBUTTON Button4132 = createButton(650, 550, 300, 100, "第二名");//1620
    LPBUTTON Button4141 = createButton(200, 50, 1200, 100, "CCF-A论文|CCF-B");
    LPBUTTON Button4142 = createButton(200, 250, 1200, 100, "CCF-B|CCF-C最佳|中科院一区");
    LPBUTTON Button4143 = createButton(200, 450, 1200, 100, "CCF-C论文|CCF-B会议长文|学报论文");
    LPBUTTON Button4144 = createButton(200, 650, 1200, 100, "SCI论文|CCF-C会议长文|EL检索期刊");
    LPBUTTON Button4151 = createButton(650, 150, 300, 100, "A类竞赛");
    LPBUTTON Button4152 = createButton(650, 350, 300, 100, "B类竞赛");
    LPBUTTON Button4153 = createButton(650, 550, 300, 100, "C类竞赛");
    LPBUTTON Button4161 = createButton(650, 150, 300, 100, "一等奖");
    LPBUTTON Button4162 = createButton(650, 350, 300, 100, "二等奖");
    LPBUTTON Button4163 = createButton(650, 550, 300, 100, "三等奖");
    drawButton(Button4111);
    drawButton(Button4112);
    int choice;
    double result = 1;
    do
    {
        peekmessage(&msg, EM_MOUSE);
        if (msg.x > 650 && msg.x < 950 && msg.y>150 && msg.y < 250 && msg.message == WM_LBUTTONDOWN)
        {
            choice = 1;
            break;
        }
        else if (msg.x > 650 && msg.x < 950 && msg.y>550 && msg.y < 650 && msg.message == WM_LBUTTONDOWN)
        {
            choice = 2;
            break;
        }
    } while (1);
    cleardevice();
    Sleep(200);
    /*printf("请输入该学生的额外GPA来源\n");
    printf("1科研成果 \n2竞赛成绩\n");*/
    /*scanf("%d", &choice);*/
    if (choice == 1) {
        /* printf("请输入科研成果形式\n1 创业项目\n2 学术论文\n3顶级期刊论文\n");*/
        loadimage(&img, "./picture/back.png", 1600, 800);
        putimage(0, 0, &img);
        drawButton(Button4121);
        drawButton(Button4122);
        drawButton(Button4123);
        do
        {
            peekmessage(&msg, EM_MOUSE);
            if (msg.x > 650 && msg.x < 950 && msg.y>150 && msg.y < 250 && msg.message == WM_LBUTTONDOWN)
            {
                choice = 1;
                break;
            }
            else if (msg.x > 650 && msg.x < 950 && msg.y>350 && msg.y < 450 && msg.message == WM_LBUTTONDOWN)
            {
                choice = 2;
                break;
            }
            else if (msg.x > 650 && msg.x < 950 && msg.y>550 && msg.y < 650 && msg.message == WM_LBUTTONDOWN)
            {
                choice = 3;
                break;
            }
        } while (1);
        Sleep(200);
        /*scanf("%d", &choice);*/
        switch (choice) {
        case 1:
            /*printf("该生为\n1.负责人 2 .第二名\n");
            scanf("%d", &choice);*/
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            drawButton(Button4131);
            drawButton(Button4132);
            do
            {
                peekmessage(&msg, EM_MOUSE);
                if (msg.x > 650 && msg.x < 950 && msg.y>150 && msg.y < 250 && msg.message == WM_LBUTTONDOWN)
                {
                    choice = 1;
                    break;
                }
                else if (msg.x > 650 && msg.x < 950 && msg.y>550 && msg.y < 650 && msg.message == WM_LBUTTONDOWN)
                {
                    choice = 2;
                    break;
                }
            } while (1);
            Sleep(200);
            if (choice == 1)result = 0.1;
            else	if (choice == 2)result = 0.05;
            /*else printf("input error!\n");*/
            break;
        case 2:
            /*printf("该论文属于\n1.CCF-A论文|CCF-B 最佳\n2.CCF-B|CCF-C最佳|中科院一区\n3.CCF-C论文|CCF-B会议长文|学报论文|中科院二区\n4.SCI论文|CCF-C会议长文|EL检索期刊\n");
            scanf("%d", &choice);*/
            cleardevice();
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            drawButton(Button4141);
            drawButton(Button4142);
            drawButton(Button4143);
            drawButton(Button4144);
            
            do
            {
                peekmessage(&msg, EM_MOUSE);
                if (msg.x > 200 && msg.x < 1400 && msg.y>50 && msg.y < 150 && msg.message == WM_LBUTTONDOWN)
                {
                    choice = 1;
                    break;
                }
                else if (msg.x > 200 && msg.x < 1400 && msg.y>250 && msg.y < 350 && msg.message == WM_LBUTTONDOWN)
                {
                    choice = 2;
                    break;
                }
                else if (msg.x > 200 && msg.x < 1400 && msg.y>450 && msg.y < 550 && msg.message == WM_LBUTTONDOWN)
                {
                    choice = 3;
                    break;
                }
                else if (msg.x > 200 && msg.x < 1400 && msg.y>650 && msg.y < 750 && msg.message == WM_LBUTTONDOWN)
                {
                    choice = 4;
                    break;
                }
            } while (1);
            if (choice == 1)result = 0.2;
            else if (choice == 2)result = 0.1;
            else if (choice == 3)result = 0.05;
            else if (choice == 4)result = 0.02;
            /*else(printf("input error!\n"));*/
            break;
        case 3:
            result = 0.4;
            break;
        }
    }
    else if (choice == 2) {
        int grade = 1;
        /* printf("请输入竞赛类别\n1.A 2.B 3.C\n");
         scanf("%d", &choice);*/
         /*printf("请输入奖项等级\n1.一等奖2.二等奖3.三等奖\n");
         scanf("%d", &grade);*/
        loadimage(&img, "./picture/back.png", 1600, 800);
        putimage(0, 0, &img);
        drawButton(Button4151);
        drawButton(Button4152);
        drawButton(Button4153);
       
        do
        {
            peekmessage(&msg, EM_MOUSE);
            if (msg.x > 650 && msg.x < 950 && msg.y>150 && msg.y < 250 && msg.message == WM_LBUTTONDOWN)
            {
                choice = 1;
                break;
            }
            else if (msg.x > 650 && msg.x < 950 && msg.y>350 && msg.y < 450 && msg.message == WM_LBUTTONDOWN)
            {
                choice = 2;
                break;
            }
            else if (msg.x > 650 && msg.x < 950 && msg.y>550 && msg.y < 650 && msg.message == WM_LBUTTONDOWN)
            {
                choice = 3;
                break;
            }
        } while (1); Sleep(200);
        loadimage(&img, "./picture/back.png", 1600, 800);
        putimage(0, 0, &img);
        drawButton(Button4161);
        drawButton(Button4162);
        drawButton(Button4163);
      
        do
        {
            peekmessage(&msg, EM_MOUSE);
            if (msg.x > 650 && msg.x < 950 && msg.y>150 && msg.y < 250 && msg.message == WM_LBUTTONDOWN)
            {
                grade = 1;
                break;
            }
            else if (msg.x > 650 && msg.x < 950 && msg.y>350 && msg.y < 450 && msg.message == WM_LBUTTONDOWN)
            {
                grade = 2;
                break;
            }
            else if (msg.x > 650 && msg.x < 950 && msg.y>550 && msg.y < 650 && msg.message == WM_LBUTTONDOWN)
            {
                grade = 3;
                break;
            }
        } while (1);
        if (choice == 1 && grade == 1)result = 0.4;
        else if ((choice == 1 && grade == 2) || (choice == 2 && grade == 1))result = 0.2;
        else if ((choice == 1 && grade == 3) || (choice == 2 && grade == 2) || (choice == 3 && grade == 1))result = 0.1;
        else if ((choice == 2 && grade == 3) || (choice == 3 && grade == 2))result = 0.05;
        else if (choice = 3 && grade == 3)result = 0.02;
        cleardevice();
    }
    /* else {
         printf("input error!\n");
     }*/
    return result;
}
void sGPAcalculate(struct Node* headNode) {
    struct Node* pmove = headNode->next;
    while (pmove != NULL)
    {
        pmove->data.sGPA = sGPACaleach(&pmove->data);
        pmove = pmove->next;
    }
}