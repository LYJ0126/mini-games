#include "game.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
using namespace std;

vector<vector<Button*>>buttons;
int currentindex = 0;//页面索引，0为主菜单，1为游戏界面，2为游戏胜利界面
guipart gui;
gamepart game;
int main()
{
	//std::wcout.imbue(std::locale("chs"));//设置中文输出
	//键盘码映射
	gui.buttonsinit();
	gui.menuinit();
	//closegraph();
	//Sleep(10000);
	int len = buttons.size();
	for (int i = 0; i < len; i++) {
		for (Button* button : buttons[i]) {
			delete button;
		}
	}
	//cout << "here";
	//_CrtDumpMemoryLeaks();
	//getchar();
	return 0;
}