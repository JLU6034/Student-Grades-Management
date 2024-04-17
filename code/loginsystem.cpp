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
//菜单
int RegisterTea() {
    loadimage(&img, "./picture/back.png", 1600, 800);
    putimage(0, 0, &img);//教师注册
    char account[16], password[16], reginum[16];  //账号，密码，注册密码
    FILE* fp;
    int turn = 1;                                 //用于检测账号是否已注册的开关
    char password_che[16];						//用于检测两次输入的密码是否一致
    char str1[16] = { 0 }, str2[16] = { 0 };             //检验账号，检验密码
    /*printf("请输入您的工号：");
    scanf("%s", account);*/
    InputBox(account, 20, _T("请输入您要注册的账号"), _T(""), _T(""), 0, 0, true);
    do {
        /*printf("请输入密码：");
        scanf("%s", password);*/
        InputBox(password, 20, _T("请输入密码"), _T(""), _T(""), 0, 0, true);
        /*printf("请再次输入密码：");
        scanf("%s", password_che);*/
        InputBox(password_che, 20, _T("请再次输入密码"), _T(""), _T(""), 0, 0, true);
        if (strcmp(password, password_che)) { MessageBox(GetHWnd(), "密码不一致，请重新输入", "警告", MB_OK); }/*printf("密码不一致，请重新输入！\n\n");*/
    } while (strcmp(password, password_che));
    /* printf("请输入教师身份验证密码：");
     scanf("%s", reginum);*/
    InputBox(reginum, 20, _T("请输入教师身份验证密码"), _T(""), _T(""), 0, 0, true);
    if (strcmp(reginum, "114514")) {
        /*printf("注册密码错误，注册失败！\n");*/
        MessageBox(GetHWnd(), "注册密码错误，注册失败！", "警告", MB_OK);
        return 0;
    }
    else {
        if ((fp = fopen("accountTea.txt", "a+")) == NULL) {
            /* printf("注册失败！\n");*/
            MessageBox(GetHWnd(), "注册失败！", "警告", MB_OK);
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
                /*printf("注册成功！\n");*/
                MessageBox(GetHWnd(), "注册成功！", "", MB_OK);
                fclose(fp);
                return 1;
            }
            else {
                MessageBox(GetHWnd(), "该账户已注册", "", MB_OK);
                fclose(fp);
                return 0;
            }
        }
    }
}//教师注册
int LoginTea() {									 //教师登录
    char account[16], password[16];       	    //账号，密码
    char che_acc[16] = { 0 }, che_pas[16] = { 0 };       //检验账号，检验密码
    FILE* fp;
    int turn = 0;                                 //用于检验账号密码是否匹配
    /*printf("请输入您的工号：");*/
    /*scanf("%s", account);*/
    InputBox(account, 17, _T("请输入您的工号"), _T(""), _T(""), 0, 0, true);
    /*printf("请输入密码：");
    scanf("%s", password);*/
    InputBox(password, 17, _T("请输入密码"), _T(""), _T(""), 0, 0, true);
    if ((fp = fopen("accountTea.txt", "r")) == NULL) {
        /*printf("登录失败！\n");*/
        /*MessageBox(GetHWnd(), "这是一个弹窗显示的消息", "消息标题", MB_OK);*/
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
            MessageBox(GetHWnd(), "已进入教师界面", "", MB_OK);
            fclose(fp);
            return 1;
        }
        else {
            fclose(fp);
            return 0;
        }
    }
}//教师登录
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


}//学生注册
void change()
{
    loadimage(&img, "./picture/back.png", 1600, 800);
    putimage(0, 0, &img);
    struct student temp;
    struct Node* result;
    char check[20];
    result = searchDataBYnum_Account(list, Account);
    /*printf("请输入新密码");
    scanf("%s", temp.password, 20);*/
    InputBox(temp.password, 20, _T("请输入新密码"), _T(""), _T(""), 0, 0, true);
    /*  getchar();*/
     /* printf("请再次输入新密码");
      scanf("%s", check, 20);*/
    InputBox(check, 20, _T("请再次输入新密码"), _T(""), _T(""), 0, 0, true);
    int key = strcmp(temp.password, check);
    if (!key)
    {
        strcpy(result->data.password, temp.password);
        saveToFilea_account(list, "accountStu.txt");
        MessageBox(GetHWnd(), "密码修改成功，请重新登陆", "", MB_OK);
        exit(0);
    }
    else
    {
        MessageBox(GetHWnd(), "两次密码不一致", "警告", MB_OK);
    }

}
int LoginStu() {                                  //学生登录
    char account[20], password[20];       	    //账号，密码
    char che_acc[20] = { 0 }, che_pas[20] = { 0 };       //检验账号，检验密码
    FILE* fp;
    int turn = 0;                                 //用于检验账号密码是否匹配
    /* printf("请输入您的学号：");
     scanf("%s", account);*/
    InputBox(account, 16, _T("请输入您的学号"), _T(""), _T(""), 0, 0, true);
    /*printf("请输入密码：");
    scanf("%s", password);*/
    InputBox(password, 20, _T("请输入密码"), _T(""), _T(""), 0, 0, true);
    if ((fp = fopen("accountStu.txt", "r")) == NULL) {
        MessageBox(GetHWnd(), "登录失败", "警告", MB_OK);
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
            MessageBox(GetHWnd(), "登陆成功", " ", MB_OK);
            fclose(fp);
            return 1;
        }
        else {

            fclose(fp);
            return 0;
        }
    }
}//学生登录
void Loginmenu()
{
    int choice;
    /* printf("欢迎使用学生成绩管理系统");
     printf("请选择您的登录身份：\n");
     printf("1.教师\n");
     printf("2.学生\n");
     printf("0.退出\n");*/
     /*scanf("%d", &choice);*/
    LPBUTTON Button21 = createButton(650, 150, 300, 100, "教师");
    LPBUTTON Button22 = createButton(650, 350, 300, 100, "学生");
    LPBUTTON Button23 = createButton(650, 550, 300, 100, "退出");
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
                    MessageBox(GetHWnd(), "账号或密码错误，请重试", "", MB_OK);
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
                    MessageBox(GetHWnd(), "账号或密码错误，请重试", "", MB_OK);
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
            printf("输入错误！请重新输入...!\n");
        }
    }

}