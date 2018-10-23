/*Задача. Рассматриваются ряды f(x) = Σi = 0...∞ ui. Для каждого индивидуального
задания определены вид элемента ряда ui, функция f(x), область сходимости D,
если D ≠ R. 
Вариант 20: u(i)=2^(2i)*(i!)^2*x^(2i+1)/(2i+1)!/(i+1); f(x)=arcsin(x)^2; x^2<=1.*/
// 
// Лабораторная №3-4. Вариант 20.
// lab 3.c 
// Черкасова Елена, группа 6382
// 25.10.2016.
//
//Программа вычисляет значение arcsin(x)^2 через разложение в бесконечный ряд

#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <conio.h>

#define real = double; // Глобальная переменная

// Вычисление машинного эпсилон
// Предусловие: 1 + eps > 1
// Постусловие:
// eps - машинное эпсилон
// Возвращает значение машинного эпсилон
real FEps(real eps = 1.0);

// Ввод параметра x
// Предусловие: 
// Постусловие: x*x > 1	
// Возвращает значение x
real FX(real x);

// Вычисление суммы sum (i=1...n) 2^2i(i!)x^(2i+1)/(2i+1)!/(i+1)
// Предусловие: fabs(u) > eps
// Постусловие:	
// i-номер слагаемого
// u-слагаемое
// Возвращает значение вычисленной суммы и номер слагаемого
real FSum(real sum, real u, int i = 1, real x);

int main()
{
	int i = 1;
	real u, sum, x, f;
	printf("Machine number= %e\n", FEps());
	x = FX();
	printf("x = %le", x, "\n");
	f = asin(x)*asin(x); // Функция для сравнения с суммой ряда
	sum = FSum(x, x, i, x);
	Fsum(x, x, i, x);
	printf("S(x) = %20.10le\n", sum);
	printf("asin(x)*asin(x) =%le\n", f);
	printf("Absolute error = %le\n", fabs(sum - f)); // Абсолютная погрешность
	printf("Remote error = %le\n", fabs(sum - f) / f); // Относительная погрешность
	_getch();
	return 0;
}
real FEps()
{
	real eps = 1.0;
	while (1 + eps > 1) {
		eps /= 2;
	}
	eps *= 2;
	return eps;
}
real FX() {
	real x;
	do {
		printf("Enter x: \n");
		scanf_s("%lf", &x, "\n");
	} while (x*x > 1);
	return x;
}
real FSum(real sum, reale u, int i, real x)
{
	while (fabs(u) > FEps()) { // Инвариант цикла : s = s(i) & u = u(i)
		u *= 2 * i*i*x*x / (2 * i + 1) / (i + 1);
		sum += u;
		printf("%e	%e\n", u, sum); 
		i++; 
	}
	return sum;
}
