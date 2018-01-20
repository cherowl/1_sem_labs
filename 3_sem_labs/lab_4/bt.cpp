#include "bt.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//-------------------------------------
bool Btree::isNull(int binAdress) // true = null
{
	return binAdress == 0;
}
//-------------------------------------
base Btree::root(int binAdress)			// для непустого бин.дерева
{
	if (binAdress != 0)
		return btMas[binAdress].info;
}
//-------------------------------------
int Btree::left(int binAdress)		// для непустого бин.дерева
{
	if (binAdress != 0)
		return btMas[binAdress].lt;
}
//-------------------------------------
int Btree::right(int binAdress)		// для непустого бин.дерева
{
	if (binAdress != 0)
		return btMas[binAdress].rt;
}
//-------------------------------------
int Btree::parent(int adr)		// для непустого бин.дерева
{
	if (isNull(adr)) return 0; // корень
    return btMas[adr].p;
}
//-------------------------------------
int Btree::cons(const base &elem, int left, int right)
{
	btMas[++inode].info = elem;
	btMas[inode].lt = left;
	btMas[inode].rt = right;
	return inode;
}
//-------------------------------------
void Btree::print(int len){
	int i = 1;
	if(!btMas) cout << "Ошибка: btMas is null"<< endl;
	while(i <= len	){
		cout << "["<< i << "]   info-" << btMas[i].info << "  p-" << btMas[i].p << "   lt-"<< btMas[i].lt << " rt- " << btMas[i].rt <<"  lev-"<< btMas[i].lev<<endl;
		i++;
	}	
}
//-------------------------------------
int Btree::height (int binRoot)
{
	if (isNull(binRoot)) return 0;
	return max (height (left(binRoot)), height(right(binRoot))) + 1;
}
//-------------------------------------
void Btree::putlevels(int p, int indexRoot){
    int ilev = 0;
    if (!isNull(indexRoot)){
		btMas[indexRoot].lev = btMas[p].lev + 1;
		putlevels(indexRoot, left(indexRoot));
    	putlevels(indexRoot, right(indexRoot));
	}   
}
//------------------------------------------------
void Btree::displayBT(int binAdress, int n)
{
    if (binAdress != 0) {
        displayBT(right(binAdress), n + 1);//Прохождение по правым
        for (int i = n + 1; i > 0; i--)
            cout <<"   ";
        cout << btMas[binAdress].info << endl;//Вывод текущего
        displayBT(left(binAdress), n + 1);//Прохождение по левым
    }

}
//------------------------------------
void Btree::setParent()
{	
	int i;
	for(i = 1; i < inode+1; i++){
		int some = left(i);
		if (some) { btMas[some].p = i; } 
		else btMas[some].p = 0;
		
		some = right(i); 
		if(some) { btMas[some].p = i; }
		else btMas[some].p = 0;
		
	}
}
//------------------------------------------------
int Btree::checkP(int checking) // возвращает отца checking
{	
	if(!isNull(checking)){
		if(checking == right(btMas[checking].p)){	
			checkP(btMas[checking].p);
		}  	
		else return btMas[checking].p; 	
	}
}
//------------end of Btree--------------
