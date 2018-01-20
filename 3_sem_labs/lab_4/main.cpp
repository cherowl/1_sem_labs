/*6. (Обратная задача.) Для заданного бинарного дерева с произвольным типом элементов:
а) получить лес, естественно представленный этим бинарным деревом;
б) вывести изображение бинарного дерева и леса;
в) перечислить элементы леса в горизонтальном порядке (в ширину).*/
#include "bt.h"
#include "forest.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int lenb = 0;
int flag = 0;
extern vector<int>v;

int makeBT (class Btree& b,string& buf);
void printHorisontal(class Forest& fr, class Btree& bt);

int main(int argc, char* argv[]){ 
    std::fstream f; 
    f.open(argv[1], ios::in); // открытие файла для чтения 
    
    cout << "Выберете способ ввода данных: 1 - файла, 2 - консоль: ";
    int tap = 0;
    int lenF = 0; int ro = 0;
    string strIn;
    //int capacity = 0;
    cin >> tap;

    switch(tap){
        case 1:
            if(!f) { cout<< "Файл-источник не был открыт"<< endl; exit(1);}
            //Считывание из файла
            getline(f, strIn); 
            f.close();
            break;
        case 2:
            cout << "Введите бинарное дерево, используя '/' для обозначения нулевых потомков "<<endl;    
            cin >> strIn; 
            break;
        default:
            cout << "Ошибка при выборе источника данных! "<<endl;
            exit(1);  
    }
    lenb = strIn.size();
    if(!lenb){
        cout << "Входные данные отсутсвуют" << endl;
        exit(1);
    } 

    if (capacity < lenb){
        cout << "Невозможно построить бинарное дерево (превышение количества узлов)" <<  endl;
        exit(1);
    } 
    cout << "Иcходные данные"<< endl;
    cout << strIn << endl;
   
    //ввод дерева     
    class Btree bt;
    
    bt.iroot = makeBT (bt, strIn);
    cout << "Номер корня = "<< bt.iroot <<endl;   
     
    cout << "Изображение бинарного дерева:" << endl;
    bt.displayBT(bt.iroot, 0);
    bt.putlevels(0,bt.iroot);//<<endl;
    bt.setParent();
    bt.print(bt.iroot); 
    cout << endl;

    class Forest fr(bt);
    fr.makeForest(bt);
    cout << "Изображение леса: " << endl;
    fr.displayF();
    cout << "Элементы леса в горизонтальном порядке: " << endl;    
    printHorisontal(fr, bt);
        
    fr.print();
    f.close();
}

int makeBT (class Btree& b, string& buf)
{	
    base simb;
    int p, q;
    static int i = 0;
    if(i < lenb){ 
        simb = buf[i++]; 
        if (simb == '/') {return 0;} 
        p = makeBT(b, buf); //cout << i << "). p = " << p << endl; 
        q = makeBT(b, buf); //cout << i << "). q = " << q << endl; 
        return b.cons(simb, p, q);
    }
    return b.root(lenb-1); // возвращает индекс корня
}

void printHorisontal(class Forest& fr, class Btree& bt)
{
    fr.horisontalBuild();
    //cout << endl;
    int resfix = fr.fix(bt);
    while(resfix){
      resfix = fr.fix(bt);
    }  
    if(!
    resfix){
     //cout << "fixes"<<endl;
    for(int i = 0; i < v.size(); i++){    
        cout << fr.fMas[v[i]].info;
    } cout <<endl;
    }
}



