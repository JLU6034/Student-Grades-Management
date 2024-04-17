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
//�滻����ɾ��
void insertDataAtSpecificPosition(char* target, char* replacement) {
    FILE* inFile = fopen("student.txt", "r+");// �Զ�д��ʽ���ļ�
    FILE* outFile = fopen("temp.txt", "w+");// �Զ�д��ʽ�򿪡�������ʱ�ļ�
    if (!inFile || !outFile) {
        printf("�޷����ļ�\n");
        return;
    }
    // ��ȡ�ļ����ݲ��滻Ŀ���ַ���
    char line[256] = {};
    while (fgets(line, sizeof(line), inFile))//��ȡÿ������
    {
        char* pos = strstr(line, target);//�ҵ����滻�ַ���
        if (pos) {
            shiftRightFromPosition(line, sizeof(line), strlen(line), strlen(target), strlen(replacement) - strlen(target));//�����滻�ַ����������
            strncpy(pos, replacement, strlen(replacement));// ���ҵ���λ���滻Ŀ���ַ���
        }
        fputs(line, outFile);//���滻�������д����ʱ�ļ�
        /*fputc('\n', outFile);*/
    }
    fclose(inFile);
    fclose(outFile);
    // ɾ��ԭʼ�ļ�������ʱ�ļ�������Ϊԭʼ�ļ�
    remove("student.txt");
    rename("temp.txt", "student.txt");
}
void deleteDataAtSpecificPosition(char* linec, char* target) {
    FILE* inFile = fopen("student.txt", "r+");// �Զ�д��ʽ���ļ�
    FILE* outFile = fopen("temp.txt", "w+");// �Զ�д��ʽ�򿪡�������ʱ�ļ�
    if (!inFile || !outFile) {
        printf("�޷����ļ�\n");
        return;
    }
    // ��ȡ�ļ����ݲ��滻Ŀ���ַ���
    char line[256] = {};
    while (fgets(line, sizeof(line), inFile))//��ȡÿ������
    {
        char* pos = strstr(line, target);//�ҵ����滻�ַ���
        char* posc = strstr(line, linec);//�ҵ����滻��ѧ��������ѧ��
        if (pos && posc) {
            shiftLeftFromPosition(line, sizeof(line), strlen(target), strlen(line) - strlen(pos));//��������
        }
        fputs(line, outFile);//���滻�������д����ʱ�ļ�
        /*fputc('\n', outFile);*/
    }
    fclose(inFile);
    fclose(outFile);
    // ɾ��ԭʼ�ļ�������ʱ�ļ�������Ϊԭʼ�ļ�
    remove("student.txt");
    rename("temp.txt", "student.txt");
}
void addCourseToFile(const char* cnum, const char* cname, const double ccre, const char* fileName)
{
    FILE* fp = fopen(fileName, "a");
    if (fp == NULL)
    {
        printf("���ļ�ʧ�ܣ�\n");
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
        printf("���ļ�ʧ�ܣ�\n");
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
