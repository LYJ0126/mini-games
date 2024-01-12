#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include "Guessnumber.h"
void guessnumber::guess()
{
	//std::vector<int>num(5);
	int* num = new int[5];
	srand((int)time(NULL));
	int x = rand() % (10000 - 1000) + 1000;
	int t = x, s = x, i = 4;
	while (t != 0) {
		num[i] = t % 10;
		t /= 10;
		i--;
	}
	int n = 0, step = 0;
	while (n != s) {
		std::cin >> n;
		if (n < 1000 || n>9999) {
			std::cout << "输入错误，请重新猜数" << std::endl << std::endl;
			continue;
		}
		step++;
		int number[5];
		int f = n, k = 4;
		while (f != 0) {
			number[k] = f % 10;
			f /= 10;
			k--;
		}
		int booka[5], bookb[10];
		memset(booka, 0, sizeof(booka));
		memset(bookb, 0, sizeof(bookb));
		int as = 0, bs = 0;
		for (int j = 1; j <= 4; j++) {
			if (number[j] == num[j]) {
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
				if (bookb[number[j]] == 1) {
					bs++;
				}
			}
		}
		std::cout << "第" << step << "步：";
		std::cout << as << "A" << bs << "B" << std::endl << std::endl;
	}
	std::cout << "您猜对了" << std::endl;
	if (step <= 10) {
		std::cout << "Newbility!(牛逼)";
	}
	delete[]num;
}
guessnumber::~guessnumber() {};