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
//��������
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
    LPBUTTON Button111 = createButton(0, 0, 400, 100, "¼��ѧ��������Ϣ");
    LPBUTTON Button112 = createButton(400, 0, 400, 100, "¼��ѧ���γ̳ɼ�");
    LPBUTTON Button113 = createButton(800, 0, 400, 100, "¼��γ�");
    LPBUTTON Button114 = createButton(1200, 0, 400, 100, "¼��������ӷ�");
    LPBUTTON Button115 = createButton(0, 750, 50, 50, "����");
    LPBUTTON Button611 = createButton(650, 150, 300, 100, "ɾ��ѧ��������Ϣ");
    LPBUTTON Button612 = createButton(650, 550, 300, 100, "ɾ���γ̳ɼ�");
    LPBUTTON Button411 = createButton(650, 150, 300, 100, "��ѧ�Ų���");
    LPBUTTON Button412 = createButton(650, 550, 300, 100, "����������");
    switch (ButtonResult)
    {
    case 0:
        /*printf("----���˳�ģ�顿----");*/
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
        /*printf("----��¼��ģ�顿----");
        printf("��ѡ��¼�����Ϣ\n");
        printf("1.¼��ѧ��������Ϣ��ѧ�š�������\n2.¼��ѧ���γ̳ɼ�\n3.¼��γ�\n4.¼��������ӷ�");
        scanf("%d", &key1);*/
        switch (key1)
        {
        case 1:
            cleardevice();
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            /*printf("������ѧ����Ϣ(name,num)��");*/
            InputBox(temp.name, 100, _T("������ѧ��������"), _T(""), _T(""), 0, 0, true);
            InputBox(temp.num, 100, _T("������ѧ��ѧ�ţ�"), _T(""), _T(""), 0, 0, true);
            /*scanf("%s%s", temp.name, temp.num);*/
            result = searchDataBYnum(list, temp.num);
            if (result != NULL)
            {
                MessageBox(GetHWnd(), "��ѧ���ѱ�ʹ��", "��Ϣ����", MB_OK);

            }
            else {
                Registerstu(list, temp.num);
                insertData(list, temp);
                saveToFile(list, "student.txt", 1, 0);
            }

            break;
        case 2:
            /* printf("������ѧ��");
             scanf("%s", temp.num);*/
            cleardevice();
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            InputBox(temp.num, 100, _T("������ѧ��ѧ�ţ�"), _T(""), _T(""), 0, 0, true);
            if (searchDataBYnum(list, temp.num) == NULL)
            {
                MessageBox(GetHWnd(), "δ�ҵ�", "����", MB_OK);
                break;
            }
            strcpy(result->data.name, searchDataBYnum(list, temp.num)->data.name);
            strcpy(result->data.num, searchDataBYnum(list, temp.num)->data.num);
            /*printf("������Ҫ¼��Ŀγ���");*/
            /*scanf("%d", &key2);*/
            temp2 = searchDataBYnum(list, temp.num)->data.scourse;
            InputBox(str, 10, _T("������Ҫ¼��Ŀγ���"), _T(""), _T(""), 0, 0, true);
            key2 = atof(str);
            /*printf("����������γ̱�ż��ɼ���cnum��grades��\n");*/
            for (int i = 0; i < key2; i++) {
                InputBox(result->data.scourse[i].each.cnum, 100, _T("������Ҫ¼��Ŀγ̱��"), _T(""), _T(""), 0, 0, true);
                InputBox(result->data.scourse[i].g, 6, _T("������ɼ�"), _T(""), _T(""), 0, 0, true);
                result->data.scourse[i].grades = atof(result->data.scourse[i].g);
                /*scanf("%s%lf", result->data.scourse[i].each.cnum, &result->data.scourse[i].grades);*/
                if (result->data.scourse[i].grades > 100 || result->data.scourse[i].grades < 0) {
                    MessageBox(GetHWnd(), "��������", "����", MB_OK);
                    goto op;
                }
                result->data.scourse[i].GPA = GPACaleach(result->data.scourse[i].grades);
                if (getCourseNameByCnum(result->data.scourse[i].each.cnum, "course.txt") && getCourseCreditByCnum(result->data.scourse[i].each.cnum, "course.txt")) {
                    strcpy(result->data.scourse[i].each.name, getCourseNameByCnum(result->data.scourse[i].each.cnum, "course.txt"));
                    result->data.scourse[i].each.credit = getCourseCreditByCnum(result->data.scourse[i].each.cnum, "course.txt");
                    while (temp2->each.cnum[0] != '\0')
                    {
                        if (strcmp(temp2->each.cnum, result->data.scourse[i].each.cnum) == 0) {
                            MessageBox(GetHWnd(), "�ÿγ��Ѵ���", "����", MB_OK);
                            goto op;
                        }
                        temp2++;
                    }
                }
                else{
                    MessageBox(GetHWnd(), "δ�ҵ��ÿγ�", "����", MB_OK);
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
            /*printf("�������š��γ�����ѧ�֣�cnum��name,credit��");*/
            cleardevice();
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            InputBox(temp.scourse->each.cnum, 100, _T("������Ҫ¼��Ŀγ̱��"), _T(""), _T(""), 0, 0, true);
            if (getCourseNameByCnum(temp.scourse->each.cnum, "course.txt") != NULL) {
                MessageBox(GetHWnd(), "�ÿγ��Ѵ���", "����", MB_OK);
                break;
            }
            InputBox(temp.scourse->each.name, 100, _T("������Ҫ¼��Ŀγ�����"), _T(""), _T(""), 0, 0, true);
            InputBox(temp.scourse->each.c, 100, _T("������Ҫ¼��Ŀγ�ѧ��"), _T(""), _T(""), 0, 0, true);
            temp.scourse->each.credit = atof(temp.scourse->each.c);
            addCourseToFile(temp.scourse->each.cnum, temp.scourse->each.name, temp.scourse->each.credit, "course.txt");
            /*scanf("%s%s%lf", temp.scourse->each.cnum, temp.scourse->each.name, &temp.scourse->each.credit);*/
            break;
        case 4:
            /*printf("������ѧ��(num)��");
            scanf("%s", temp.num);*/
            cleardevice();
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            InputBox(temp.num, 100, _T("������ѧ��"), _T(""), _T(""), 0, 0, true);
            result = searchDataBYnum(list, temp.num);
            if (result == NULL)
            {
                MessageBox(GetHWnd(), "δ�ҵ�", "����", MB_OK);
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
        /*printf("��ѧ�Ų����밴1�������������밴2\n");
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
            /*printf("----������ģ�顿----");
            *
            printf("������Ҫ���ҵ�ѧ��ѧ�ţ�");*/
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            InputBox(temp.num, 100, _T("������Ҫ���ҵ�ѧ��ѧ��"), _T(""), _T(""), 0, 0, true);
            /*scanf("%s", temp.num, 20);*/
            result = searchDataBYnum(list, temp.num);
            if (result == NULL)
            {
                MessageBox(GetHWnd(), "δ�ҵ�", "����", MB_OK);
            }
            else
            {
                cleardevice();
                loadimage(&img, "./picture/back.png", 1600, 800);
                putimage(0, 0, &img);
                struct coursegrades* pri = result->data.scourse;
                /*printf("����\t���\tGPA");*/
                struct coursegrades* pri2 = result->data.scourse;//
                int startX = 200, startY = 100;
                int tableWidth = 1200, rowHeight = 600;
                int cols = 9; // ����
                int colWidth = tableWidth / cols; // ÿ�еĿ��
                drawButton(Button115);

                settextcolor(BLACK);
                outtextxy(startX + 5, startY + 5, "ѧ��");
                outtextxy(startX + colWidth + 5, startY + 5, "����");
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
                char strValue[20]; // �����㹻�Ŀռ�������ת������ַ���
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
            /*printf("----������ģ�顿----");
            printf("������Ҫ���ҵ�ѧ��������");
            scanf("%s", temp.name, 20);*/
            InputBox(temp.name, 100, _T("������Ҫ���ҵ�ѧ������"), _T(""), _T(""), 0, 0, true);
            cleardevice();
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            result = searchDataBYName(list, temp.name);
            if (result == NULL)
            {
                MessageBox(GetHWnd(), "δ�ҵ�", "����", MB_OK);
            }
            else
            {
                struct coursegrades* pri = result->data.scourse;
                /*printf("����\t���\tGPA");*/
                struct coursegrades* pri2 = result->data.scourse;
                int startX = 200, startY = 100;
                int tableWidth = 1200, rowHeight = 600;
                int cols = 9; // ����
                int colWidth = tableWidth / cols; // ÿ�еĿ��

                drawButton(Button115);
                settextcolor(BLACK);
                outtextxy(startX + 5, startY + 5, "ѧ��");
                outtextxy(startX + colWidth + 5, startY + 5, "����");
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
                char strValue[20]; // �����㹻�Ŀռ�������ת������ַ���
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
            printf("�������");
        }
        break;
    case 5:
        /*printf("----���޸�ģ�顿----");
        printf("������Ҫ�޸�ѧ����ѧ��:");
        scanf_s("%s", temp.num, 20);*/
        InputBox(temp.num, 100, _T("������Ҫ�޸ĵ�ѧ��ѧ��"), _T(""), _T(""), 0, 0, true);
        loadimage(&img, "./picture/back.png", 1600, 800);
        putimage(0, 0, &img);
        temp2 = searchDataBYnum(list, temp.num)->data.scourse;
        if (searchDataBYnum(list, temp.num) == NULL)
        {
            MessageBox(GetHWnd(), "δ�ҵ�", "����", MB_OK);
        }
        else
        {
            strcpy(result->data.name, searchDataBYnum(list, temp.num)->data.name);
            strcpy(result->data.num, searchDataBYnum(list, temp.num)->data.num);
            /* printf("������Ҫ�޸ĵĿγ���");
             scanf("%d", &key2);*/
            InputBox(str2, 100, _T("������Ҫ�޸ĵĿγ���"), _T(""), _T(""), 0, 0, true);
            key2 = atof(str2);
            /*printf("����������γ̱�ż��ɼ���cnum��grades��\n");*/
            for (int i = 0; i < key2; i++) {
                /*scanf("%s%lf", result->data.scourse[i].each.cnum, &result->data.scourse[i].grades);*/
                InputBox(result->data.scourse[i].each.cnum, 100, _T("������Ҫ�޸ĵĿγ̵ı��"), _T(""), _T(""), 0, 0, true);
                InputBox(str, 100, _T("������Ҫ�޸ĵĿγ̵ĳɼ�"), _T(""), _T(""), 0, 0, true);
               
                if (getCourseNameByCnum(result->data.scourse[i].each.cnum, "course.txt") && getCourseCreditByCnum(result->data.scourse[i].each.cnum, "course.txt")) {
                    strcpy(result->data.scourse[i].each.name, getCourseNameByCnum(result->data.scourse[i].each.cnum, "course.txt"));
                    result->data.scourse[i].each.credit = getCourseCreditByCnum(result->data.scourse[i].each.cnum, "course.txt");
                    while (strcmp(temp2->each.cnum, result->data.scourse[i].each.cnum) != 0)
                    {
                        temp2++;
                    }
                    result->data.scourse[i].grades = temp2->grades;
                    result->data.scourse[i].GPA = temp2->GPA;
                    MessageBox(GetHWnd(), "�޸ĳɹ�", "��ʾ", MB_OK);
                    saveToFile(result, "student.txt", 5, key2);

                }
                else {
                    MessageBox(GetHWnd(), "δ�ҵ�", "����", MB_OK);
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
    case 6://���
        /* printf("----��ɾ��ģ�顿----");
         printf("ɾ��ѧ��������Ϣ�밴1��ɾ���γ̳ɼ��밴2\n");
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
            /* printf("������Ҫɾ����ѧ��ѧ��");
             scanf("%s", temp.num, 20);*/
            InputBox(temp.num, 100, _T("������Ҫɾ����ѧ��ѧ��"), _T(""), _T(""), 0, 0, true);
            if (searchDataBYnum(list, temp.num) == NULL)
            {
                MessageBox(GetHWnd(), "δ�ҵ�", "����", MB_OK);
            }
            else
            {
                deleteDataBYnum(list, temp.num);
                MessageBox(GetHWnd(), "��ɾ��", "��ʾ", MB_OK);
                saveToFile(list, "student.txt", 3, 0);
                break;
            }
        case 2:
            loadimage(&img, "./picture/back.png", 1600, 800);
            putimage(0, 0, &img);
            /*printf("������Ҫɾ����ѧ��ѧ��");
            scanf("%s", temp.num, 20);*/
            InputBox(temp.num, 100, _T("������Ҫɾ����ѧ��ѧ��"), _T(""), _T(""), 0, 0, true);
            if (searchDataBYnum(list, temp.num) == NULL)
            {
                MessageBox(GetHWnd(), "δ�ҵ�", "����", MB_OK);
            }
            else
            {
                struct coursegrades* temp2 = searchDataBYnum(list, temp.num)->data.scourse;
                strcpy(result->data.name, searchDataBYnum(list, temp.num)->data.name);
                strcpy(result->data.num, searchDataBYnum(list, temp.num)->data.num);
                /*printf("������Ҫɾ���Ŀγ���:");
                scanf("%d", &key2);*/
                InputBox(str2, 100, _T("������Ҫɾ���Ŀγ���"), _T(""), _T(""), 0, 0, true);
                key2 = atof(str2);
                /*printf("����������Ҫɾ���Ŀγ̱��\n");*/
                for (int i = 0; i < key2; i++) {
                    /*scanf("%s", result->data.scourse[i].each.cnum);*/
                    InputBox(result->data.scourse[i].each.cnum, 100, _T("������Ҫɾ���Ŀγ̱��"), _T(""), _T(""), 0, 0, true);
                    if (getCourseNameByCnum(result->data.scourse[i].each.cnum, "course.txt") && getCourseCreditByCnum(result->data.scourse[i].each.cnum, "course.txt")) {
                        while (strcmp(temp2->each.cnum, result->data.scourse[i].each.cnum) != 0)
                        {
                            temp2++;
                        }
                        result->data.scourse[i].grades = temp2->grades;
                        result->data.scourse[i].GPA = temp2->GPA;
                        strcpy(result->data.scourse[i].each.name, getCourseNameByCnum(result->data.scourse[i].each.cnum, "course.txt"));
                        result->data.scourse[i].each.credit = getCourseCreditByCnum(result->data.scourse[i].each.cnum, "course.txt");
                        MessageBox(GetHWnd(), "��ɾ��", "��ʾ", MB_OK);
                    }
                    else {
                        MessageBox(GetHWnd(), "δ�ҵ��ÿγ�", "����", MB_OK);
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
             printf("�����������������...!\n");*/
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
    int cols = 9; // ����
    int colWidth = tableWidth / cols; // ÿ�еĿ��
    LPBUTTON Button1 = createButton(0, 750, 50, 50, "����");
    switch (ButtonResult)
    {
    case 0:
        printf("----���˳�ģ�顿----");
        //system("pause");
        exit(0);
        break;
    case 1:
        /* printf("----�����ģ�顿----\n");
         printf("����\t���\tGPA");*/
        loadimage(&img, "./picture/back.png", 1600, 800);
        putimage(0, 0, &img);
        settextcolor(WHITE);
        setcolor(WHITE);
        drawButton(Button1);

        settextcolor(BLACK);
        /*drawButton(Button1);*/
        outtextxy(startX + 5, startY + 5, "ѧ��");
        outtextxy(startX + colWidth + 5, startY + 5, "����");
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
        char strValue[20]; // �����㹻�Ŀռ�������ת������ַ���
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
             printf("�����������������...!\n");*/
    }
}
