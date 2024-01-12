#include<iostream>
#include<cmath>
#include "guessnumber.h"
using namespace std;


void guess::f()
{
	Colorprint cc;
	cc.colorprint("��Ϸ����\n", 6);
	cc.colorprint("    �����������һ��������Ҳ��������������������ֲ������\n", 6);
	cc.colorprint("    �������÷�������������Ĳ�������������Խ�ٷ���Խ�ߡ�5���������֣�7������90������\n", 6);
	//srand((int)time(NULL));
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
	int n = 0, step = 1;
	Colorprint ss;
	while (n != s) {
		ss.colorprint("�����,����������\"-1\"\n\n", 6);
		cin >> n;
		if (n == -1)  return;
		if (n < 1000 || n>9999) { 
			ss.colorprint("�����������������\n\n", 4);
			continue;
		}
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
		cout << "��";
		ss.colorprint(step, 12);
		cout << "��" << endl;
		if (as && bs) {
			ss.colorprint("�¶�", 6), ss.colorprint(as, 3), ss.colorprint("����������λ����ȷ��", 6);
			ss.colorprint("�¶�", 6), ss.colorprint(bs, 3), ss.colorprint("�����ֵ���λ�ò���ȷ��", 6);
		}
		else if (as && bs == 0) {
			ss.colorprint("�¶�", 6), ss.colorprint(as, 3), ss.colorprint("����������λ����ȷ��", 6);
		}
		else if (bs && as == 0) {
			ss.colorprint("�¶�", 6), ss.colorprint(bs, 3), ss.colorprint("�����ֵ���λ�ò���ȷ��", 6);
		}
		else ss.colorprint("û�����ֲ¶ԡ�", 6); 
		cout << "   ";
		ss.colorprint("( ", 14), ss.colorprint(as, 12), ss.colorprint("A", 11);
		ss.colorprint(bs, 12), ss.colorprint("B", 9), ss.colorprint(" )", 14);
		cout << endl << endl;
		step++;
	}
	cout << "���¶���" << endl;
	int fenshu = 0;
	if (step <= 5) fenshu = 100;
	else if (step > 5 && step <= 19) fenshu = 100 - 5 * (step - 5);
	else fenshu = 20;
	ss.colorprint("�÷�: ", 6), ss.colorprint(fenshu, 12);
	if (step <= 7) {
		cout << "Newbility!(ţ��)";
	}
	return;
}

guess::~guess()
{
	delete[]num;
}