#include <iostream>
#include "game.h"

using namespace std;

HWND hmenu, hnd;

extern vector<vector<Button*>>buttons;
extern int currentindex;
extern guipart gui;
extern gamepart game;


guipart::guipart()//���캯��
{
	Exit = false;//�Ƿ��˳�
	exittimes = 0;//��¼�˳������������ظ��˳�
}

void guipart::buttonsinit() {
	buttons.resize(3);//�ܹ�3�������а�ť����8����ť
	//�������˵�������ť
	buttons[0].push_back(new Button(75, 140, 120, 60, 1.0, false, "��ʼ", [&]() {setcurrentindex(1); }));
	buttons[0].push_back(new Button(255, 140, 120, 60, 1.0, false, "�˳�", [&]() {setcurrentindex(0); }));
	buttons[1].push_back(new Button(140, 160, 120, 60, 1.0, false, "����Ϸ", [&]() {setcurrentindex(1); }));
	buttons[1].push_back(new Button(140, 240, 120, 60, 1.0, false, "�������˵�", [&]() {setcurrentindex(0); }));
	buttons[1].push_back(new Button(140, 320, 120, 60, 1.0, false, "�˳�", [&]() {setcurrentindex(0); }));
	buttons[2].push_back(new Button(140, 160, 120, 60, 1.0, false, "����Ϸ", [&]() {setcurrentindex(1); }));
	buttons[2].push_back(new Button(140, 240, 120, 60, 1.0, false, "�������˵�", [&]() {setcurrentindex(0); }));
	buttons[2].push_back(new Button(140, 320, 120, 60, 1.0, false, "�˳�", [&]() {setcurrentindex(0); }));
}

void guipart::menuinit()
{
	hmenu = initgraph(450, 300);
	setbkcolor(bkcolor);
	cleardevice();
	SetWindowText(GetHWnd(), "1A2B");
	//Sleep(2000);
	settextcolor(RGB(10, 10, 10));
	settextstyle(40, 0, ("����"));
	outtextxy(140, 30, "1");
	settextcolor(RGB(180,60,100));
	outtextxy(185, 30, "A");
	settextcolor(RGB(30, 30, 30));
	outtextxy(230, 30, "2");
	settextcolor(RGB(60,180,100));
	outtextxy(275, 30, "B");
	currentindex = 0;
	for (Button* button : buttons[currentindex]) button->draw();//�������˵���ť
	ExMessage msg;
	while (1) {
		if (peekmessage(&msg)) {
			int mousex = msg.x;
			int mousey = msg.y;//��ȡ���λ��
			switch (msg.message) {
			case WM_LBUTTONDOWN:
				mouseclick(mousex, mousey);
				break;
			case WM_MOUSEMOVE: {
				mousemove(mousex, mousey);
				for (Button* button : buttons[currentindex]) button->draw();
				break;
			}
			}
		}
		if (Exit && exittimes<1) {//�˳���Ϸ,��֮ǰû���˳���
			exittimes++;//�˳�������һ,�����ظ��˳�
			initgraph(450, 300);//�˳���Ϸ����
			setbkcolor(bkcolor);
			cleardevice();
			settextcolor(RGB(70, 70, 50));
			settextstyle(40, 0, ("΢���ź�"));
			outtextxy(160, 100, "��Ϸ����");
			outtextxy(80, 160, "��ӭ�´μ������飡");
			Sleep(1500);
			closegraph();
			return;
		}
		else if (exittimes >= 1) {
			return;
		}
	}
}

/*void guipart::addbutton(int index, Button* button)
{
	if(index>=0&&index<=buttons.size()) buttons[index].push_back(button);
}*/

void guipart::setcurrentindex(int index)
{
	if (index >= 0 && index <= buttons.size()) currentindex = index;
}

