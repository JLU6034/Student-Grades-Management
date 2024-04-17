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
#include "keydown.h"
extern char Account[20];
extern IMAGE test[2];
extern ExMessage msg;
extern IMAGE img;
extern struct Node* list;
//�˵�
int RegisterTea() {
    loadimage(&img, "./picture/back.png", 1600, 800);
    putimage(0, 0, &img);//��ʦע��
    char account[16], password[16], reginum[16];  //�˺ţ����룬ע������
    FILE* fp;
    int turn = 1;                                 //���ڼ���˺��Ƿ���ע��Ŀ���
    char password_che[16];						//���ڼ����������������Ƿ�һ��
    char str1[16] = { 0 }, str2[16] = { 0 };             //�����˺ţ���������
    /*printf("���������Ĺ��ţ�");
    scanf("%s", account);*/
    InputBox(account, 20, _T("��������Ҫע����˺�"), _T(""), _T(""), 0, 0, true);
    do {
        /*printf("���������룺");
        scanf("%s", password);*/
        InputBox(password, 20, _T("����������"), _T(""), _T(""), 0, 0, true);
        /*printf("���ٴ��������룺");
        scanf("%s", password_che);*/
        InputBox(password_che, 20, _T("���ٴ���������"), _T(""), _T(""), 0, 0, true);
        if (strcmp(password, password_che)) { MessageBox(GetHWnd(), "���벻һ�£�����������", "����", MB_OK); }/*printf("���벻һ�£����������룡\n\n");*/
    } while (strcmp(password, password_che));
    /* printf("�������ʦ�����֤���룺");
     scanf("%s", reginum);*/
    InputBox(reginum, 20, _T("�������ʦ�����֤����"), _T(""), _T(""), 0, 0, true);
    if (strcmp(reginum, "114514")) {
        /*printf("ע���������ע��ʧ�ܣ�\n");*/
        MessageBox(GetHWnd(), "ע���������ע��ʧ�ܣ�", "����", MB_OK);
        return 0;
    }
    else {
        if ((fp = fopen("accountTea.txt", "a+")) == NULL) {
            /* printf("ע��ʧ�ܣ�\n");*/
            MessageBox(GetHWnd(), "ע��ʧ�ܣ�", "����", MB_OK);
            return 0;
        }
        else {
            while (!feof(fp)) {
                fscanf(fp, "%s%s", str1, str2);
                if (!strcmp(str1, account)) {
                    turn = 0;
                    break;
                }
            }
            if (turn) {
                fseek(fp, 0, 2);
                fprintf(fp, "%s %s\n", account, password);
                fflush(fp);
                /*printf("ע��ɹ���\n");*/
                MessageBox(GetHWnd(), "ע��ɹ���", "", MB_OK);
                fclose(fp);
                return 1;
            }
            else {
                MessageBox(GetHWnd(), "���˻���ע��", "", MB_OK);
                fclose(fp);
                return 0;
            }
        }
    }
}//��ʦע��
int LoginTea() {									 //��ʦ��¼
    char account[16], password[16];       	    //�˺ţ�����
    char che_acc[16] = { 0 }, che_pas[16] = { 0 };       //�����˺ţ���������
    FILE* fp;
    int turn = 0;                                 //���ڼ����˺������Ƿ�ƥ��
    /*printf("���������Ĺ��ţ�");*/
    /*scanf("%s", account);*/
    InputBox(account, 17, _T("���������Ĺ���"), _T(""), _T(""), 0, 0, true);
    /*printf("���������룺");
    scanf("%s", password);*/
    InputBox(password, 17, _T("����������"), _T(""), _T(""), 0, 0, true);
    if ((fp = fopen("accountTea.txt", "r")) == NULL) {
        /*printf("��¼ʧ�ܣ�\n");*/
        /*MessageBox(GetHWnd(), "����һ��������ʾ����Ϣ", "��Ϣ����", MB_OK);*/
        return 0;
    }
    else {
        while (!feof(fp)) {
            fscanf(fp, "%s%s", che_acc, che_pas);
            if (!strcmp(che_acc, account) && !strcmp(che_pas, password)) {
                turn = 1;
                break;
            }
        }
        if (turn) {
            MessageBox(GetHWnd(), "�ѽ����ʦ����", "", MB_OK);
            fclose(fp);
            return 1;
        }
        else {
            fclose(fp);
            return 0;
        }
    }
}//��ʦ��¼
struct Node* searchDataBYnum_Account(struct Node* headNode, const char* num)
{
    struct Node* pmove = headNode->next;
    while (pmove != NULL && strcmp(pmove->data.num, num))
    {
        pmove = pmove->next;
    }
    return pmove;
};
int Registerstu(struct Node* headNode, char* account)
{
    struct Node* pmove = headNode->next;
    FILE* fp;
    if ((fp = fopen("accountStu.txt", "a+")) == NULL)
    {
        return 0;
    }

    fseek(fp, 0, 2);
    fprintf(fp, "%s %s\n", account, "123456");
    fflush(fp);
    fclose(fp);


}//ѧ��ע��
void change()
{
    loadimage(&img, "./picture/back.png", 1600, 800);
    putimage(0, 0, &img);
    struct student temp;
    struct Node* result;
    char check[20];
    result = searchDataBYnum_Account(list, Account);
    /*printf("������������");
    scanf("%s", temp.password, 20);*/
    InputBox(temp.password, 20, _T("������������"), _T(""), _T(""), 0, 0, true);
    /*  getchar();*/
     /* printf("���ٴ�����������");
      scanf("%s", check, 20);*/
    InputBox(check, 20, _T("���ٴ�����������"), _T(""), _T(""), 0, 0, true);
    int key = strcmp(temp.password, check);
    if (!key)
    {
        strcpy(result->data.password, temp.password);
        saveToFilea_account(list, "accountStu.txt");
        MessageBox(GetHWnd(), "�����޸ĳɹ��������µ�½", "", MB_OK);
        exit(0);
    }
    else
    {
        MessageBox(GetHWnd(), "�������벻һ��", "����", MB_OK);
    }

}
int LoginStu() {                                  //ѧ����¼
    char account[20], password[20];       	    //�˺ţ�����
    char che_acc[20] = { 0 }, che_pas[20] = { 0 };       //�����˺ţ���������
    FILE* fp;
    int turn = 0;                                 //���ڼ����˺������Ƿ�ƥ��
    /* printf("����������ѧ�ţ�");
     scanf("%s", account);*/
    InputBox(account, 16, _T("����������ѧ��"), _T(""), _T(""), 0, 0, true);
    /*printf("���������룺");
    scanf("%s", password);*/
    InputBox(password, 20, _T("����������"), _T(""), _T(""), 0, 0, true);
    if ((fp = fopen("accountStu.txt", "r")) == NULL) {
        MessageBox(GetHWnd(), "��¼ʧ��", "����", MB_OK);
        return 0;
    }
    else {
        while (!feof(fp)) {
            fscanf(fp, "%s%s", che_acc, che_pas);
            if (!strcmp(che_acc, account) && !strcmp(che_pas, password)) {
                turn = 1;
                break;
            }
        }
        if (turn) {
            strcpy(Account, account);
            MessageBox(GetHWnd(), "��½�ɹ�", " ", MB_OK);
            fclose(fp);
            return 1;
        }
        else {

            fclose(fp);
            return 0;
        }
    }
}//ѧ����¼
void Loginmenu()
{
    int choice;
    /* printf("��ӭʹ��ѧ���ɼ�����ϵͳ");
     printf("��ѡ�����ĵ�¼��ݣ�\n");
     printf("1.��ʦ\n");
     printf("2.ѧ��\n");
     printf("0.�˳�\n");*/
     /*scanf("%d", &choice);*/
    LPBUTTON Button21 = createButton(650, 150, 300, 100, "��ʦ");
    LPBUTTON Button22 = createButton(650, 350, 300, 100, "ѧ��");
    LPBUTTON Button23 = createButton(650, 550, 300, 100, "�˳�");
    drawButton(Button21);
    drawButton(Button22);
    drawButton(Button23);
    do
    {
        peekmessage(&msg, EM_MOUSE);
        if (msg.x > 650 && msg.x < 950 && msg.y>150 && msg.y < 250 && msg.message == WM_LBUTTONDOWN)
        {
            choice = 1;
            break;
        }
        if (msg.x > 650 && msg.x < 950 && msg.y>350 && msg.y < 450 && msg.message == WM_LBUTTONDOWN)
        {
            choice = 2;
            break;
        }
        if (msg.x > 650 && msg.x < 950 && msg.y>550 && msg.y < 650 && msg.message == WM_LBUTTONDOWN)
        {
            choice = 0;
            break;
        }
    } while (1);
    while (1)
    {
        switch (choice)
        {
        case 1:
            while (1)
            {
                int key = LoginTea();
                if (key == 1)
                {
                    break;
                }
                else
                {
                    MessageBox(GetHWnd(), "�˺Ż��������������", "", MB_OK);
                }
            }

            while (1)
            {
                DrawMenu();
                keyDown_tea();
            }
            break;
        case 2:
            while (1)
            {
                int key = LoginStu();
                if (key == 1)
                {
                    /*DrawSTMenu();
                    KeyDown_stu();*/
                    break;
                }
                else
                {
                    MessageBox(GetHWnd(), "�˺Ż��������������", "", MB_OK);
                }
            }
            while (1)
            {
                DrawSTMenu();
                KeyDown_stu();

            }
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("�����������������...!\n");
        }
    }

}