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
const COLORREF bkcolor = RGB(187, 173, 160);//����ɫ
const COLORREF numcolor = RGB(119, 110, 101);//����ɫ
const COLORREF colora = RGB(180, 110, 110);//���'A'��ɫ
const COLORREF colorb = RGB(110, 180, 110);//���'B'��ɫ
const COLORREF blockcolor = RGB(207, 193, 180);//�������ɫ

class Button//��ť��
{
private:
	int x, y;//��ť���Ͻ�����
	int width, height;//��ť���
	float scale;//��ť���ű���,����ʵ�������ͣЧ��
	bool hover;//����Ƿ���ͣ�ڰ�ť��
	string text;//��ť����
	function<void()> onclick;//��ť����¼�
public:
	Button(int _x, int _y, int _width, int _height, float _scale, bool _hover, string _text, function<void()> _onclick);//���캯��
	void checkhover(int mousex, int mousey);//�������Ƿ���ͣ�ڰ�ť��)
	bool checkclick(int mousex, int mousey);//�������Ƿ����˰�ť
	void draw();//���ư�ť
};

class guipart
{
private:
	string title;
	string rule1;
	string rule2;
	string rule3;
	int exittimes;//��¼�˳������������ظ��˳�
	//vector<Button*>buttons;
public:
	bool Exit;//�Ƿ��˳�
	void buttonsinit();
	void menuinit();
	void gameinit();
	//void addbutton(int index, Button* button);//��Ӱ�ť��index��Ӧ��ҳ����
	void setcurrentindex(int index);//���õ�ǰҳ��
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
	int history[101][6];//��ʷ��¼��ÿһ����������λ���Լ�AB����
public:
	void gamerun();
	void finishwin(int steps);
	void finishlose();
};