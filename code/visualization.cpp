#define _CRT_SECURE_NO_WARNINGS
#include<graphics.h>
#include<easyx.h>
#include<stdio.h>
#include<assert.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include "structure.h"
#include "visualization.h"
extern char Account[20];
extern IMAGE test[2];
extern ExMessage msg;
extern IMAGE img;
extern int ButtonResult;
LPBUTTON createButton(int x, int y, int w, int h, const char* str)
{
    LPBUTTON button = (LPBUTTON)malloc(sizeof(BUTTON));
    assert(button);
    button->x = x;
    button->y = y;
    button->w = w;
    button->h = h;
    button->color = RGB(62, 183, 204);
    int length = strlen(str) + 1;
    button->text = (char*)malloc(sizeof(char) * length);
    assert(button->text);
    strcpy_s(button->text, length, str);
    return button;
}
void drawButton(LPBUTTON button)
{
    setfillcolor(button->color);
    fillrectangle(button->x, button->y, button->x + button->w, button->y + button->h);
    setbkmode(TRANSPARENT);
    settextstyle(20, 0, "ËÎÌå");
    //settextcolor(BLACK);
    int textw = textwidth(button->text);
    int texth = textheight(button->text);
    int xx = button->x + (button->w - textw) / 2;//ÎÄ×ÖÎ»ÖÃ
    int yy = button->y + (button->h - texth) / 2;
    outtextxy(xx, yy, button->text);
}
void DrawSTMenu() {

    cleardevice();
    setcolor(WHITE);
    loadimage(&img, "./picture/back.png", 1600, 800);
    putimage(0, 0, &img);
    LPBUTTON Button1 = createButton(0, 0, 533, 100, "ä¯ÀÀ");
    LPBUTTON Button2 = createButton(534, 0, 533, 100, "ÕËºÅÃÜÂëÐÞ¸Ä");
    LPBUTTON Button3 = createButton(1067, 0, 533, 100, "ÍË³ö");

    drawButton(Button1);
    drawButton(Button2);
    drawButton(Button3);

    do
    {
        peekmessage(&msg, EM_MOUSE);
        if (msg.x > 0 && msg.x < 533 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
        {
            ButtonResult = 1;
            Sleep(200);
            break;
        }
        else if (msg.x > 200 && msg.x < 1067 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
        {
            ButtonResult = 2;
            break;
        }
        else if (msg.x > 400 && msg.x < 1600 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
        {
            ButtonResult = 0;
            break;
        }

    } while (1);
    cleardevice();
}
void DrawMenu() {

    cleardevice();
    setcolor(WHITE);
    loadimage(&img, "./picture/back.png", 1600, 800);
    putimage(0, 0, &img);
    LPBUTTON Button1 = createButton(0, 0, 200, 100, "Â¼Èë");
    LPBUTTON Button2 = createButton(200, 0, 200, 100, "ä¯ÀÀ");
    LPBUTTON Button3 = createButton(400, 0, 200, 100, "ÅÅÐò");
    LPBUTTON Button4 = createButton(600, 0, 200, 100, "²éÕÒ");
    LPBUTTON Button5 = createButton(800, 0, 200, 100, "ÐÞ¸Ä");
    LPBUTTON Button6 = createButton(1000, 0, 200, 100, "É¾³ý");
    LPBUTTON Button7 = createButton(1200, 0, 200, 100, "ÕËºÅ¹ÜÀí");
    LPBUTTON Button0 = createButton(1400, 0, 200, 100, "ÍË³ö");
    //LPBUTTON Button6 = createButton(0, 550, 100, 50, "·µ»Ø");
    drawButton(Button1);
    drawButton(Button2);
    drawButton(Button3);
    drawButton(Button4);
    drawButton(Button5);
    drawButton(Button6);
    drawButton(Button7);
    drawButton(Button0);
    //drawButton(Button6);
    do
    {
        peekmessage(&msg, EM_MOUSE);
        if (msg.x > 0 && msg.x < 200 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
        {
            ButtonResult = 1;
            Sleep(200);
            break;
        }
        else if (msg.x > 200 && msg.x < 400 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
        {
            ButtonResult = 2;
            break;
        }
        else if (msg.x > 400 && msg.x < 600 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
        {
            ButtonResult = 3;
            break;
        }
        else if (msg.x > 600 && msg.x < 800 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
        {
            ButtonResult = 4;
            break;
        }
        else if (msg.x > 800 && msg.x < 1000 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
        {
            ButtonResult = 5;
            break;
        }
        else if (msg.x > 1000 && msg.x < 1200 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
        {
            ButtonResult = 6;
            break;
        }
        else if (msg.x > 1200 && msg.x < 1400 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
        {
            ButtonResult = 7;
            break;
        }
        else if (msg.x > 1400 && msg.x < 1600 && msg.y>0 && msg.y < 100 && msg.message == WM_LBUTTONDOWN)
        {
            ButtonResult = 0;
            break;
        }
    } while (1);
    //LPBUTTON ButtonArr[] = { Button1,Button2,Button3,Button4,Button5,Button6,Button7,Button0,/*Button6 */ };
    //const int ButtonCount = sizeof(ButtonArr) / sizeof(Button1);
    //bool Running = true;

    //while (Running)
    //{
    //    if (ButtonResult >= 0 && ButtonResult <= 7)
    //    {
    //        Running = false;
    //    }
    //    ExMessage msg;
    //    peekmessage(&msg, EM_MOUSE);


    //    if (msg.message == WM_LBUTTONDOWN && msg.x >= 0 && msg.x < 1600 && msg.y>0 && msg.y < 100)
    //    {
    //        HandleMouseClick(msg.x, msg.y, ButtonArr, ButtonCount);
    //    }
    //}
}
void DrawReturn()
{
    settextcolor(WHITE);
    LPBUTTON Button8 = createButton(0, 550, 50, 50, "·µ»Ø");
    drawButton(Button8);
}
void DrawPage()
{
    settextcolor(WHITE);
    LPBUTTON Button11 = createButton(600, 750, 50, 25, "ÉÏÒ»Ò³");
    LPBUTTON Button12 = createButton(850, 750, 50, 25, "ÏÂÒ»Ò³");
    drawButton(Button11);
    drawButton(Button12);
}
