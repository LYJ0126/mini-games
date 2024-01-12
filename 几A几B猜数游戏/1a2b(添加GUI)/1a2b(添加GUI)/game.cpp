#include <iostream>
#include "game.h"

using namespace std;

HWND hmenu, hnd;

extern vector<vector<Button*>>buttons;
extern int currentindex;
extern guipart gui;
extern gamepart game;


guipart::guipart()//构造函数
{
	Exit = false;//是否退出
	exittimes = 0;//记录退出次数，避免重复退出
}

void guipart::buttonsinit() {
	buttons.resize(3);//总共3个界面有按钮，共8个按钮
	//创建主菜单两个按钮
	buttons[0].push_back(new Button(75, 140, 120, 60, 1.0, false, "开始", [&]() {setcurrentindex(1); }));
	buttons[0].push_back(new Button(255, 140, 120, 60, 1.0, false, "退出", [&]() {setcurrentindex(0); }));
	buttons[1].push_back(new Button(140, 160, 120, 60, 1.0, false, "新游戏", [&]() {setcurrentindex(1); }));
	buttons[1].push_back(new Button(140, 240, 120, 60, 1.0, false, "返回主菜单", [&]() {setcurrentindex(0); }));
	buttons[1].push_back(new Button(140, 320, 120, 60, 1.0, false, "退出", [&]() {setcurrentindex(0); }));
	buttons[2].push_back(new Button(140, 160, 120, 60, 1.0, false, "新游戏", [&]() {setcurrentindex(1); }));
	buttons[2].push_back(new Button(140, 240, 120, 60, 1.0, false, "返回主菜单", [&]() {setcurrentindex(0); }));
	buttons[2].push_back(new Button(140, 320, 120, 60, 1.0, false, "退出", [&]() {setcurrentindex(0); }));
}

