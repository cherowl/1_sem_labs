// ����������� ��������� ����� � �������� �������
// ������� 20
#include <iostream>
#include <conio.h>
using namespace std;
int main ()
{
setlocale (0,""); // ��� ������������� ��������� ��� �����-������
double x, y; // ���������� ����� p
// ��������� ���������� ����� � ����������
cout <<"������� ���������� ����� Q (x y):\n";
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
	cout <<"������� ��� ��� \n";
}
	if ((x>=-1) && (x<=0) && (y<=1) && (y>=0) || (x*x+y*y<=1) && (x>=0) && (y<=0))
	cout <<"����� ������ � �������\n";
	else cout <<"�����  �� ������ � �������\n";
_getch (); // ��� �������� "������ �����-������"
return 0;
}