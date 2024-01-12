#pragma once
#include <iostream>
#include <functional>
#include <conio.h>
#include <easyx.h>
#include <string>
#include <vector>
#include <random>
using namespace std;
#define GRID_WIDTH 80
#define INTERVAL 15
const COLORREF bkcolor = RGB(187, 173, 160);//背景色
const COLORREF numcolor = RGB(119, 110, 101);//数字色
const COLORREF colora = RGB(180, 110, 110);//结果'A'颜色
const COLORREF colorb = RGB(110, 180, 110);//结果'B'颜色
const COLORREF blockcolor = RGB(207, 193, 180);//方块填充色

class Button//按钮类
{
private:
	int x, y;//按钮左上角坐标
	int width, height;//按钮宽高
	float scale;//按钮缩放比例,用于实现鼠标悬停效果
	bool hover;//鼠标是否悬停在按钮上
	string text;//按钮文字
	function<void()> onclick;//按钮点击事件
public:
	Button(int _x, int _y, int _width, int _height, float _scale, bool _hover, string _text, function<void()> _onclick);//构造函数
	void checkhover(int mousex, int mousey);//检查鼠标是否悬停在按钮上)
	bool checkclick(int mousex, int mousey);//检查鼠标是否点击了按钮
	void draw();//绘制按钮
};

class guipart
{
private:
	string title;
	string rule1;
	string rule2;
	string rule3;
	int exittimes;//记录退出次数，避免重复退出
	//vector<Button*>buttons;
public:
	bool Exit;//是否退出
	void buttonsinit();
	void menuinit();
	void gameinit();
	//void addbutton(int index, Button* button);//添加按钮到index对应的页面中
	void setcurrentindex(int index);//设置当前页面
	void mouseclick(int mousex, int mousey);
	void mousemove(int mousex, int mousey);
	//void dealwithmouse
	guipart();
	~guipart();
};

class gamepart
{
private:
	int num[5];
	int history[101][6];//历史记录，每一步的输入四位数以及AB个数
public:
	void gamerun();
	void finishwin(int steps);
	void finishlose();
};