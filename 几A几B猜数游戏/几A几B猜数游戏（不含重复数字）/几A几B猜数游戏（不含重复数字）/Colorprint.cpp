#include<iostream>
#include<Windows.h>
#include "guessnumber.h"

void Colorprint::colorprint(const char* s, int color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
	printf(s);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}
void Colorprint::colorprint(int x, int color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
	std::cout << x;
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}