void guipart::mouseclick(int mousex, int mousey)
{
	if (currentindex >= 0 && currentindex < buttons.size()) {
		for (int i = 0; i < buttons[currentindex].size(); i++) {
			int oldindex = currentindex;
			bool flag = buttons[currentindex][i]->checkclick(mousex, mousey);
			if (flag) {
				if (oldindex == 0) {
					if (i == 1) Exit = true;//�˳�
					else {
						gameinit();//������Ϸ
					}
				}
				else if (oldindex == 1) {
					if(i==0) gameinit();//���¿�ʼ
					else if (i == 1) {
						closegraph();
						menuinit();//�������˵�
					}
					else {//�˳�
						closegraph();
						Exit = true;
					}
				}
				else if (oldindex == 2) {
					if (i == 0) gameinit();
					else if (i == 1) {
						closegraph();
						menuinit();//�������˵�
					}
					else {//�˳�
						closegraph();
						Exit = true;
					}
				}
			}
		}
	}
}

void guipart::mousemove(int mousex, int mousey)
{
	if (currentindex >= 0 && currentindex < buttons.size()) {
		for (int i = 0; i < buttons[currentindex].size(); i++) {
			buttons[currentindex][i]->checkhover(mousex, mousey);
		}
	}
}

void guipart::gameinit()
{
	closegraph();//�ر����˵�����
	hnd = initgraph(GRID_WIDTH * 10 + INTERVAL * 11, GRID_WIDTH * 5 + INTERVAL * 6 + 210, NULL);//��ʼ������
	setbkcolor(bkcolor);//���ñ�����ɫ
	cleardevice();
	HWND hnnd = GetHWnd();
	SetWindowText(hnnd, "1A2B");//���ô��ڱ���
	title = "1A2B";
	rule1 = "�����������һ�������ظ����ֵ���λ��(��λ��Ϊ0)����Ҳ��������������������ֲ������";
	rule2 = "�������÷�������������Ĳ�������������Խ�ٷ���Խ�ߡ�����Ϸ�������99��";
	rule3 = "A��ʾ���ֺ�λ�þ���ȷ��B��ʾ������ȷ��λ�ò���ȷ";
	settextcolor(RGB(10, 10, 10));
	settextstyle(40, 0, ("����"));
	//outtextxy(5, 5, title.c_str());
	outtextxy(395, 5, title[0]);
	settextcolor(RGB(180,60,100));
	outtextxy(425, 5, title[1]);
	settextcolor(RGB(30, 30, 30));
	outtextxy(455, 5, title[2]);
	settextcolor(RGB(60,180,110));
	outtextxy(485, 5, title[3]);
	settextcolor(RGB(30, 30, 30));
	settextstyle(20, 0, ("����"));
	outtextxy(15, 50, "����:");
	outtextxy(50, 70, rule1.c_str());
	outtextxy(50, 90, rule2.c_str());
	outtextxy(50, 110, rule3.c_str());
	settextcolor(RGB(200, 120, 180));
	settextstyle(25, 0, ("����"));
	outtextxy(15, 140, "��q��ESC�˳���Ϸ���������˵�");
	outtextxy(15, 175, "ͨ��\"����\"����\"WS\"�����Բ鿴��ʷ��¼");
	setfillcolor(blockcolor);
	int iniy = 130 + 10 + 60 + 10 + INTERVAL;
	int inix = GRID_WIDTH * 2 + INTERVAL * 3;
	for (int i = 0; i < 4; ++i) {
		solidrectangle(inix + i * (GRID_WIDTH + INTERVAL), iniy, inix + i * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, iniy + GRID_WIDTH);
	}
	settextcolor(numcolor);
	settextstyle(50, 0, "΢���ź�");
	outtextxy(52, iniy + 15, "1");
	outtextxy(140, iniy + 15, ":");
	game.gamerun();
}

guipart::~guipart()
{
	/*int len = buttons.size();
	for (int i = 0; i < len; ++i) {
		int size = buttons[i].size();
		for (int j = 0; j < size; ++j) {
			Button* cur = buttons[i][j];
			delete cur;
		}
	}*/
}

