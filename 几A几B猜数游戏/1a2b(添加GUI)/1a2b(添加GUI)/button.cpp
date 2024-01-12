//按钮类函数

#include "game.h"

Button::Button(int _x, int _y, int _width, int _height, float _scale, bool _hover, 
	string _text, function<void()> _onclick) {//构造函数
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
	hover = mousex >= x && mousex <= x + width && mousey >= y && mousey <= y + height;//检测鼠标是否在按钮上
	if (hover) {
		scale = 0.9f;//鼠标悬停时缩小按钮
	}
	else {
		scale = 1.0f;//鼠标离开时恢复按钮
	}
}

bool Button::checkclick(int mousex, int mousey)
{
	if (hover && mousex >= x && mousex <= x + width && mousey >= y && mousey <= y + height) {//检测鼠标是否在按钮上并且点击
		onclick();//执行按钮点击事件
		hover = false;
		scale = 1.0f;
		return true;
	}
	return false;
}

void Button::draw()
{
	setfillcolor(bkcolor);
	//鼠标指向按钮时，按钮会缩放变小。先将原来按钮处赋成背景色，防止空隙处颜色还是按钮色，与背景突兀。
	fillrectangle(x, y, x + width, y + height);
	int scalewidth = width * scale;//缩放后的宽度
	int scaleheight = height * scale;//缩放后的高度
	int scalex = x + (width - scalewidth) / 2;//缩放后的x坐标
	int scaley = y + (height - scaleheight) / 2;//缩放后的y坐标
	if (hover) {
		setlinecolor(RGB(187, 173, 160));
		setfillcolor(RGB(229, 241, 251));
	}
	else {
		setlinecolor(RGB(187, 173, 160));
		setfillcolor(RGB(255, 255, 255));
	}
	fillrectangle(scalex, scaley, scalex + scalewidth, scaley + scaleheight);//绘制按钮
	settextcolor(RGB(30, 30, 30));
	setbkmode(TRANSPARENT);
	settextstyle(30 * scale, 0, _T("微软雅黑"));
	int textx = scalex + (scalewidth - text.length() * 10 * scale) / 2;//文字x坐标(10为文字大小)
	int texty = scaley + (scaleheight - textheight(_T("微软雅黑"))) / 2;//文字y坐标
	outtextxy(textx, texty, text.c_str());//绘制文字
}