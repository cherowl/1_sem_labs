// 
// Лабораторная №2. Вариант 5с.
// lab 2.cpp 
// Черкасова Елена, группа 6382
// 11.10.2016.
//
// Задача. Нахождение наименьшего n такого, что сумма n Фибоначчи больше некоторого заданного m.

#include <limits.h> 
#include <stdio.h>
#include <iostream>
#include <conio.h>

using namespace std;
using uint = unsigned int;

int fib();
int main()
{
		int n;
		int m;
		int sum;
		
		n = fib();
		printf("Min n to sum>m is the following: %d", n ,"\n");
		
		_getch();
		return 0;
}

int fib() {
	uint fib1 = 1;
	uint fib2 = 1;
	uint i = 1;
	uint chan;
	int n = 1;
	int m;
	int sum=1;
	char buf[BUFSIZ]; //создание буфера

	printf("Input m, m>1 \n");

	while(!scanf_s("%d",&m)){
		system("cls"); //очистка экрана
		printf("Error 1. Input m again. \n");
		fflush(stdin); //очистка потока ввода
		setbuf(stdin, buf); //установка буффера для потока ввода
	}
	if (m < 0) { //проверка на переполнение
		printf("Error 2");
		_getch();
		exit(2);
	}
		for (i = 1; i > 1, m > 1, sum <= m; i++) {
			chan = fib1;
			if (UINT_MAX - fib1 >= fib2) fib1 += fib2;
			if (fib1<0) {
				printf("Error 2");
				_getch();
				exit(2);
			}
			fib2 = chan;
			if (UINT_MAX - sum >= fib2) sum += fib2;
			if (sum<0) {
				printf("Error 2");
				_getch();
				exit(2);
			}
			n++;
		}
	return n;
}