void gamepart::gamerun()
{
	memset(game.history, 0, sizeof(game.history));//��ʼ��
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> dis(0.0, 1.0);
	int a = 1, b = 1, c = 1, d = 1, x;
	while (!(a != b && a != c && a != d && b != c && b != d && c != d)) {
		double value = dis(mt);
		x = (int)(value * 9000 + 1000);
		a = x / 1000;
		x %= 1000;
		b = x / 100;
		x %= 100;
		c = x / 10;
		x %= 10;
		d = x;
	}
	x = a * 1000 + b * 100 + c * 10 + d;
	int t = x, s = x, i = 4;
	while (t != 0) {
		num[i] = t % 10;
		t /= 10;
		i--;
	}
	int step = 1;
	int line = 0, pos = 0;//line��ʾ������ǵڼ�(��һ)�У�pos��ʾ��������ֵ�λ��
	int topline = 1;//topline��ʾ��ǰ��ʾ��5���У�������һ���ǵڼ���(��)
	bool win = false;
	//ExMessage msg;
	setbkmode(TRANSPARENT);
	int number[5];
	int lastline[5];
	//��enter֮ǰ�����һ�����ֲ��ᱣ����history�У�Ϊ�˷�ֹ��enter֮ǰ���ϼ��鿴��ʷ��¼ʱ�����һ�����ֱ����ǣ�
	//��Ҫ�������һ�����֣�������lastline���鱣��
	while (1) {
		line = (step <= 5) ? (step - 1) : 4;
		//cout << "pos:" << pos << ' ' << "line:" << line << '\n';
		/*if (peekmessage(&msg)) {
			if (WM_KEYDOWN) {
				if (pos < 3) {
					if (checksancode(pos, msg.scancode)) {
						outtextxy(40, 500, "here");
						outtextxy(205 + 15 + pos * (GRID_WIDTH + INTERVAL), 240 + line, keyboard[msg.scancode].c_str());
					}
				}
			}
		}*/
		/*string ss = to_string(pos);
		outtextxy(50, 400, ss.c_str());
		string sss = to_string(line);
		outtextxy(50, 500, sss.c_str());*/
		char key = _getch();
		//outtextxy(50, 600, key);
		if (key == 'q' || (int)key == 27) {//q��ESC�˳���Ϸ
			closegraph();
			//ShowWindow(hmenu, SW_SHOW);
			gui.menuinit();//�������˵�
			return;
		}
		else if (key >= '0' && key <= '9') {//��������
			bool atlastline;//�ж����һ���Ƿ�����ڻ�����
			if (step <= 5) atlastline = true;
			else {
				atlastline = (topline + 4 == step) ? true : false;
			}
			if (atlastline) {//ֻ�е����һ�г����ڻ�����ʱ��������������
				if (pos == 0) {//��һ��������Ϊ0
					if (key > '0') {
						settextcolor(numcolor);
						settextstyle(50, 0, ("΢���ź�"));
						outtextxy(235 + pos * (GRID_WIDTH + INTERVAL), 240 + line * (GRID_WIDTH + INTERVAL), key);
						number[pos] = key - '0';
						pos++;
					}
				}
				else if (pos > 0 && pos < 4) {
					settextcolor(numcolor);
					settextstyle(50, 0, ("΢���ź�"));
					outtextxy(235 + pos * (GRID_WIDTH + INTERVAL), 240 + line * (GRID_WIDTH + INTERVAL), key);
					number[pos] = key - '0';
					pos++;
				}
			}
		}
		else if ((int)key == 8) {//�˸�
			bool atlastline;//�ж����һ���Ƿ�����ڻ�����
			if (step <= 5) atlastline = true;
			else {
				atlastline = (topline + 4 == step) ? true : false;
			}
			if (atlastline) {//ֻ�е����һ�г����ڻ�����ʱ�������˸�}
				if (pos > 0 && pos <= 4) {
					pos--;
					setfillcolor(blockcolor);
					solidrectangle(205 + pos * (GRID_WIDTH + INTERVAL), 225 + line * (GRID_WIDTH + INTERVAL), 205 + pos * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, 225 + line * (GRID_WIDTH + INTERVAL) + GRID_WIDTH);
					number[pos] = 0;
				}
			}
		}
		else if (((int)key == 10 || (int)key == 13) && pos == 4) { //enter�������������(��λ��)
			int booka[5], bookb[10];
			memset(booka, 0, sizeof(booka));
			memset(bookb, 0, sizeof(bookb));
			int as = 0, bs = 0;//A��B������
			for (int j = 1; j <= 4; j++) {
				if (number[j - 1] == num[j]) {
					as++;
					booka[j] = 1;
				}
			}
			for (int j = 1; j <= 4; j++) {
				if (booka[j] == 1) continue;
				else {
					bookb[num[j]] = 1;
				}
			}
			for (int j = 1; j <= 4; j++) {
				if (booka[j] == 1) continue;
				else {
					if (bookb[number[j - 1]] == 1) {
						bs++;
					}
				}
			}
			//��¼��
			for (int i = 0; i < 4; ++i) {
				history[step][i] = number[i];
			}
			history[step][4] = as;
			history[step][5] = bs;
			//��ʾ��
			//�˴�Ҫ�ж��Ƿ��ǵ�����ײ��ˣ����ǣ���Ҫȫ������һ��(�����ܹ��������5��)
			if (step >= 5) {//������ײ��ˣ�Ҫȫ������һ��
				topline++;//������ʾ�ĵ�һ�ж�Ӧ���к�
				//����߲���ˢ��,��Ϳ��ԭ����
				int stepx = 20, stepy = 130 + 80 + INTERVAL + 15;
				setfillcolor(bkcolor);
				solidrectangle(stepx, stepy - 15, (GRID_WIDTH + INTERVAL) * 2, stepy - 15 + (GRID_WIDTH + INTERVAL) * 5);
				//�����²���
				settextcolor(numcolor);
				settextstyle(50, 0, "΢���ź�");
				for (int i = topline; i <= step; ++i) {
					outtextxy(52, stepy + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(i).c_str());
					outtextxy(140, stepy + (i - topline) * (GRID_WIDTH + INTERVAL), ":");
				}
				step++;
				outtextxy(52, stepy + 4 * (GRID_WIDTH + INTERVAL), to_string(step).c_str());
				outtextxy(140, stepy + 4 * (GRID_WIDTH + INTERVAL), ":");
				//ǰ���з��鼰���ָ���
				setfillcolor(blockcolor);
				int inix = 2 * GRID_WIDTH + 3 * INTERVAL;
				int iniy = stepy - 15;
				for (int i = topline; i < step; ++i) {
					for (int j = 0; j < 4; ++j) {
						//��������Լ����ָ���
						solidrectangle(inix + j * (GRID_WIDTH + INTERVAL), iniy + (i - topline) * (GRID_WIDTH + INTERVAL), inix + j * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, iniy + (i - topline) * (GRID_WIDTH + INTERVAL) + GRID_WIDTH);
						outtextxy(235 + j * (GRID_WIDTH + INTERVAL), 240 + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(history[i][j]).c_str());
					}
				}
				//���һ�����4���µķ���
				for (int j = 0; j < 4; ++j) {
					solidrectangle(inix + j * (GRID_WIDTH + INTERVAL), iniy + 4 * (GRID_WIDTH + INTERVAL), inix + j * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, iniy + 4 * (GRID_WIDTH + INTERVAL) + GRID_WIDTH);
				}
				//���½��
				setfillcolor(bkcolor);
				int resx = inix + 4 * (GRID_WIDTH + INTERVAL);
				solidrectangle(resx, iniy, resx + 4 * (GRID_WIDTH + INTERVAL), iniy + 5 * (GRID_WIDTH + INTERVAL));
				//A
				settextcolor(colora);
				//settextstyle(50, 0, ("΢���ź�"));
				for (int j = 0; j < 4; ++j) {
					outtextxy(resx + (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "A");
				}
				//B
				settextcolor(colorb);
				for (int j = 0; j < 4; ++j) {
					outtextxy(resx + 3 * (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "B");
				}
				//���
				settextcolor(numcolor);
				for (int j = 0; j < 4; ++j) {
					outtextxy(resx + 30, stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][4]).c_str());
					outtextxy(resx + 30 + 2 * (GRID_WIDTH + INTERVAL), stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][5]).c_str());
				}
			}
			else {//����С��5����ֻ��Ҫ���ϴ𰸲������һ���ĸ������
				//������
				settextcolor(numcolor);
				settextstyle(50, 0, "΢���ź�");
				int resx = 6 * GRID_WIDTH + 7 * INTERVAL;
				settextcolor(colora);
				outtextxy(resx + 30 + GRID_WIDTH + INTERVAL, 240 + line * (GRID_WIDTH + INTERVAL), "A");
				settextcolor(colorb);
				outtextxy(resx + 30 + (GRID_WIDTH + INTERVAL) * 3, 240 + line * (GRID_WIDTH + INTERVAL), "B");
				settextcolor(numcolor);
				outtextxy(resx + 30, 240 + line * (GRID_WIDTH + INTERVAL), to_string(history[step][4]).c_str());
				outtextxy(resx+30+2*(GRID_WIDTH+INTERVAL), 240 + line * (GRID_WIDTH + INTERVAL), to_string(history[step][5]).c_str());
				//�����һ���ĸ������
				setfillcolor(blockcolor);
				int inix = 2 * GRID_WIDTH + 3 * INTERVAL;
				int iniy = 130 + 80 + INTERVAL;
				for (int i = 0; i < 4; ++i) {
					solidrectangle(inix + i * (GRID_WIDTH + INTERVAL), iniy + step * (GRID_WIDTH + INTERVAL), inix + i * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, iniy + step * (GRID_WIDTH + INTERVAL) + GRID_WIDTH);
				}
				//���²���
				outtextxy(52, iniy + 15 + step * (GRID_WIDTH + INTERVAL), to_string(step + 1).c_str());
				outtextxy(140, iniy + 15 + step * (GRID_WIDTH + INTERVAL), ":");
				step++;
			}
			pos = 0;//�ǵù�λ
			if (as == 4) {
				win = true;
			}
		}
		else if (key == 'w' || key == 'W' || key == 72) {//���յ��ϼ�
			if (topline > 1) {//ֻ�е���ʾ�������в��ǵ�һ�вſ�������
				if (topline + 4 == step) {
					//�����ʾ�������һ����Ŀǰ���һ�У���Ҫ�����һ�е����ֱ��浽lastline������
					for (int i = 0; i < 4; i++) lastline[i] = number[i];
				}
				topline--;
				//����߲���ˢ��,��Ϳ��ԭ����
				int stepx = 20, stepy = 130 + 80 + INTERVAL + 15;
				setfillcolor(bkcolor);
				solidrectangle(stepx, stepy - 15, (GRID_WIDTH + INTERVAL) * 2, stepy - 15 + (GRID_WIDTH + INTERVAL) * 5);
				//�����²���
				settextcolor(numcolor);
				settextstyle(50, 0, "΢���ź�");
				for (int i = topline; i < topline + 5; ++i) {
					outtextxy(52, stepy + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(i).c_str());
					outtextxy(140, stepy + (i - topline) * (GRID_WIDTH + INTERVAL), ":");
				}
				//���鼰���ָ���
				setfillcolor(blockcolor);
				int inix = 2 * GRID_WIDTH + 3 * INTERVAL;
				int iniy = stepy - 15;
				for (int i = topline; i < topline + 5; ++i) {
					for (int j = 0; j < 4; ++j) {
						//��������Լ����ָ���
						solidrectangle(inix + j * (GRID_WIDTH + INTERVAL), iniy + (i - topline) * (GRID_WIDTH + INTERVAL), inix + j * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, iniy + (i - topline) * (GRID_WIDTH + INTERVAL) + GRID_WIDTH);
						outtextxy(235 + j * (GRID_WIDTH + INTERVAL), 240 + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(history[i][j]).c_str());
					}
				}
				//�������
				setfillcolor(bkcolor);
				int resx = inix + 4 * (GRID_WIDTH + INTERVAL);
				solidrectangle(resx, iniy, resx + 4 * (GRID_WIDTH + INTERVAL), iniy + 5 * (GRID_WIDTH + INTERVAL));
				//A
				settextcolor(colora);
				//settextstyle(50, 0, ("΢���ź�"));
				for (int j = 0; j < 5; ++j) {
					outtextxy(resx + (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "A");
				}
				//B
				settextcolor(colorb);
				for (int j = 0; j < 5; ++j) {
					outtextxy(resx + 3 * (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "B");
				}
				//���
				settextcolor(numcolor);
				for (int j = 0; j < 5; ++j) {
					outtextxy(resx + 30, stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][4]).c_str());
					outtextxy(resx + 30 + 2 * (GRID_WIDTH + INTERVAL), stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][5]).c_str());
				}
			}
		}
		else if (key == 's' || key == 'S' || key == 80) {//���յ��¼�
			if (topline + 4 < step) {//ֻ�е���ʾ�������в������һ�вſ�������
				topline++;
				//����߲���ˢ��,��Ϳ��ԭ����
				int stepx = 20, stepy = 130 + 80 + INTERVAL + 15;
				setfillcolor(bkcolor);
				solidrectangle(stepx, stepy - 15, (GRID_WIDTH + INTERVAL) * 2, stepy - 15 + (GRID_WIDTH + INTERVAL) * 5);
				//�����²���
				settextcolor(numcolor);
				settextstyle(50, 0, "΢���ź�");
				for (int i = topline; i <= topline + 4; ++i) {
					outtextxy(52, stepy + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(i).c_str());
					outtextxy(140, stepy + (i - topline) * (GRID_WIDTH + INTERVAL), ":");
				}
				//���鼰���ָ���
				setfillcolor(blockcolor);
				int inix = 2 * GRID_WIDTH + 3 * INTERVAL;
				int iniy = stepy - 15;
				for (int i = topline; i <= topline + 4; ++i) {
					for (int j = 0; j < 4; ++j) {
						//�������
						solidrectangle(inix + j * (GRID_WIDTH + INTERVAL), iniy + (i - topline) * (GRID_WIDTH + INTERVAL), inix + j * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, iniy + (i - topline) * (GRID_WIDTH + INTERVAL) + GRID_WIDTH);
					}
				}
				//���ָ���
				if (topline + 4 == step) {//�����ʾ��������һ����Ŀǰ���һ�У���Ҫ����lastline���������ʾ�����һ��
					//ǰ�������ָ���
					for (int i = topline; i < topline + 4; ++i) {
						for (int j = 0; j < 4; ++j) {
							outtextxy(235 + j * (GRID_WIDTH + INTERVAL), 240 + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(history[i][j]).c_str());
						}
					}
					//���һ�����ָ���
					for (int j = 0; j < pos; ++j) {
						outtextxy(235 + j * (GRID_WIDTH + INTERVAL), 240 + 4 * (GRID_WIDTH + INTERVAL), to_string(lastline[j]).c_str());
					}
				}
				else {
					//��������ȫ��һ�����
					for (int i = topline; i <= topline + 4; ++i) {
						for (int j = 0; j < 4; ++j) {
							outtextxy(235 + j * (GRID_WIDTH + INTERVAL), 240 + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(history[i][j]).c_str());
						}
					}
				}
				//�������
				setfillcolor(bkcolor);
				int resx = inix + 4 * (GRID_WIDTH + INTERVAL);
				solidrectangle(resx, iniy, resx + 4 * (GRID_WIDTH + INTERVAL), iniy + 5 * (GRID_WIDTH + INTERVAL));
				if(topline+4==step) {//�����ʾ��������һ����Ŀǰ���һ�У���ֻ�ø���ǰ���еĽ��
					//A
					settextcolor(colora);
					//settextstyle(50, 0, ("΢���ź�"));
					for (int j = 0; j < 4; ++j) {
						outtextxy(resx + (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "A");
					}
					//B
					settextcolor(colorb);
					for (int j = 0; j < 4; ++j) {
						outtextxy(resx + 3 * (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "B");
					}
					//���
					settextcolor(numcolor);
					for (int j = 0; j < 4; ++j) {
						outtextxy(resx + 30, stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][4]).c_str());
						outtextxy(resx + 30 + 2 * (GRID_WIDTH + INTERVAL), stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][5]).c_str());
					}
				}
				else {//����ȫ�����еĽ��
					//A
					settextcolor(colora);
					//settextstyle(50, 0, ("΢���ź�"));
					for (int j = 0; j < 5; ++j) {
						outtextxy(resx + (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "A");
					}
					//B
					settextcolor(colorb);
					for (int j = 0; j < 5; ++j) {
						outtextxy(resx + 3 * (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "B");
					}
					//���
					settextcolor(numcolor);
					for (int j = 0; j < 5; ++j) {
						outtextxy(resx + 30, stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][4]).c_str());
						outtextxy(resx + 30 + 2 * (GRID_WIDTH + INTERVAL), stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][5]).c_str());
					}
				}
			}
		}
		//�����ж�
		if (win) {//��ת��ʤ������
			Sleep(500);
			closegraph();
			finishwin(step - 1);
			break;
		}
		if (step == 100) {//��ת��ʧ�ܻ���
			Sleep(500);
			closegraph();
			finishlose();
			break;
		}
	}
}