void guipart::menuinit()
{
	hmenu = initgraph(450, 300);
	setbkcolor(bkcolor);
	cleardevice();
	SetWindowText(GetHWnd(), "1A2B");
	//Sleep(2000);
	settextcolor(RGB(10, 10, 10));
	settextstyle(40, 0, ("楷体"));
	outtextxy(140, 30, "1");
	settextcolor(RGB(180,60,100));
	outtextxy(185, 30, "A");
	settextcolor(RGB(30, 30, 30));
	outtextxy(230, 30, "2");
	settextcolor(RGB(60,180,100));
	outtextxy(275, 30, "B");
	currentindex = 0;
	for (Button* button : buttons[currentindex]) button->draw();//绘制主菜单按钮
	ExMessage msg;
	while (1) {
		if (peekmessage(&msg)) {
			int mousex = msg.x;
			int mousey = msg.y;//获取鼠标位置
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
		if (Exit && exittimes<1) {//退出游戏,且之前没有退出过
			exittimes++;//退出次数加一,避免重复退出
			initgraph(450, 300);//退出游戏界面
			setbkcolor(bkcolor);
			cleardevice();
			settextcolor(RGB(70, 70, 50));
			settextstyle(40, 0, ("微软雅黑"));
			outtextxy(160, 100, "游戏结束");
			outtextxy(80, 160, "欢迎下次继续体验！");
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
					if (i == 1) Exit = true;//退出
					else {
						gameinit();//进入游戏
					}
				}
				else if (oldindex == 1) {
					if(i==0) gameinit();//重新开始
					else if (i == 1) {
						closegraph();
						menuinit();//返回主菜单
					}
					else {//退出
						closegraph();
						Exit = true;
					}
				}
				else if (oldindex == 2) {
					if (i == 0) gameinit();
					else if (i == 1) {
						closegraph();
						menuinit();//返回主菜单
					}
					else {//退出
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
	closegraph();//关闭主菜单窗口
	hnd = initgraph(GRID_WIDTH * 10 + INTERVAL * 11, GRID_WIDTH * 5 + INTERVAL * 6 + 210, NULL);//初始化窗口
	setbkcolor(bkcolor);//设置背景颜色
	cleardevice();
	HWND hnnd = GetHWnd();
	SetWindowText(hnnd, "1A2B");//设置窗口标题
	title = "1A2B";
	rule1 = "电脑随机生成一个不含重复数字的四位数(首位不为0)，玩家猜数，电脑则告诉玩家数字猜中情况";
	rule2 = "最终所得分数由玩家所消耗步数决定，步数越少分数越高。本游戏最多允许99步";
	rule3 = "A表示数字和位置均正确，B表示数字正确但位置不正确";
	settextcolor(RGB(10, 10, 10));
	settextstyle(40, 0, ("楷体"));
	//outtextxy(5, 5, title.c_str());
	outtextxy(395, 5, title[0]);
	settextcolor(RGB(180,60,100));
	outtextxy(425, 5, title[1]);
	settextcolor(RGB(30, 30, 30));
	outtextxy(455, 5, title[2]);
	settextcolor(RGB(60,180,110));
	outtextxy(485, 5, title[3]);
	settextcolor(RGB(30, 30, 30));
	settextstyle(20, 0, ("宋体"));
	outtextxy(15, 50, "规则:");
	outtextxy(50, 70, rule1.c_str());
	outtextxy(50, 90, rule2.c_str());
	outtextxy(50, 110, rule3.c_str());
	settextcolor(RGB(200, 120, 180));
	settextstyle(25, 0, ("宋体"));
	outtextxy(15, 140, "按q或ESC退出游戏，返回主菜单");
	outtextxy(15, 175, "通过\"上下\"键或\"WS\"键可以查看历史记录");
	setfillcolor(blockcolor);
	int iniy = 130 + 10 + 60 + 10 + INTERVAL;
	int inix = GRID_WIDTH * 2 + INTERVAL * 3;
	for (int i = 0; i < 4; ++i) {
		solidrectangle(inix + i * (GRID_WIDTH + INTERVAL), iniy, inix + i * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, iniy + GRID_WIDTH);
	}
	settextcolor(numcolor);
	settextstyle(50, 0, "微软雅黑");
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
	memset(game.history, 0, sizeof(game.history));//初始化
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
	int line = 0, pos = 0;//line表示输入的是第几(减一)行，pos表示输入的数字的位置
	int topline = 1;//topline表示当前显示的5行中，最上面一行是第几行(步)
	bool win = false;
	//ExMessage msg;
	setbkmode(TRANSPARENT);
	int number[5];
	int lastline[5];
	//在enter之前，最后一行数字不会保存在history中，为了防止在enter之前按上键查看历史记录时，最后一行数字被覆盖，
	//需要保存最后一行数字，这里用lastline数组保存
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
		if (key == 'q' || (int)key == 27) {//q或ESC退出游戏
			closegraph();
			//ShowWindow(hmenu, SW_SHOW);
			gui.menuinit();//返回主菜单
			return;
		}
		else if (key >= '0' && key <= '9') {//输入数字
			bool atlastline;//判断最后一行是否出现在画面中
			if (step <= 5) atlastline = true;
			else {
				atlastline = (topline + 4 == step) ? true : false;
			}
			if (atlastline) {//只有当最后一行出现在画面中时，才能输入数字
				if (pos == 0) {//第一个数不能为0
					if (key > '0') {
						settextcolor(numcolor);
						settextstyle(50, 0, ("微软雅黑"));
						outtextxy(235 + pos * (GRID_WIDTH + INTERVAL), 240 + line * (GRID_WIDTH + INTERVAL), key);
						number[pos] = key - '0';
						pos++;
					}
				}
				else if (pos > 0 && pos < 4) {
					settextcolor(numcolor);
					settextstyle(50, 0, ("微软雅黑"));
					outtextxy(235 + pos * (GRID_WIDTH + INTERVAL), 240 + line * (GRID_WIDTH + INTERVAL), key);
					number[pos] = key - '0';
					pos++;
				}
			}
		}
		else if ((int)key == 8) {//退格
			bool atlastline;//判断最后一行是否出现在画面中
			if (step <= 5) atlastline = true;
			else {
				atlastline = (topline + 4 == step) ? true : false;
			}
			if (atlastline) {//只有当最后一行出现在画面中时，才能退格}
				if (pos > 0 && pos <= 4) {
					pos--;
					setfillcolor(blockcolor);
					solidrectangle(205 + pos * (GRID_WIDTH + INTERVAL), 225 + line * (GRID_WIDTH + INTERVAL), 205 + pos * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, 225 + line * (GRID_WIDTH + INTERVAL) + GRID_WIDTH);
					number[pos] = 0;
				}
			}
		}
		else if (((int)key == 10 || (int)key == 13) && pos == 4) { //enter且数字输入完成(四位数)
			int booka[5], bookb[10];
			memset(booka, 0, sizeof(booka));
			memset(bookb, 0, sizeof(bookb));
			int as = 0, bs = 0;//A和B的数量
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
			//记录答案
			for (int i = 0; i < 4; ++i) {
				history[step][i] = number[i];
			}
			history[step][4] = as;
			history[step][5] = bs;
			//显示答案
			//此处要判断是否是到画面底部了，若是，则要全部上移一行(画面总共最多容纳5行)
			if (step >= 5) {//到画面底部了，要全部上移一行
				topline++;//更新显示的第一行对应的行号
				//最左边步数刷新,先涂掉原步数
				int stepx = 20, stepy = 130 + 80 + INTERVAL + 15;
				setfillcolor(bkcolor);
				solidrectangle(stepx, stepy - 15, (GRID_WIDTH + INTERVAL) * 2, stepy - 15 + (GRID_WIDTH + INTERVAL) * 5);
				//更新新步数
				settextcolor(numcolor);
				settextstyle(50, 0, "微软雅黑");
				for (int i = topline; i <= step; ++i) {
					outtextxy(52, stepy + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(i).c_str());
					outtextxy(140, stepy + (i - topline) * (GRID_WIDTH + INTERVAL), ":");
				}
				step++;
				outtextxy(52, stepy + 4 * (GRID_WIDTH + INTERVAL), to_string(step).c_str());
				outtextxy(140, stepy + 4 * (GRID_WIDTH + INTERVAL), ":");
				//前四行方块及数字更新
				setfillcolor(blockcolor);
				int inix = 2 * GRID_WIDTH + 3 * INTERVAL;
				int iniy = stepy - 15;
				for (int i = topline; i < step; ++i) {
					for (int j = 0; j < 4; ++j) {
						//方块填充以及数字更新
						solidrectangle(inix + j * (GRID_WIDTH + INTERVAL), iniy + (i - topline) * (GRID_WIDTH + INTERVAL), inix + j * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, iniy + (i - topline) * (GRID_WIDTH + INTERVAL) + GRID_WIDTH);
						outtextxy(235 + j * (GRID_WIDTH + INTERVAL), 240 + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(history[i][j]).c_str());
					}
				}
				//最后一行添加4个新的方块
				for (int j = 0; j < 4; ++j) {
					solidrectangle(inix + j * (GRID_WIDTH + INTERVAL), iniy + 4 * (GRID_WIDTH + INTERVAL), inix + j * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, iniy + 4 * (GRID_WIDTH + INTERVAL) + GRID_WIDTH);
				}
				//更新结果
				setfillcolor(bkcolor);
				int resx = inix + 4 * (GRID_WIDTH + INTERVAL);
				solidrectangle(resx, iniy, resx + 4 * (GRID_WIDTH + INTERVAL), iniy + 5 * (GRID_WIDTH + INTERVAL));
				//A
				settextcolor(colora);
				//settextstyle(50, 0, ("微软雅黑"));
				for (int j = 0; j < 4; ++j) {
					outtextxy(resx + (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "A");
				}
				//B
				settextcolor(colorb);
				for (int j = 0; j < 4; ++j) {
					outtextxy(resx + 3 * (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "B");
				}
				//结果
				settextcolor(numcolor);
				for (int j = 0; j < 4; ++j) {
					outtextxy(resx + 30, stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][4]).c_str());
					outtextxy(resx + 30 + 2 * (GRID_WIDTH + INTERVAL), stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][5]).c_str());
				}
			}
			else {//步数小于5步，只需要填上答案并添加下一行四个待填方格
				//输出结果
				settextcolor(numcolor);
				settextstyle(50, 0, "微软雅黑");
				int resx = 6 * GRID_WIDTH + 7 * INTERVAL;
				settextcolor(colora);
				outtextxy(resx + 30 + GRID_WIDTH + INTERVAL, 240 + line * (GRID_WIDTH + INTERVAL), "A");
				settextcolor(colorb);
				outtextxy(resx + 30 + (GRID_WIDTH + INTERVAL) * 3, 240 + line * (GRID_WIDTH + INTERVAL), "B");
				settextcolor(numcolor);
				outtextxy(resx + 30, 240 + line * (GRID_WIDTH + INTERVAL), to_string(history[step][4]).c_str());
				outtextxy(resx+30+2*(GRID_WIDTH+INTERVAL), 240 + line * (GRID_WIDTH + INTERVAL), to_string(history[step][5]).c_str());
				//添加下一行四个待填方格
				setfillcolor(blockcolor);
				int inix = 2 * GRID_WIDTH + 3 * INTERVAL;
				int iniy = 130 + 80 + INTERVAL;
				for (int i = 0; i < 4; ++i) {
					solidrectangle(inix + i * (GRID_WIDTH + INTERVAL), iniy + step * (GRID_WIDTH + INTERVAL), inix + i * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, iniy + step * (GRID_WIDTH + INTERVAL) + GRID_WIDTH);
				}
				//更新步数
				outtextxy(52, iniy + 15 + step * (GRID_WIDTH + INTERVAL), to_string(step + 1).c_str());
				outtextxy(140, iniy + 15 + step * (GRID_WIDTH + INTERVAL), ":");
				step++;
			}
			pos = 0;//记得归位
			if (as == 4) {
				win = true;
			}
		}
		else if (key == 'w' || key == 'W' || key == 72) {//接收到上键
			if (topline > 1) {//只有当显示的最上行不是第一行才可以上移
				if (topline + 4 == step) {
					//如果显示的最底下一行是目前最后一行，则要把最后一行的数字保存到lastline数组中
					for (int i = 0; i < 4; i++) lastline[i] = number[i];
				}
				topline--;
				//最左边步数刷新,先涂掉原步数
				int stepx = 20, stepy = 130 + 80 + INTERVAL + 15;
				setfillcolor(bkcolor);
				solidrectangle(stepx, stepy - 15, (GRID_WIDTH + INTERVAL) * 2, stepy - 15 + (GRID_WIDTH + INTERVAL) * 5);
				//更新新步数
				settextcolor(numcolor);
				settextstyle(50, 0, "微软雅黑");
				for (int i = topline; i < topline + 5; ++i) {
					outtextxy(52, stepy + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(i).c_str());
					outtextxy(140, stepy + (i - topline) * (GRID_WIDTH + INTERVAL), ":");
				}
				//方块及数字更新
				setfillcolor(blockcolor);
				int inix = 2 * GRID_WIDTH + 3 * INTERVAL;
				int iniy = stepy - 15;
				for (int i = topline; i < topline + 5; ++i) {
					for (int j = 0; j < 4; ++j) {
						//方块填充以及数字更新
						solidrectangle(inix + j * (GRID_WIDTH + INTERVAL), iniy + (i - topline) * (GRID_WIDTH + INTERVAL), inix + j * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, iniy + (i - topline) * (GRID_WIDTH + INTERVAL) + GRID_WIDTH);
						outtextxy(235 + j * (GRID_WIDTH + INTERVAL), 240 + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(history[i][j]).c_str());
					}
				}
				//结果更新
				setfillcolor(bkcolor);
				int resx = inix + 4 * (GRID_WIDTH + INTERVAL);
				solidrectangle(resx, iniy, resx + 4 * (GRID_WIDTH + INTERVAL), iniy + 5 * (GRID_WIDTH + INTERVAL));
				//A
				settextcolor(colora);
				//settextstyle(50, 0, ("微软雅黑"));
				for (int j = 0; j < 5; ++j) {
					outtextxy(resx + (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "A");
				}
				//B
				settextcolor(colorb);
				for (int j = 0; j < 5; ++j) {
					outtextxy(resx + 3 * (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "B");
				}
				//结果
				settextcolor(numcolor);
				for (int j = 0; j < 5; ++j) {
					outtextxy(resx + 30, stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][4]).c_str());
					outtextxy(resx + 30 + 2 * (GRID_WIDTH + INTERVAL), stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][5]).c_str());
				}
			}
		}
		else if (key == 's' || key == 'S' || key == 80) {//接收到下键
			if (topline + 4 < step) {//只有当显示的最下行不是最后一行才可以下移
				topline++;
				//最左边步数刷新,先涂掉原步数
				int stepx = 20, stepy = 130 + 80 + INTERVAL + 15;
				setfillcolor(bkcolor);
				solidrectangle(stepx, stepy - 15, (GRID_WIDTH + INTERVAL) * 2, stepy - 15 + (GRID_WIDTH + INTERVAL) * 5);
				//更新新步数
				settextcolor(numcolor);
				settextstyle(50, 0, "微软雅黑");
				for (int i = topline; i <= topline + 4; ++i) {
					outtextxy(52, stepy + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(i).c_str());
					outtextxy(140, stepy + (i - topline) * (GRID_WIDTH + INTERVAL), ":");
				}
				//方块及数字更新
				setfillcolor(blockcolor);
				int inix = 2 * GRID_WIDTH + 3 * INTERVAL;
				int iniy = stepy - 15;
				for (int i = topline; i <= topline + 4; ++i) {
					for (int j = 0; j < 4; ++j) {
						//方块填充
						solidrectangle(inix + j * (GRID_WIDTH + INTERVAL), iniy + (i - topline) * (GRID_WIDTH + INTERVAL), inix + j * (GRID_WIDTH + INTERVAL) + GRID_WIDTH, iniy + (i - topline) * (GRID_WIDTH + INTERVAL) + GRID_WIDTH);
					}
				}
				//数字更新
				if (topline + 4 == step) {//如果显示的最下面一行是目前最后一行，则要利用lastline数组更新显示的最后一行
					//前四行数字更新
					for (int i = topline; i < topline + 4; ++i) {
						for (int j = 0; j < 4; ++j) {
							outtextxy(235 + j * (GRID_WIDTH + INTERVAL), 240 + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(history[i][j]).c_str());
						}
					}
					//最后一行数字更新
					for (int j = 0; j < pos; ++j) {
						outtextxy(235 + j * (GRID_WIDTH + INTERVAL), 240 + 4 * (GRID_WIDTH + INTERVAL), to_string(lastline[j]).c_str());
					}
				}
				else {
					//五行数字全部一起更新
					for (int i = topline; i <= topline + 4; ++i) {
						for (int j = 0; j < 4; ++j) {
							outtextxy(235 + j * (GRID_WIDTH + INTERVAL), 240 + (i - topline) * (GRID_WIDTH + INTERVAL), to_string(history[i][j]).c_str());
						}
					}
				}
				//结果更新
				setfillcolor(bkcolor);
				int resx = inix + 4 * (GRID_WIDTH + INTERVAL);
				solidrectangle(resx, iniy, resx + 4 * (GRID_WIDTH + INTERVAL), iniy + 5 * (GRID_WIDTH + INTERVAL));
				if(topline+4==step) {//如果显示的最下面一行是目前最后一行，则只用更新前四行的结果
					//A
					settextcolor(colora);
					//settextstyle(50, 0, ("微软雅黑"));
					for (int j = 0; j < 4; ++j) {
						outtextxy(resx + (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "A");
					}
					//B
					settextcolor(colorb);
					for (int j = 0; j < 4; ++j) {
						outtextxy(resx + 3 * (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "B");
					}
					//结果
					settextcolor(numcolor);
					for (int j = 0; j < 4; ++j) {
						outtextxy(resx + 30, stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][4]).c_str());
						outtextxy(resx + 30 + 2 * (GRID_WIDTH + INTERVAL), stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][5]).c_str());
					}
				}
				else {//更新全部五行的结果
					//A
					settextcolor(colora);
					//settextstyle(50, 0, ("微软雅黑"));
					for (int j = 0; j < 5; ++j) {
						outtextxy(resx + (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "A");
					}
					//B
					settextcolor(colorb);
					for (int j = 0; j < 5; ++j) {
						outtextxy(resx + 3 * (GRID_WIDTH + INTERVAL) + 30, stepy + j * (GRID_WIDTH + INTERVAL), "B");
					}
					//结果
					settextcolor(numcolor);
					for (int j = 0; j < 5; ++j) {
						outtextxy(resx + 30, stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][4]).c_str());
						outtextxy(resx + 30 + 2 * (GRID_WIDTH + INTERVAL), stepy + j * (GRID_WIDTH + INTERVAL), to_string(history[topline + j][5]).c_str());
					}
				}
			}
		}
		//结束判断
		if (win) {//跳转到胜利画面
			Sleep(500);
			closegraph();
			finishwin(step - 1);
			break;
		}
		if (step == 100) {//跳转到失败画面
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
	settextstyle(40, 0, "宋体");
	string s1 = "恭喜你，你赢了！";
	string s2 = "步数";
	string stepnum = to_string(steps);
	//s2 += stepnum;
	int score = 0;
	if (steps <= 5) score = 100;//5步以内为100分
	else if (steps <= 10) {
		score = 100 - (steps - 5) * 4;//6-10步为96-80分
	}
	else if (steps <= 20) {
		score = 80 - (steps - 10) * 3;//11-20步为77-50分
	}
	else if (steps <= 30) {
		score = 50 - (steps - 20) * 2;//21-30步为48-30分
	}
	else if (steps <= 40) {
		score = 30 - (steps - 30) * 1;//31-40步为29-20分
	}
	else score = 10;//40步以上为10分
	string s3 = "得分";
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
	for (Button* button : buttons[currentindex]) button->draw();//绘制胜利界面按钮
	ExMessage msg;
	while (1) {
		if (peekmessage(&msg)) {
			int mousex = msg.x;
			int mousey = msg.y;//获取鼠标位置
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
	settextstyle(40, 0, "宋体");
	string s1 = "很遗憾，你输了!";
	string s2 = "99步内未能猜出数";
	int x1 = (450 - textwidth(s1.c_str())) / 2;
	int x2 = (450 - textwidth(s2.c_str())) / 2;
	outtextxy(x1, 20, s1.c_str());
	outtextxy(x2, 80, s2.c_str());
	currentindex = 2;
	for (Button* button : buttons[currentindex]) button->draw();//绘制失败界面按钮
	ExMessage msg;
	while (1) {
		if (peekmessage(&msg)) {
			int mousex = msg.x;
			int mousey = msg.y;//获取鼠标位置
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