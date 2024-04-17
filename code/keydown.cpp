#define _CRT_SECURE_NO_WARNINGS
#include"keydown.h"
#include "listopretor.h"
#include "loginsystem.h"
extern char Account[20];
extern ExMessage msg;
extern IMAGE img;
extern int ButtonResult;
extern struct Node* list;
extern int q;
extern int w;
extern int currentActiveButton;
//键盘输入
void keyDown_tea()
{
    op:int key1 = 0;
    int key2 = 0;
    char str[10];
    char str2[10];
    int userkey = 0;
    struct student temp = {};
    struct coursegrades* temp2 = NULL;
    struct Node* result = createNode(temp);
    settextcolor(WHITE);
    loadimage(&img, "./picture/back.png", 1600, 800);
    putimage(0, 0, &img);
    LPBUTTON Button111 = createButton(0, 0, 400, 100, "录入学生基本信息");
    LPBUTTON Button112 = createButton(400, 0, 400, 100, "录入学生课程成绩");
    LPBUTTON Button113 = createButton(800, 0, 400, 100, "录入课程");
    LPBUTTON Button114 = createButton(1200, 0, 400, 100, "录入素质类加分");
    LPBUTTON Button115 = createButton(0, 750, 50, 50, "返回");
    LPBUTTON Button611 = createButton(650, 150, 300, 100, "删除学生个人信息");
    LPBUTTON Button612 = createButton(650, 550, 300, 100, "删除课程成绩");
    LPBUTTON Button411 = createButton(650, 150, 300, 100, "按学号查找");
    LPBUTTON Button412 = createButton(650, 550, 300, 100, "按姓名查找");
    switch (ButtonResult)
    {
    case 0:
        /*printf("----【退出模块】----");*/
        //system("pause");
        exit(0);
        break;
    case 1:
        loadimage(&img, "./picture/back.png", 1600, 800);
        putimage(0, 0, &img);
        drawButton(Button111);
        drawButton(Button112);
        drawButton(Button113);
        drawButton(Button114);
        drawButton(Button115);

        do
        {
            peekmessage(&msg, EM_MOUSE);
            if (msg.x > 0 && msg.x < 400 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
            {
                key1 = 1;
                break;
            }
            else if (msg.x > 400 && msg.x < 800 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
            {
                key1 = 2;
                break;
            }
            else if (msg.x > 800 && msg.x < 1200 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
            {
                key1 = 3;
                break;
            }
            else if (msg.x > 1200 && msg.x < 1600 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
            {
                key1 = 4;
                break;
            }
            else if (msg.x > 0 && msg.x < 50 && msg.y>750 && msg.y < 800 && msg.message == WM_LBUTTONDOWN)
            {
                key1 = 5;
                break;
            }
        } while (1);
        /*printf("----【录入模块】----");
        printf("请选择录入的信息\n");
        printf("1.录入学生基本信息（学号、姓名）\n2.录入学生课程成绩\n3.录入课程\n4.录入素质类加分");
        scanf("%d", &key1);*/
        switch (key1)
        {
        case 1:
            cleardevice();
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            /*printf("请输入学生信息(name,num)：");*/
            InputBox(temp.name, 100, _T("请输入学生姓名："), _T(""), _T(""), 0, 0, true);
            InputBox(temp.num, 100, _T("请输入学生学号："), _T(""), _T(""), 0, 0, true);
            /*scanf("%s%s", temp.name, temp.num);*/
            result = searchDataBYnum(list, temp.num);
            if (result != NULL)
            {
                MessageBox(GetHWnd(), "该学号已被使用", "消息标题", MB_OK);

            }
            else {
                Registerstu(list, temp.num);
                insertData(list, temp);
                saveToFile(list, "student.txt", 1, 0);
            }

            break;
        case 2:
            /* printf("请输入学号");
             scanf("%s", temp.num);*/
            cleardevice();
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            InputBox(temp.num, 100, _T("请输入学生学号："), _T(""), _T(""), 0, 0, true);
            if (searchDataBYnum(list, temp.num) == NULL)
            {
                MessageBox(GetHWnd(), "未找到", "警告", MB_OK);
                break;
            }
            strcpy(result->data.name, searchDataBYnum(list, temp.num)->data.name);
            strcpy(result->data.num, searchDataBYnum(list, temp.num)->data.num);
            /*printf("请输入要录入的课程数");*/
            /*scanf("%d", &key2);*/
            temp2 = searchDataBYnum(list, temp.num)->data.scourse;
            InputBox(str, 10, _T("请输入要录入的课程数"), _T(""), _T(""), 0, 0, true);
            key2 = atof(str);
            /*printf("请依次输入课程编号及成绩（cnum，grades）\n");*/
            for (int i = 0; i < key2; i++) {
                InputBox(result->data.scourse[i].each.cnum, 100, _T("请输入要录入的课程编号"), _T(""), _T(""), 0, 0, true);
                InputBox(result->data.scourse[i].g, 6, _T("请输入成绩"), _T(""), _T(""), 0, 0, true);
                result->data.scourse[i].grades = atof(result->data.scourse[i].g);
                /*scanf("%s%lf", result->data.scourse[i].each.cnum, &result->data.scourse[i].grades);*/
                if (result->data.scourse[i].grades > 100 || result->data.scourse[i].grades < 0) {
                    MessageBox(GetHWnd(), "分数错误", "警告", MB_OK);
                    goto op;
                }
                result->data.scourse[i].GPA = GPACaleach(result->data.scourse[i].grades);
                if (getCourseNameByCnum(result->data.scourse[i].each.cnum, "course.txt") && getCourseCreditByCnum(result->data.scourse[i].each.cnum, "course.txt")) {
                    strcpy(result->data.scourse[i].each.name, getCourseNameByCnum(result->data.scourse[i].each.cnum, "course.txt"));
                    result->data.scourse[i].each.credit = getCourseCreditByCnum(result->data.scourse[i].each.cnum, "course.txt");
                    while (temp2->each.cnum[0] != '\0')
                    {
                        if (strcmp(temp2->each.cnum, result->data.scourse[i].each.cnum) == 0) {
                            MessageBox(GetHWnd(), "该课程已存在", "警告", MB_OK);
                            goto op;
                        }
                        temp2++;
                    }
                }
                else{
                    MessageBox(GetHWnd(), "未找到该课程", "警告", MB_OK);
                    goto op;
                }

            }
            saveToFile(result, "student.txt", 2, key2);
            saveGPAToFile(list, "GPA.txt");
            deleteList(list);
            readFromFile(list, "student.txt", 1);
            readGPAFromFile(list, "GPA.txt");
            sGPAcalculate(list);
            break;
        case 3:
            /*printf("请输入编号、课程名和学分（cnum，name,credit）");*/
            cleardevice();
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            InputBox(temp.scourse->each.cnum, 100, _T("请输入要录入的课程编号"), _T(""), _T(""), 0, 0, true);
            if (getCourseNameByCnum(temp.scourse->each.cnum, "course.txt") != NULL) {
                MessageBox(GetHWnd(), "该课程已存在", "警告", MB_OK);
                break;
            }
            InputBox(temp.scourse->each.name, 100, _T("请输入要录入的课程名称"), _T(""), _T(""), 0, 0, true);
            InputBox(temp.scourse->each.c, 100, _T("请输入要录入的课程学分"), _T(""), _T(""), 0, 0, true);
            temp.scourse->each.credit = atof(temp.scourse->each.c);
            addCourseToFile(temp.scourse->each.cnum, temp.scourse->each.name, temp.scourse->each.credit, "course.txt");
            /*scanf("%s%s%lf", temp.scourse->each.cnum, temp.scourse->each.name, &temp.scourse->each.credit);*/
            break;
        case 4:
            /*printf("请输入学号(num)：");
            scanf("%s", temp.num);*/
            cleardevice();
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            InputBox(temp.num, 100, _T("请输入学号"), _T(""), _T(""), 0, 0, true);
            result = searchDataBYnum(list, temp.num);
            if (result == NULL)
            {
                MessageBox(GetHWnd(), "未找到", "警告", MB_OK);
            }
            else
            {
                result->data.eGPA += GPAextra();
            }
            saveGPAToFile(list, "GPA.txt");
            deleteList(list);
            readFromFile(list, "student.txt", 1);
            readGPAFromFile(list, "GPA.txt");
            sGPAcalculate(list);
            break;
        case 5:
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            break;
        }
        saveGPAToFile(list, "GPA.txt");
        deleteList(list);
        readFromFile(list, "student.txt", 1);
        readGPAFromFile(list, "GPA.txt");
        sGPAcalculate(list);
        break;
    case 2:
        print(list);
        break;
    case 3:
        printList(list);
        break;
    case 4:
        /*printf("按学号查找请按1，按姓名查找请按2\n");
        scanf("%d", &userkey);*/
        loadimage(&img, "./picture/back.png", 1600, 800);
        putimage(0, 0, &img);
        drawButton(Button411);
        drawButton(Button412);
        /*drawButton(Button115); */
        do
        {
            peekmessage(&msg, EM_MOUSE);
            if (msg.x > 650 && msg.x < 950 && msg.y>150 && msg.y < 250 && msg.message == WM_LBUTTONDOWN)
            {
                userkey = 1;
                break;
            }
            else if (msg.x > 650 && msg.x < 950 && msg.y>550 && msg.y < 650 && msg.message == WM_LBUTTONDOWN)
            {
                userkey = 2;
                break;
            }
        } while (1);
        switch (userkey)
        {
        case 1:
            /*printf("----【查找模块】----");
            *
            printf("请输入要查找的学生学号：");*/
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            InputBox(temp.num, 100, _T("请输入要查找的学生学号"), _T(""), _T(""), 0, 0, true);
            /*scanf("%s", temp.num, 20);*/
            result = searchDataBYnum(list, temp.num);
            if (result == NULL)
            {
                MessageBox(GetHWnd(), "未找到", "警告", MB_OK);
            }
            else
            {
                cleardevice();
                loadimage(&img, "./picture/back.png", 1600, 800);
                putimage(0, 0, &img);
                struct coursegrades* pri = result->data.scourse;
                /*printf("姓名\t编号\tGPA");*/
                struct coursegrades* pri2 = result->data.scourse;//
                int startX = 200, startY = 100;
                int tableWidth = 1200, rowHeight = 600;
                int cols = 9; // 列数
                int colWidth = tableWidth / cols; // 每列的宽度
                drawButton(Button115);

                settextcolor(BLACK);
                outtextxy(startX + 5, startY + 5, "学号");
                outtextxy(startX + colWidth + 5, startY + 5, "姓名");
                outtextxy(startX + 2 * colWidth + 5, startY + 5, "GPA");

                outtextxy(startX + 3 * colWidth + 5, startY + 5, result->data.scourse[0].each.name);
                outtextxy(startX + 4 * colWidth + 5, startY + 5, result->data.scourse[1].each.name);
                outtextxy(startX + 5 * colWidth + 5, startY + 5, result->data.scourse[2].each.name);
                outtextxy(startX + 6 * colWidth + 5, startY + 5, result->data.scourse[3].each.name);
                outtextxy(startX + 7 * colWidth + 5, startY + 5, result->data.scourse[4].each.name);
                outtextxy(startX + 8 * colWidth + 5, startY + 5, result->data.scourse[5].each.name);
                settextcolor(BLACK);
                outtextxy(startX + 5, startY + 30, result->data.name);
                outtextxy(startX + colWidth + 5, startY + 30, result->data.num);
                char strValue[20]; // 保留足够的空间来容纳转换后的字符串
                sprintf(strValue, "%.2lf", result->data.eGPA + result->data.sGPA);
                outtextxy(startX + 2 * colWidth + 5, startY + 30, strValue);
                char strValue0[20]; char strValue1[20]; char strValue2[20]; char strValue3[20]; char strValue4[20]; char strValue5[20];
                sprintf(strValue0, "%.2lf", result->data.scourse[0].grades);
                sprintf(strValue1, "%.2lf", result->data.scourse[1].grades);
                sprintf(strValue2, "%.2lf", result->data.scourse[2].grades);
                sprintf(strValue3, "%.2lf", result->data.scourse[3].grades);
                sprintf(strValue4, "%.2lf", result->data.scourse[4].grades);
                sprintf(strValue5, "%.2lf", result->data.scourse[5].grades);
                outtextxy(startX + 3 * colWidth + 5, startY + 30, strValue0);
                outtextxy(startX + 4 * colWidth + 5, startY + 30, strValue1);
                outtextxy(startX + 5 * colWidth + 5, startY + 30, strValue2);
                outtextxy(startX + 6 * colWidth + 5, startY + 30, strValue3);
                outtextxy(startX + 7 * colWidth + 5, startY + 30, strValue4);
                outtextxy(startX + 8 * colWidth + 5, startY + 30, strValue5);

                do
                {
                    peekmessage(&msg, EM_MOUSE);
                    if (msg.x > 0 && msg.x < 50 && msg.y>750 && msg.y < 800 && msg.message == WM_LBUTTONDOWN)
                    {
                        break;
                    }
                } while (1);
            }
            break;
        case 2:
            /*printf("----【查找模块】----");
            printf("请输入要查找的学生姓名：");
            scanf("%s", temp.name, 20);*/
            InputBox(temp.name, 100, _T("请输入要查找的学生姓名"), _T(""), _T(""), 0, 0, true);
            cleardevice();
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            result = searchDataBYName(list, temp.name);
            if (result == NULL)
            {
                MessageBox(GetHWnd(), "未找到", "警告", MB_OK);
            }
            else
            {
                struct coursegrades* pri = result->data.scourse;
                /*printf("姓名\t编号\tGPA");*/
                struct coursegrades* pri2 = result->data.scourse;
                int startX = 200, startY = 100;
                int tableWidth = 1200, rowHeight = 600;
                int cols = 9; // 列数
                int colWidth = tableWidth / cols; // 每列的宽度

                drawButton(Button115);
                settextcolor(BLACK);
                outtextxy(startX + 5, startY + 5, "学号");
                outtextxy(startX + colWidth + 5, startY + 5, "姓名");
                outtextxy(startX + 2 * colWidth + 5, startY + 5, "GPA");

                outtextxy(startX + 3 * colWidth + 5, startY + 5, result->data.scourse[0].each.name);
                outtextxy(startX + 4 * colWidth + 5, startY + 5, result->data.scourse[1].each.name);
                outtextxy(startX + 5 * colWidth + 5, startY + 5, result->data.scourse[2].each.name);
                outtextxy(startX + 6 * colWidth + 5, startY + 5, result->data.scourse[3].each.name);
                outtextxy(startX + 7 * colWidth + 5, startY + 5, result->data.scourse[4].each.name);
                outtextxy(startX + 8 * colWidth + 5, startY + 5, result->data.scourse[5].each.name);
                settextcolor(BLACK);
                outtextxy(startX + 5, startY + 30, result->data.name);
                outtextxy(startX + colWidth + 5, startY + 30, result->data.num);
                char strValue[20]; // 保留足够的空间来容纳转换后的字符串
                sprintf(strValue, "%.2lf", result->data.eGPA + result->data.sGPA);
                outtextxy(startX + 2 * colWidth + 5, startY + 30, strValue);
                char strValue0[20]; char strValue1[20]; char strValue2[20]; char strValue3[20]; char strValue4[20]; char strValue5[20];
                sprintf(strValue0, "%.2lf", result->data.scourse[0].grades);
                sprintf(strValue1, "%.2lf", result->data.scourse[1].grades);
                sprintf(strValue2, "%.2lf", result->data.scourse[2].grades);
                sprintf(strValue3, "%.2lf", result->data.scourse[3].grades);
                sprintf(strValue4, "%.2lf", result->data.scourse[4].grades);
                sprintf(strValue5, "%.2lf", result->data.scourse[5].grades);
                outtextxy(startX + 3 * colWidth + 5, startY + 30, strValue0);
                outtextxy(startX + 4 * colWidth + 5, startY + 30, strValue1);
                outtextxy(startX + 5 * colWidth + 5, startY + 30, strValue2);
                outtextxy(startX + 6 * colWidth + 5, startY + 30, strValue3);
                outtextxy(startX + 7 * colWidth + 5, startY + 30, strValue4);
                outtextxy(startX + 8 * colWidth + 5, startY + 30, strValue5);

                do
                {
                    peekmessage(&msg, EM_MOUSE);
                    if (msg.x > 0 && msg.x < 50 && msg.y>750 && msg.y < 800 && msg.message == WM_LBUTTONDOWN)
                    {
                        break;
                    }
                } while (1);
            }
            break;
        default:
            printf("输入错误");
        }
        break;
    case 5:
        /*printf("----【修改模块】----");
        printf("请输入要修改学生的学号:");
        scanf_s("%s", temp.num, 20);*/
        InputBox(temp.num, 100, _T("请输入要修改的学生学号"), _T(""), _T(""), 0, 0, true);
        loadimage(&img, "./picture/back.png", 1600, 800);
        putimage(0, 0, &img);
        temp2 = searchDataBYnum(list, temp.num)->data.scourse;
        if (searchDataBYnum(list, temp.num) == NULL)
        {
            MessageBox(GetHWnd(), "未找到", "警告", MB_OK);
        }
        else
        {
            strcpy(result->data.name, searchDataBYnum(list, temp.num)->data.name);
            strcpy(result->data.num, searchDataBYnum(list, temp.num)->data.num);
            /* printf("请输入要修改的课程数");
             scanf("%d", &key2);*/
            InputBox(str2, 100, _T("请输入要修改的课程数"), _T(""), _T(""), 0, 0, true);
            key2 = atof(str2);
            /*printf("请依次输入课程编号及成绩（cnum，grades）\n");*/
            for (int i = 0; i < key2; i++) {
                /*scanf("%s%lf", result->data.scourse[i].each.cnum, &result->data.scourse[i].grades);*/
                InputBox(result->data.scourse[i].each.cnum, 100, _T("请输入要修改的课程的编号"), _T(""), _T(""), 0, 0, true);
                InputBox(str, 100, _T("请输入要修改的课程的成绩"), _T(""), _T(""), 0, 0, true);
               
                if (getCourseNameByCnum(result->data.scourse[i].each.cnum, "course.txt") && getCourseCreditByCnum(result->data.scourse[i].each.cnum, "course.txt")) {
                    strcpy(result->data.scourse[i].each.name, getCourseNameByCnum(result->data.scourse[i].each.cnum, "course.txt"));
                    result->data.scourse[i].each.credit = getCourseCreditByCnum(result->data.scourse[i].each.cnum, "course.txt");
                    while (strcmp(temp2->each.cnum, result->data.scourse[i].each.cnum) != 0)
                    {
                        temp2++;
                    }
                    result->data.scourse[i].grades = temp2->grades;
                    result->data.scourse[i].GPA = temp2->GPA;
                    MessageBox(GetHWnd(), "修改成功", "提示", MB_OK);
                    saveToFile(result, "student.txt", 5, key2);

                }
                else {
                    MessageBox(GetHWnd(), "未找到", "警告", MB_OK);
                    break;
                } 
                result->data.scourse[i].grades = atof(str);
                result->data.scourse[i].GPA = GPACaleach(result->data.scourse[i].grades);
                saveToFile(result, "student.txt", 2, key2);
            }
        }
        saveGPAToFile(list, "GPA.txt");
        deleteList(list);
        readFromFile(list, "student.txt", 1);
        readGPAFromFile(list, "GPA.txt");
        sGPAcalculate(list);
        break;
    case 6://完成
        /* printf("----【删除模块】----");
         printf("删除学生个人信息请按1，删除课程成绩请按2\n");
         scanf("%d", &key1);*/
        cleardevice();
        loadimage(&img, "./picture/back.png", 1600, 800);
        putimage(0, 0, &img);
        drawButton(Button611);
        drawButton(Button612);
        do
        {
            peekmessage(&msg, EM_MOUSE);
            if (msg.x > 650 && msg.x < 950 && msg.y>150 && msg.y < 250 && msg.message == WM_LBUTTONDOWN)
            {
                key1 = 1;
                break;
            }
            else if (msg.x > 650 && msg.x < 950 && msg.y>550 && msg.y < 650 && msg.message == WM_LBUTTONDOWN)
            {
                key1 = 2;
                break;
            }
        } while (1);
        switch (key1)
        {
        case 1:
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            /* printf("请输入要删除的学生学号");
             scanf("%s", temp.num, 20);*/
            InputBox(temp.num, 100, _T("请输入要删除的学生学号"), _T(""), _T(""), 0, 0, true);
            if (searchDataBYnum(list, temp.num) == NULL)
            {
                MessageBox(GetHWnd(), "未找到", "警告", MB_OK);
            }
            else
            {
                deleteDataBYnum(list, temp.num);
                MessageBox(GetHWnd(), "已删除", "提示", MB_OK);
                saveToFile(list, "student.txt", 3, 0);
                break;
            }
        case 2:
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            /*printf("请输入要删除的学生学号");
            scanf("%s", temp.num, 20);*/
            InputBox(temp.num, 100, _T("请输入要删除的学生学号"), _T(""), _T(""), 0, 0, true);
            if (searchDataBYnum(list, temp.num) == NULL)
            {
                MessageBox(GetHWnd(), "未找到", "警告", MB_OK);
            }
            else
            {
                struct coursegrades* temp2 = searchDataBYnum(list, temp.num)->data.scourse;
                strcpy(result->data.name, searchDataBYnum(list, temp.num)->data.name);
                strcpy(result->data.num, searchDataBYnum(list, temp.num)->data.num);
                /*printf("请输入要删除的课程数:");
                scanf("%d", &key2);*/
                InputBox(str2, 100, _T("请输入要删除的课程数"), _T(""), _T(""), 0, 0, true);
                key2 = atof(str2);
                /*printf("请依次输入要删除的课程编号\n");*/
                for (int i = 0; i < key2; i++) {
                    /*scanf("%s", result->data.scourse[i].each.cnum);*/
                    InputBox(result->data.scourse[i].each.cnum, 100, _T("请输入要删除的课程编号"), _T(""), _T(""), 0, 0, true);
                    if (getCourseNameByCnum(result->data.scourse[i].each.cnum, "course.txt") && getCourseCreditByCnum(result->data.scourse[i].each.cnum, "course.txt")) {
                        while (strcmp(temp2->each.cnum, result->data.scourse[i].each.cnum) != 0)
                        {
                            temp2++;
                        }
                        result->data.scourse[i].grades = temp2->grades;
                        result->data.scourse[i].GPA = temp2->GPA;
                        strcpy(result->data.scourse[i].each.name, getCourseNameByCnum(result->data.scourse[i].each.cnum, "course.txt"));
                        result->data.scourse[i].each.credit = getCourseCreditByCnum(result->data.scourse[i].each.cnum, "course.txt");
                        MessageBox(GetHWnd(), "已删除", "提示", MB_OK);
                    }
                    else {
                        MessageBox(GetHWnd(), "未找到该课程", "警告", MB_OK);
                        break;
                    }
                }
                saveToFile(result, "student.txt", 5, key2);
                break;
            }
            break;
        }
        saveGPAToFile(list, "GPA.txt");
        deleteList(list);
        readFromFile(list, "student.txt", 1);
        readGPAFromFile(list, "GPA.txt");
        sGPAcalculate(list);

        break;
    case 7:
        RegisterTea();
        break;
    case 8:
        saveGPAToFile(list, "GPA.txt");
        deleteList(list);
        readFromFile(list, "student.txt", 1);
        readGPAFromFile(list, "GPA.txt");
        sGPAcalculate(list);
        break;
        /* default:
             printf("输入错误！请重新输入...!\n");*/
    };

}
void KeyDown_stu()
{
    settextcolor(WHITE);
    /*int userkey = 0;*/
    struct student temp;
    struct Node* result;
    result = searchDataBYnum(list, Account);
    struct coursegrades* pri = result->data.scourse;
    struct coursegrades* pri2 = result->data.scourse;
    /*scanf("%d", &userkey);*/
    int startX = 200, startY = 100;
    int tableWidth = 1200, rowHeight = 600;
    int cols = 9; // 列数
    int colWidth = tableWidth / cols; // 每列的宽度
    LPBUTTON Button1 = createButton(0, 750, 50, 50, "返回");
    switch (ButtonResult)
    {
    case 0:
        printf("----【退出模块】----");
        //system("pause");
        exit(0);
        break;
    case 1:
        /* printf("----【浏览模块】----\n");
         printf("姓名\t编号\tGPA");*/
        loadimage(&img, "./picture/back.png", 1600, 800);
        putimage(0, 0, &img);
        settextcolor(WHITE);
        setcolor(WHITE);
        drawButton(Button1);

        settextcolor(BLACK);
        /*drawButton(Button1);*/
        outtextxy(startX + 5, startY + 5, "学号");
        outtextxy(startX + colWidth + 5, startY + 5, "姓名");
        outtextxy(startX + 2 * colWidth + 5, startY + 5, "GPA");
        outtextxy(startX + 3 * colWidth + 5, startY + 5, result->data.scourse[0].each.name);
        outtextxy(startX + 4 * colWidth + 5, startY + 5, result->data.scourse[1].each.name);
        outtextxy(startX + 5 * colWidth + 5, startY + 5, result->data.scourse[2].each.name);
        outtextxy(startX + 6 * colWidth + 5, startY + 5, result->data.scourse[3].each.name);
        outtextxy(startX + 7 * colWidth + 5, startY + 5, result->data.scourse[4].each.name);
        outtextxy(startX + 8 * colWidth + 5, startY + 5, result->data.scourse[5].each.name);
        settextcolor(BLACK);
        outtextxy(startX + 5, startY + 30, result->data.name);
        outtextxy(startX + colWidth + 5, startY + 30, result->data.num);
        char strValue[20]; // 保留足够的空间来容纳转换后的字符串
        sprintf(strValue, "%.2lf", result->data.eGPA + result->data.sGPA);
        outtextxy(startX + 2 * colWidth + 5, startY + 30, strValue);
        char strValue0[20]; char strValue1[20]; char strValue2[20]; char strValue3[20]; char strValue4[20]; char strValue5[20];
        sprintf(strValue0, "%.2lf", result->data.scourse[0].grades);
        sprintf(strValue1, "%.2lf", result->data.scourse[1].grades);
        sprintf(strValue2, "%.2lf", result->data.scourse[2].grades);
        sprintf(strValue3, "%.2lf", result->data.scourse[3].grades);
        sprintf(strValue4, "%.2lf", result->data.scourse[4].grades);
        sprintf(strValue5, "%.2lf", result->data.scourse[5].grades);
        outtextxy(startX + 3 * colWidth + 5, startY + 30, strValue0);
        outtextxy(startX + 4 * colWidth + 5, startY + 30, strValue1);
        outtextxy(startX + 5 * colWidth + 5, startY + 30, strValue2);
        outtextxy(startX + 6 * colWidth + 5, startY + 30, strValue3);
        outtextxy(startX + 7 * colWidth + 5, startY + 30, strValue4);
        outtextxy(startX + 8 * colWidth + 5, startY + 30, strValue5);
        do
        {
            peekmessage(&msg, EM_MOUSE);
            if (msg.x > 0 && msg.x < 50 && msg.y>750 && msg.y < 800 && msg.message == WM_LBUTTONDOWN)
            {
                break;
            }
        } while (1);

        break;
    case 2:
        change();
        break;
        /* default:
             printf("输入错误！请重新输入...!\n");*/
    }
}
