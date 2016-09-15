// Определение попадания точки в заданную область
// Вариант 20
#include <iostream>
#include <conio.h>
using namespace std;
int main ()
{
setlocale (0,""); // для использования кириллицы при вводе-выводе
double x, y; // координаты точки p
// считываем координаты точки с клавиатуры
cout <<"Введите координаты точки Q (x y):\n";
//cin >> x >> y;
while(true)
{
	cin >> x>>y;
	if(!cin) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "error \n";
		cin >> x>>y;
		continue;
	}
	break;
	cout <<"Введите еще раз \n";
}
	if ((x>=-1) && (x<=0) && (y<=1) && (y>=0) || (x*x+y*y<=1) && (x>=0) && (y<=0))
	cout <<"Точка попала в область\n";
	else cout <<"Точка  не попала в область\n";
_getch (); // для задержки "экрана ввода-вывода"
return 0;
}