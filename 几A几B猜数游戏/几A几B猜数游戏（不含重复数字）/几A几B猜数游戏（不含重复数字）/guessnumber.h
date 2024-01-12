#pragma once
#include<cstring>
//#include<time.h>
//#include<sys/timeb.h>
#include <random>
class guess
{
private:
	int* num = new int[5];
public:
	void f();
	~guess();
};

class Colorprint
{
private:
	friend class guess;
	void colorprint(const char*, int);
	void colorprint(int, int);
};