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
//写文件
void saveToFile(struct Node* headNode, const char* fileName, int a, int n1)//写文件
{
    FILE* fp = NULL;
    switch (a)
    {
    case 1:
    case 3:
        fp = fopen(fileName, "w+");
        break;
    default:
        break;
    }
    ;
    struct Node* pmove = headNode->next;
    struct coursegrades* pri = pmove->data.scourse;
    if ((a != 5 && a != 2 && a != 4) && fp == NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    if (a == 2) //存储课程成绩
    {
        /*char* str=(char*)malloc(sizeof(char)*256);
        str = {};*/
        for (int i = 0; i < n1; i++) {
            char str[256] = {};
            char str1[256] = {};
            snprintf(str, sizeof(str), "|%s\t|%s\t||\t%s\t|%s\t|%.2lf\t|%.2lf\t|%.2lf\t|", headNode->data.name, headNode->data.num, headNode->data.scourse[i].each.cnum, headNode->data.scourse[i].each.name, headNode->data.scourse[i].each.credit, headNode->data.scourse[i].grades, headNode->data.scourse[i].GPA);
            snprintf(str1, sizeof(str1), "|%s\t|%s\t|", headNode->data.name, headNode->data.num);
            insertDataAtSpecificPosition(str1, str);
        }
        /*free(str);*/
    }
    else if (a == 3 || a == 1) //彻底存储整个链表
    {
        while (pmove != NULL)
        {
            if (fprintf(fp, "|%s\t|%s\t|", pmove->data.name, pmove->data.num) != EOF);
            pri = pmove->data.scourse;
            while (pri->each.cnum[0] != '\0')//判断是否为空
            {
                fprintf(fp, "|\t%s\t|%s\t|%.2lf\t|%.2lf\t|%.2lf\t|", pri->each.cnum, pri->each.name, pri->each.credit, pri->grades, pri->GPA);
                pri++;
            }
            if (pri->each.cnum[0] == '\0') {
                fprintf(fp, "\n");
            }
            /*char str[256];
            snprintf(str, sizeof(str), "|\t%s	|%s	|%s	|%.2lf	|%.2lf	", pmove->data.name, pmove->data.scourse->each.cnum, pmove->data.scourse->each.name, pmove->data.scourse->grades, pmove->data.scourse->GPA);
            deleteDataAtSpecificPosition(pmove->data.num, str);*/
            /*free(str);*/
            pmove = pmove->next;
        }
        fclose(fp);
    }
    else if (a == 4) //修改成绩
    {
        for (int i = 0; i < n1; i++) {
            char str[256] = {};
            char str1[256] = {};
            char str2[30] = {};
            snprintf(str, sizeof(str), "|\t%s\t|%s\t|%.2lf\t|%.2lf\t|%.2lf\t|", headNode->data.scourse[i].each.cnum, headNode->data.scourse[i].each.name, headNode->data.scourse[i].each.credit, headNode->data.scourse[i].grades, headNode->data.scourse[i].GPA);
            snprintf(str1, sizeof(str1), "|\t%s\t|%s\t|", headNode->data.scourse[i].each.cnum, headNode->data.scourse[i].each.name);//要修改的课程号课程名
            snprintf(str2, sizeof(str2), "|%s\t|%s\t|", headNode->data.name, headNode->data.num);//学生姓名学号
            deleteDataAtSpecificPosition(str1, str);
            insertDataAtSpecificPosition(str1, str);
        }
    }
    else if (a == 5) //删除课程
    {
        for (int i = 0; i < n1; i++) {
            char str[256] = {};
            char str1[256] = {};
            snprintf(str, sizeof(str), "|%s\t|%s\t|", headNode->data.name, headNode->data.num);
            snprintf(str1, sizeof(str1), "|\t%s\t|%s\t|%.2lf\t|%.2lf\t|%.2lf\t|", headNode->data.scourse[i].each.cnum, headNode->data.scourse[i].each.name, headNode->data.scourse[i].each.credit, headNode->data.scourse[i].grades, headNode->data.scourse[i].GPA);
            deleteDataAtSpecificPosition(str, str1);
        }
    }
}
void readFromFile(struct Node* headNode, const char* fileName, int mode)//读文件
{
    FILE* fp = fopen(fileName, "r+");
    if (fp == NULL)
    {
        printf("无法打开文件！\n");
        return;
    }
    struct student temp {};
    switch (mode) {
    case 1:
        /*size_t len = 0;*/
        while (fscanf(fp, "|%s\t|%s\t|", temp.name, temp.num) != EOF)
        {
            /*len=sizeof(temp.num)+sizeof(temp.name)+5;
            fseek(fp, len, SEEK_CUR);*/
            struct coursegrades* pri = temp.scourse;
            while (fscanf(fp, "|\t%s\t|%s\t|%lf\t|%lf\t|%lf\t|", pri->each.cnum, pri->each.name, &pri->each.credit, &pri->grades, &pri->GPA) == 5)
            {
                pri++;
            }
            fscanf(fp, "\n");
            insertData(headNode, temp);
        }
        break;
    case 2:
        // 另一种读取方式
        break;
        // 可以添加更多的case来处理不同的读取方式
    default:
        printf("未知的读取模式\n");
        break;
    }
    fclose(fp);
}
void readCoursesFromFile(struct course* courses, const char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        fp = fopen(fileName, "w+");
        if (fp != NULL) {
            fclose(fp);
        }
        return;
    }
    while (fscanf(fp, " %s %s %lf", courses->cnum, courses->name, &courses->credit) == 3)
    {
        courses++;
    }
    fclose(fp);
}
void saveGPAToFile(struct Node* headNode, const char* fileName) {
    FILE* fp = fopen(fileName, "w+");
    if (fp == NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    struct Node* pmove = headNode->next;
    while (pmove != NULL)
    {
        fprintf(fp, "|%s\t|%s\t|%.2lf\t|%.2lf\t|\n", pmove->data.name, pmove->data.num, pmove->data.sGPA, pmove->data.eGPA);
        pmove = pmove->next;
    }
    fclose(fp);
}
void readGPAFromFile(struct Node* headNode, const char* fileName) {
    FILE* fp = fopen(fileName, "r+");
    struct Node* result = NULL;
    if (fp == NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    struct student temp {};
    while (fscanf(fp, "|%s\t|%s\t|%lf\t|%lf\t|\n", temp.name, temp.num, &temp.sGPA, &temp.eGPA) == 4)
    {
        result = searchDataBYnum(headNode, temp.num);
        result->data.sGPA = temp.sGPA;
        result->data.eGPA = temp.eGPA;
    }
    fclose(fp);
}
void saveToFilea_account(struct Node* headNode, const char* fileName)//写文件
{
    struct Node* pmove = headNode->next;
    FILE* fp = fopen(fileName, "w");
    if (fp == NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    while (pmove != NULL)
    {
        fprintf(fp, "%s\t%s\n", pmove->data.num, pmove->data.password);
        pmove = pmove->next;
    }
    fclose(fp);
}
void readFromFile_account(struct Node* headNode, const char* fileName)//读文件
{
    FILE* fp = fopen(fileName, "r+");
    struct Node* result = NULL;
    if (fp == NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    struct student temp {};
    while (fscanf(fp, "%s\t%s\n", temp.num, temp.password) == 2)
    {
        result = searchDataBYnum(headNode, temp.num);
        strcpy(result->data.password, temp.password);
    }
    fclose(fp);
}
//从指定位置向右移动数组元素
void shiftRightFromPosition(char arr[], int length, int length2, int position, int shift) {
    // 检查数组是否为空，位置是否有效
    if (arr == NULL || length <= 0 || position < 0 || position >= length) {
        return;
    }

    // 检查是否有足够的空间进行移动
    if (position + shift >= length) {
        return;
    }
    char* s1, * s2;//s1为arr的末尾，s2为b的首地址
    position += 1;//从position位置插入
    s1 = arr + length2 + shift;//s1指向arr的末尾
    s2 = s1;
    while (s1 >= arr + position - 1 + shift)
    {
        *s1 = *(s1 - shift);
        *(s1 - shift) = '\0';
        s1--;
    };
    s1 = arr;
    return;
}
void shiftLeftFromPosition(char arr[], int length, int length2, int position) {
    // 检查数组是否为空，位置是否有效
    if (arr == NULL || length <= 0 || position < 0 || position >= length) {
        return;
    }
    char* s1, * s2;
    length = strlen(arr);
    s1 = arr + position;
    while (s1 <= arr + length - length2 - 1)
    {
        *s1 = *(s1 + length2);
        s1++;
    }
    while (s1 <= arr + length - 1)
    {
        *s1 = '\0';
        s1++;
    }
    s1 = arr;
    return;
}


