//��ť�ຯ��

#include "game.h"

Button::Button(int _x, int _y, int _width, int _height, float _scale, bool _hover, 
	string _text, function<void()> _onclick) {//���캯��
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	scale = _scale;
	hover = _hover;
	text = _text;
	onclick = _onclick;
}

void Button::checkhover(int mousex, int mousey)
{
	hover = mousex >= x && mousex <= x + width && mousey >= y && mousey <= y + height;//�������Ƿ��ڰ�ť��
	if (hover) {
		scale = 0.9f;//�����ͣʱ��С��ť
	}
	else {
		scale = 1.0f;//����뿪ʱ�ָ���ť
	}
}

bool Button::checkclick(int mousex, int mousey)
{
	if (hover && mousex >= x && mousex <= x + width && mousey >= y && mousey <= y + height) {//�������Ƿ��ڰ�ť�ϲ��ҵ��
		onclick();//ִ�а�ť����¼�
		hover = false;
		scale = 1.0f;
		return true;
	}
	return false;
}

void Button::draw()
{
	setfillcolor(bkcolor);
	//���ָ��ťʱ����ť�����ű�С���Ƚ�ԭ����ť�����ɱ���ɫ����ֹ��϶����ɫ���ǰ�ťɫ���뱳��ͻأ��
	fillrectangle(x, y, x + width, y + height);
	int scalewidth = width * scale;//���ź�Ŀ��
	int scaleheight = height * scale;//���ź�ĸ߶�
	int scalex = x + (width - scalewidth) / 2;//���ź��x����
	int scaley = y + (height - scaleheight) / 2;//���ź��y����
	if (hover) {
		setlinecolor(RGB(187, 173, 160));
		setfillcolor(RGB(229, 241, 251));
	}
	else {
		setlinecolor(RGB(187, 173, 160));
		setfillcolor(RGB(255, 255, 255));
	}
	fillrectangle(scalex, scaley, scalex + scalewidth, scaley + scaleheight);//���ư�ť
	settextcolor(RGB(30, 30, 30));
	setbkmode(TRANSPARENT);
	settextstyle(30 * scale, 0, _T("΢���ź�"));
	int textx = scalex + (scalewidth - text.length() * 10 * scale) / 2;//����x����(10Ϊ���ִ�С)
	int texty = scaley + (scaleheight - textheight(_T("΢���ź�"))) / 2;//����y����
	outtextxy(textx, texty, text.c_str());//��������
}