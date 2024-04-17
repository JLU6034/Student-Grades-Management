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
//替换查找删除
void insertDataAtSpecificPosition(char* target, char* replacement) {
    FILE* inFile = fopen("student.txt", "r+");// 以读写方式打开文件
    FILE* outFile = fopen("temp.txt", "w+");// 以读写方式打开、创建临时文件
    if (!inFile || !outFile) {
        printf("无法打开文件\n");
        return;
    }
    // 读取文件内容并替换目标字符串
    char line[256] = {};
    while (fgets(line, sizeof(line), inFile))//读取每行内容
    {
        char* pos = strstr(line, target);//找到被替换字符串
        if (pos) {
            shiftRightFromPosition(line, sizeof(line), strlen(line), strlen(target), strlen(replacement) - strlen(target));//右移替换字符串后的内容
            strncpy(pos, replacement, strlen(replacement));// 在找到的位置替换目标字符串
        }
        fputs(line, outFile);//将替换后的内容写入临时文件
        /*fputc('\n', outFile);*/
    }
    fclose(inFile);
    fclose(outFile);
    // 删除原始文件并将临时文件重命名为原始文件
    remove("student.txt");
    rename("temp.txt", "student.txt");
}
void deleteDataAtSpecificPosition(char* linec, char* target) {
    FILE* inFile = fopen("student.txt", "r+");// 以读写方式打开文件
    FILE* outFile = fopen("temp.txt", "w+");// 以读写方式打开、创建临时文件
    if (!inFile || !outFile) {
        printf("无法打开文件\n");
        return;
    }
    // 读取文件内容并替换目标字符串
    char line[256] = {};
    while (fgets(line, sizeof(line), inFile))//读取每行内容
    {
        char* pos = strstr(line, target);//找到被替换字符串
        char* posc = strstr(line, linec);//找到被替换的学生姓名和学号
        if (pos && posc) {
            shiftLeftFromPosition(line, sizeof(line), strlen(target), strlen(line) - strlen(pos));//数组左移
        }
        fputs(line, outFile);//将替换后的内容写入临时文件
        /*fputc('\n', outFile);*/
    }
    fclose(inFile);
    fclose(outFile);
    // 删除原始文件并将临时文件重命名为原始文件
    remove("student.txt");
    rename("temp.txt", "student.txt");
}
void addCourseToFile(const char* cnum, const char* cname, const double ccre, const char* fileName)
{
    FILE* fp = fopen(fileName, "a");
    if (fp == NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    fprintf(fp, "%s %s %.2lf\n", cnum, cname, ccre);
    fclose(fp);
}
void modifyCourseInFile(const char* cnum, const char* newCname, const char* fileName)
{
    struct course courses[100];
    readCoursesFromFile(courses, fileName);

    for (int i = 0; i < 100; i++)
    {
        if (strcmp(courses[i].cnum, cnum) == 0)
        {
            strcpy(courses[i].name, newCname);
            break;
        }
    }

    FILE* fp = fopen(fileName, "w");
    if (fp == NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    for (int i = 0; i < 100; i++)
    {
        if (courses[i].cnum[0] != '\0')
        {
            fprintf(fp, "%s %s %lf\n", courses[i].cnum, courses[i].name, courses[i].credit);
        }
    }
    fclose(fp);
}
char* getCourseNameByCnum(const char* cnum, const char* fileName)
{
    struct course courses[100];
    readCoursesFromFile(courses, fileName);

    for (int i = 0; i < 100; i++)
    {
        if (strcmp(courses[i].cnum, cnum) == 0)
        {
            return courses[i].name;
        }
    }
    return NULL;
}
double getCourseCreditByCnum(const char* cnum, const char* fileName)
{
    struct course courses[100];
    readCoursesFromFile(courses, fileName);

    for (int i = 0; i < 100; i++)
    {
        if (strcmp(courses[i].cnum, cnum) == 0)
        {
            return courses[i].credit;
        }
    }
    return 0;
}