void gamepart::finishwin(int steps)
{
	initgraph(400, 450, NULL);
	setbkcolor(bkcolor);
	SetWindowText(GetHWnd(), "1A2B");
	cleardevice();
	settextcolor(RGB(120, 100, 140));
	settextstyle(40, 0, "����");
	string s1 = "��ϲ�㣬��Ӯ�ˣ�";
	string s2 = "����";
	string stepnum = to_string(steps);
	//s2 += stepnum;
	int score = 0;
	if (steps <= 5) score = 100;//5������Ϊ100��
	else if (steps <= 10) {
		score = 100 - (steps - 5) * 4;//6-10��Ϊ96-80��
	}
	else if (steps <= 20) {
		score = 80 - (steps - 10) * 3;//11-20��Ϊ77-50��
	}
	else if (steps <= 30) {
		score = 50 - (steps - 20) * 2;//21-30��Ϊ48-30��
	}
	else if (steps <= 40) {
		score = 30 - (steps - 30) * 1;//31-40��Ϊ29-20��
	}
	else score = 10;//40������Ϊ10��
	string s3 = "�÷�";
	string scorenum = to_string(score);
	//s3 += scorenum;
	int x1 = (450 - textwidth(s1.c_str())) / 2;
	//int x2 = (450 - textwidth(s2.c_str())) / 2;
	outtextxy(x1, 20, s1.c_str());
	//outtextxy(x2, 80, s2.c_str());
	outtextxy(15, 80, s2.c_str());
	outtextxy(100, 80, ":");
	settextcolor(RGB(100, 140, 120));
	outtextxy(130, 80, stepnum.c_str());
	settextcolor(RGB(120, 100, 140));
	outtextxy(210, 80, s3.c_str());
	outtextxy(295, 80, ":");
	settextcolor(RGB(100, 140, 120));
	outtextxy(325, 80, scorenum.c_str());
	currentindex = 1;
	for (Button* button : buttons[currentindex]) button->draw();//����ʤ�����水ť
	ExMessage msg;
	while (1) {
		if (peekmessage(&msg)) {
			int mousex = msg.x;
			int mousey = msg.y;//��ȡ���λ��
			switch (msg.message) {
			case WM_LBUTTONDOWN:
				gui.mouseclick(mousex, mousey);
				if (gui.Exit) return;
				break;
			case WM_MOUSEMOVE: {
				gui.mousemove(mousex, mousey);
				for (Button* button : buttons[currentindex]) button->draw();
				break;
			}
			}
		}
	}
}

void gamepart::finishlose()
{
	initgraph(400, 450, NULL);
	setbkcolor(bkcolor);
	SetWindowText(GetHWnd(), "1A2B");
	cleardevice();
	settextcolor(RGB(120, 100, 140));
	settextstyle(40, 0, "����");
	string s1 = "���ź���������!";
	string s2 = "99����δ�ܲ³���";
	int x1 = (450 - textwidth(s1.c_str())) / 2;
	int x2 = (450 - textwidth(s2.c_str())) / 2;
	outtextxy(x1, 20, s1.c_str());
	outtextxy(x2, 80, s2.c_str());
	currentindex = 2;
	for (Button* button : buttons[currentindex]) button->draw();//����ʧ�ܽ��水ť
	ExMessage msg;
	while (1) {
		if (peekmessage(&msg)) {
			int mousex = msg.x;
			int mousey = msg.y;//��ȡ���λ��
			switch (msg.message) {
			case WM_LBUTTONDOWN:
				gui.mouseclick(mousex, mousey);
				if (gui.Exit) return;
				break;
			case WM_MOUSEMOVE: {
				gui.mousemove(mousex, mousey);
				for (Button* button : buttons[currentindex]) button->draw();
				break;
			}
			}
		}
	}
}