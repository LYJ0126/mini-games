#include "game.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
using namespace std;

vector<vector<Button*>>buttons;
int currentindex = 0;//ҳ��������0Ϊ���˵���1Ϊ��Ϸ���棬2Ϊ��Ϸʤ������
guipart gui;
gamepart game;
int main()
{
	//std::wcout.imbue(std::locale("chs"));//�����������
	//������ӳ��
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