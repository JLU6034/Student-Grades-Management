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
extern char Account[20];
extern IMAGE test[2];
extern ExMessage msg;
extern IMAGE img;
extern int ButtonResult;
extern struct Node* list;
extern int q;
extern int w;
typedef int(*CompareFunc)(struct student, struct student);
struct Node* createHead()
{
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	assert(headNode);
	headNode->next = NULL;
	return headNode;
}

struct Node* createNode(student data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	assert(newNode);
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void insertData(struct Node* headNode, struct student data)
{
    struct Node* newNode = createNode(data);
    newNode->next = headNode->next;
    headNode->next = newNode;
}
void deleteList(struct Node* headNode) {
    struct Node* currentNode = headNode->next;
    struct Node* nextNode;

    while (currentNode != NULL) {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }

    headNode->next = NULL;
}
//删除数据
void deleteDataBYnum(struct Node* headNode, const char* num)
{
    struct Node* preNode = headNode;
    struct Node* curNode = headNode->next;
    while (curNode != NULL && strcmp(curNode->data.num, num))
    {
        preNode = curNode;
        curNode = preNode->next;
    }
    if (curNode == NULL)
    {
        printf("删除失败！没有找到指定数据！\n");
    }
    else
    {
        preNode->next = curNode->next;
        free(curNode);
    }
}
// 获取链表长度
int getLength(struct Node* head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}
// 分割链表
struct Node* split(struct Node* head, int size) {
    struct Node* cur = head;//当前节点
    for (int i = 1; cur != NULL && i < size; i++) {
        cur = cur->next;
    }
    // 如果当前节点为空，返回NULL
    if (cur == NULL) {
        return NULL;
    }
    // 如果当前节点不为空，保存当前节点的下一个节点
    struct Node* next = cur->next;
    cur->next = NULL;
    return next;
}
// 归并排序
struct Node* mergeSort(struct Node* head, CompareFunc compare) {
    int length = getLength(head);
    struct Node dummy;
    struct Node* start, * tail;
    // 每次合并的链表长度
    for (int size = 1; size < length; size <<= 1) {
        dummy.next = NULL;  // 将 dummy.next 设置为 NULL
        start = head;
        tail = &dummy;
        // 每次合并两个长度为size的链表
        while (start != NULL) {
            struct Node* mid = split(start, size);
            struct Node* end = split(mid, size);
            struct Node* merged = merge(start, mid, compare);
            tail->next = merged;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            start = end;
        }
        head = dummy.next;  // 更新 head 为新的链表头
    }
    return dummy.next;
}
//合并链表
struct Node* merge(struct Node* a, struct Node* b, CompareFunc compare) {
    struct Node dummy;
    struct Node* tail = &dummy;
    // 如果a和b都不为空，比较a和b的值，将较小的值放到tail后面
    while (a != NULL && b != NULL) {
        if (compare(a->data, b->data) <= 0) {
            tail->next = a;
            a = a->next;
        }
        else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    // 如果a不为空，将a的剩余部分放到tail后面
    if (a != NULL) {
        tail->next = a;
    }
    else {
        tail->next = b;
    }
    return dummy.next;
}
struct Node* searchDataBYName(struct Node* headNode, const char* name)
{
    struct Node* pmove = headNode->next;
    while (pmove != NULL && strcmp(pmove->data.name, name))
    {
        pmove = pmove->next;
    }
    return pmove;
};
struct Node* searchDataBYnum(struct Node* headNode, const char* num)
{
    struct Node* pmove = headNode->next;
    while (pmove != NULL && strcmp(pmove->data.num, num))
    {
        pmove = pmove->next;
    }
    return pmove;
}
void print(struct Node* headNode)
{
    cleardevice();
    loadimage(&img, "./picture/back.png", 1600, 800);
    putimage(0, 0, &img);
    int counts = 0;
    struct Node* pmove = headNode->next;
    struct Node* pmove1 = headNode->next;
    struct coursegrades* pri = pmove->data.scourse;
    struct Node* temp = headNode->next;
    static int currentPage = 0; // 当前页码
    int itemsPerPage = 23; // 每页显示的项数
    int totalItems = 0;
    while (temp)
    {
        temp = temp->next;
        totalItems++;
    }
    setcolor(BLACK);
    settextcolor(WHITE);
    LPBUTTON Button115 = createButton(0, 750, 50, 50, "返回");
    drawButton(Button115);
    DrawPage();
    settextstyle(15, 0, "宋体");
    int startX = 200, startY = 100;
    int tableWidth = 1200, rowHeight = 600;
    int cols = 9; // 列数
    int colWidth = tableWidth / cols; // 每列的宽度
    for (int i = 0; i <= cols; ++i) {
        line(startX + i * colWidth, startY, startX + i * colWidth, startY + rowHeight);
    }
    line(startX, startY, startX + tableWidth, startY);
    line(startX, startY + rowHeight, startX + tableWidth, startY + rowHeight);

    settextcolor(BLACK);
    outtextxy(startX + 5, startY + 5, "学号");
    outtextxy(startX + colWidth + 5, startY + 5, "姓名");
    outtextxy(startX + 2 * colWidth + 5, startY + 5, "GPA");
    /*outtextxy(startX + 3 * colWidth + 5, startY + 5, pmove->data.scourse[0].each.name);
    outtextxy(startX + 4 * colWidth + 5, startY + 5, pmove->data.scourse[1].each.name);
    outtextxy(startX + 5 * colWidth + 5, startY + 5, pmove->data.scourse[2].each.name);
    outtextxy(startX + 6 * colWidth + 5, startY + 5, pmove->data.scourse[3].each.name);
    outtextxy(startX + 7 * colWidth + 5, startY + 5, pmove->data.scourse[4].each.name);
    outtextxy(startX + 8 * colWidth + 5, startY + 5, pmove->data.scourse[5].each.name);*/
    for (int i = 1; i < 24; i++)
    {
        line(startX, startY + 25 * i, startX + tableWidth, startY + 25 * i);
    }

    for (int skipItems = 0; skipItems < currentPage * itemsPerPage; ++skipItems) {
        if (pmove1) { pmove1 = pmove1->next; }
    }
    int displayedItems = 0;
    settextcolor(WHITE);
    while (pri->each.cnum[0] != '\0') {
        /*printf("\t%s", pri->each.name);*/
        pri++;
        counts++;
    }
    if (pri->each.cnum[0] == '\0') {
        /*printf("\n");*/
    }
    while (pmove != NULL)
    {
        /*printf("%s\t%s\t%.2lf", pmove->data.name, pmove->data.num, pmove->data.sGPA + pmove->data.eGPA);*/
        qsort(pmove->data.scourse, counts, sizeof(struct coursegrades), compareCourseNum);  // 对每个学生的课程成绩进行排序
        pri = pmove->data.scourse;
        while (pri->each.cnum[0] != '\0') {
            /* printf("\t%.2lf\t%.2lf", pri->grades, pri->GPA);*/
            pri++;
        }
        if (pri->each.cnum[0] == '\0') {
            /*printf("\n");*/
        }
        pmove = pmove->next;
    }
    /* pmove = headNode->next;*/
    settextcolor(BLACK);
    outtextxy(startX + 3 * colWidth + 5, startY + 5, pmove1->data.scourse[0].each.name);
    outtextxy(startX + 4 * colWidth + 5, startY + 5, pmove1->data.scourse[1].each.name);
    outtextxy(startX + 5 * colWidth + 5, startY + 5, pmove1->data.scourse[2].each.name);
    outtextxy(startX + 6 * colWidth + 5, startY + 5, pmove1->data.scourse[3].each.name);
    outtextxy(startX + 7 * colWidth + 5, startY + 5, pmove1->data.scourse[4].each.name);
    outtextxy(startX + 8 * colWidth + 5, startY + 5, pmove1->data.scourse[5].each.name);
    while (pmove1 != NULL && displayedItems < itemsPerPage)
    {
        w = q % 23;
        settextcolor(BLACK);
        outtextxy(startX + 5, startY + 30 + 25 * w, pmove1->data.name);
        outtextxy(startX + colWidth + 5, startY + 30 + 25 * w, pmove1->data.num);
        char strValue[20]; // 保留足够的空间来容纳转换后的字符串
        sprintf(strValue, "%.2lf", pmove1->data.eGPA + pmove1->data.sGPA);
        outtextxy(startX + 2 * colWidth + 5, startY + 30 + 25 * w, strValue);
        char strValue0[20]; char strValue1[20]; char strValue2[20]; char strValue3[20]; char strValue4[20]; char strValue5[20];
        sprintf(strValue0, "%.2lf", pmove1->data.scourse[0].grades);
        sprintf(strValue1, "%.2lf", pmove1->data.scourse[1].grades);
        sprintf(strValue2, "%.2lf", pmove1->data.scourse[2].grades);
        sprintf(strValue3, "%.2lf", pmove1->data.scourse[3].grades);
        sprintf(strValue4, "%.2lf", pmove1->data.scourse[4].grades);
        sprintf(strValue5, "%.2lf", pmove1->data.scourse[5].grades);
        outtextxy(startX + 3 * colWidth + 5, startY + 30 + 25 * w, strValue0);
        outtextxy(startX + 4 * colWidth + 5, startY + 30 + 25 * w, strValue1);
        outtextxy(startX + 5 * colWidth + 5, startY + 30 + 25 * w, strValue2);
        outtextxy(startX + 6 * colWidth + 5, startY + 30 + 25 * w, strValue3);
        outtextxy(startX + 7 * colWidth + 5, startY + 30 + 25 * w, strValue4);
        outtextxy(startX + 8 * colWidth + 5, startY + 30 + 25 * w, strValue5);
        pmove1 = pmove1->next;
        displayedItems++;
        /*outtextxy(10, 400, pmove->data.num);
        //outtextxy(20, 400, pmove->data.math);
        //outtextxy(30, 400, pmove->data.english);
        //outtextxy(40, 400, pmove->data.py);
        outtextxy(50, 400, pmove->data.sum);
        outtextxy(60, 400, pmove->data.average);*/
        q++;
    }
    q = 0;
    bool needUpdate = false;
    do {
        peekmessage(&msg, EM_MOUSE); // 不断检查鼠标消息
        if (msg.x > 850 && msg.x < 900 && msg.y>750 && msg.y < 775 && msg.message == WM_LBUTTONDOWN) {
            if (currentPage * itemsPerPage + displayedItems < totalItems) {
                currentPage++;
                needUpdate = true;

            }
        }
        else if (msg.x > 600 && msg.x < 650 && msg.y>750 && msg.y < 775 && msg.message == WM_LBUTTONDOWN) {
            if (currentPage > 0) {
                currentPage--;
                needUpdate = true;
            }
        }
        else if (msg.x > 0 && msg.x < 50 && msg.y>750 && msg.y < 800 && msg.message == WM_LBUTTONDOWN)
        {
            break;
        }
        if (needUpdate) {
            cleardevice(); // 清除屏幕
            print(headNode); // 重新调用printList来绘制新的页面
        }
    } while (1);
    currentPage = 0;
    /* printf("姓名\t编号\tGPA");*/
     //while (pri->each.cnum[0] != '\0') {
     //    /*printf("\t%s", pri->each.name);*/
     //    pri++;
     //    counts++;
     //}
     //if (pri->each.cnum[0] == '\0') {
     //   /* printf("\n");*/
     //}
     //while (pmove != NULL)
     //{
     //    /*printf("%s\t%s\t%.2lf", pmove->data.name, pmove->data.num, pmove->data.sGPA + pmove->data.eGPA);*/
     //    qsort(pmove->data.scourse, counts, sizeof(struct coursegrades), compareCourseNum);  // 对每个学生的课程成绩进行排序
     //    pri = pmove->data.scourse;
     //    while (pri->each.cnum[0] != '\0') {
     //       /* printf("\t%.2lf\t%.2lf", pri->grades, pri->GPA);*/
     //        pri++;
     //    }
     //    if (pri->each.cnum[0] == '\0') {
     //        /*printf("\n");*/
     //    }
     //    pmove = pmove->next;
     //}
}
void printList(struct Node* headNode)
{
    setcolor(WHITE);
    loadimage(&img, "./picture/back.png", 1600, 800);
    putimage(0, 0, &img);
    LPBUTTON Button1 = createButton(650, 150, 300, 100, "按GPA排序");
    LPBUTTON Button2 = createButton(650, 550, 300, 100, "按学号排序");
    LPBUTTON Button3 = createButton(650, 150, 300, 100, "保存结果到文件中");
    LPBUTTON Button4 = createButton(650, 550, 300, 100, "不保存结果到文件中");
    LPBUTTON Button115 = createButton(0, 750, 50, 50, "返回");
    drawButton(Button1);
    drawButton(Button2);


    int counts = 0;
    struct Node* pmove = headNode->next;
    struct coursegrades* pri = pmove->data.scourse;
    /*printf("姓名\t编号\tGPA");*/
    while (pri->each.cnum[0] != '\0') {
        printf("\t%s", pri->each.name);
        pri++;
        counts++;
    }
    if (pri->each.cnum[0] == '\0') {
        /* printf("\n");*/
    }
    while (pmove != NULL)
    {
        /*printf("%s\t%s\t%.2lf", pmove->data.name, pmove->data.num, pmove->data.sGPA + pmove->data.eGPA);*/
        qsort(pmove->data.scourse, counts, sizeof(struct coursegrades), compareCourseNum);  // 对每个学生的课程成绩进行排序
        pri = pmove->data.scourse;
        while (pri->each.cnum[0] != '\0') {
            /* printf("\t%.2lf\t%.2lf", pri->grades, pri->GPA);*/
            pri++;
        }
        if (pri->each.cnum[0] == '\0') {
            /*printf("\n");*/
        }
        pmove = pmove->next;
    }
    /* printf("请选择排序方式\n");
     printf("1.按GPA排序\n");
     printf("2.按学号排序\n");*/
    int chosen2 = 0;
    do
    {
        peekmessage(&msg, EM_MOUSE);
        if (msg.x > 650 && msg.x < 950 && msg.y>150 && msg.y < 250 && msg.message == WM_LBUTTONDOWN)
        {
            chosen2 = 1;
            break;
        }
        else if (msg.x > 650 && msg.x < 950 && msg.y>550 && msg.y < 650 && msg.message == WM_LBUTTONDOWN)
        {
            chosen2 = 2;
            break;
        }
    } while (1);
    /*scanf("%d", &chosen2);*/
    switch (chosen2)
    {
    case 1:
        list = mergeSort(list, compareBySGPA);
        print(list);
        cleardevice();
        setcolor(WHITE);
        /*printf("是否保存排序结果到文件中(Y/N)?\n");*/
        loadimage(&img, "./picture/back.png", 1600, 800);
        putimage(0, 0, &img);
        drawButton(Button3);
        drawButton(Button4);
        char saveChoice;
        do
        {
            peekmessage(&msg, EM_MOUSE);
            if (msg.x > 650 && msg.x < 950 && msg.y>150 && msg.y < 250 && msg.message == WM_LBUTTONDOWN)
            {
                saveChoice = 'Y';
                break;
            }
            else if (msg.x > 650 && msg.x < 950 && msg.y>550 && msg.y < 650 && msg.message == WM_LBUTTONDOWN)
            {
                saveChoice = 'N';
                break;
            }
        } while (1);
        /*scanf(" %c", &saveChoice);*/
        if (saveChoice == 'Y' || saveChoice == 'y') {
            saveToFile(list, "student.txt", 3, 0);  // 保存排序后的结果到文件中
        }
        break;
    case 2:
        list = mergeSort(list, compareByStudentID);
        print(list);
        cleardevice();
        loadimage(&img, "./picture/back.png", 1600, 800);
        putimage(0, 0, &img);
        drawButton(Button3);
        drawButton(Button4);

        do
        {
            peekmessage(&msg, EM_MOUSE);
            if (msg.x > 650 && msg.x < 950 && msg.y>150 && msg.y < 250 && msg.message == WM_LBUTTONDOWN)
            {
                saveChoice = 'Y';
                break;
            }
            else if (msg.x > 650 && msg.x < 950 && msg.y>550 && msg.y < 650 && msg.message == WM_LBUTTONDOWN)
            {
                saveChoice = 'N';
                break;
            }
        } while (1);
        /*  printf("是否保存排序结果到文件中(Y/N)?\n");*/
          /*scanf(" %c", &saveChoice);*/
        if (saveChoice == 'Y' || saveChoice == 'y') {
            saveToFile(list, "student.txt", 3, 0);  // 保存排序后的结果到文件中
        }
        break;
        /* default:
             printf("输入错误\n");*/


    }
}
