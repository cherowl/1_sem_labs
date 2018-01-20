#include "forest.h"
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

stack <int> s;
std::vector <int> v;

//----------------Forest-----------------
bool Forest::isNull(int adr) // true = null
{
	return adr == 0;
}
//-------------------------------------
base Forest::root(int adr)			// для непустого бин.дерева
{
	if (adr != 0)
		return fMas[adr].info;
}
//-------------------------------------
int Forest::parent(int adr)		// для непустого бин.дерева
{
	if (isNull(adr)) return 0; // корень
    return fMas[adr].p;
}
//-------------------------------------
void Forest::print(){
    cout << "Printing forest" << endl;    
	int i = 1;
    if(!fMas) cout << "Ошибка: fMas is null"<< endl;
	while(i < inode + 1){   
		cout << "["<< i << "]  info:" << fMas[i].info << ".  p:" << fMas[i].p <<".  bigp"<< fMas[i].bigp <<".  lev:"<< fMas[i].lev <<  endl;
		i++;	
    }
}
//------------------------------------------------
void Forest::cons(const base& elem, int parentAdr, int iN) // not creating a tree
{
    inode = iN;  
    fMas[iN].info = elem;    
    fMas[iN].p = parentAdr;  
} 
//------------------------------------------------
void Forest::makeForest(class Btree& b)
{	
	int i;
	for(i = b.inode ; i >= 1; i--){
        int flag = 0;
        if(i == b.iroot){ cons(b.root(i), 0, b.iroot); flag = 1; }
		
        int some = b.left(i);
        Btree::node* bnode = &b.btMas[some];
		if (some) { cons(bnode->info, b.checkP(some), some); flag = 1;} 
		
        some = b.right(i); 
        bnode = &b.btMas[some];               
		if(some) { 
            cons(bnode->info, b.checkP(some), some);  
            flag = 1;
            continue;          
        }
        if(!flag) { cons(b.btMas[i].info, b.checkP(i), i); }
	}
    inode = b.inode;
    putlevels();
    setBigP();
}
//------------------------------------------------
int Forest::putlevels()
{
    for(int i = 1; i <= inode; i++){
        fMas[i].lev = lev(i); 
    }
}
//------------------------------------------------
int Forest::lev(int index)
{
    int i;
    for(i = 0; index != 0; i++){
       index = fMas[index].p;
    }
    return i;
}
//------------------------------------------------
void Forest::out(int ind)
{
    for(int j = 0; j < fMas[ind].lev; j++){ cout << "   "; } //shift
    cout <<fMas[ind].info << endl;  // вывести элемент, чей отец - ind     
}
//------------------------------------------------
int Forest::find(int ind)
{
    for(int i = inode; i >= 1; i--){ 
        if(ind == fMas[i].p && label(i) == 1 ){
            return i;  // элемент элемент, чей отец - ind  
        }
    } 
    fMas[ind].lb = 0;
    return 0; // not found 
}
//------------------------------------------------
bool Forest::label(int ind)
{
    return fMas[ind].lb == 1; // 1 = true(еще не рассмотретренный узел), 0 = false
}
//---------------------------------------------
void Forest::displayTree(int ir)
{
    static int flag = 0;
    //cout<<"flag-" <<flag;
    if(ir){                  
        if(!flag) { out(ir); flag = 1; s.push(ir);}
        if(!s.empty()){
            int f = find(ir); //cout<<"f: " << f << endl;
	        if(f){ 
                s.push(f);
                out(f);
                displayTree(f);
            }else{
                s.pop();
                if(!s.empty()) displayTree(s.top());
            }
        } flag = 0;
    } 
}
//---------------------------------------------
void Forest::displayF()
{
    int numT = 0;
    for(int i = inode; i >= 1; i--){ 
        if(!fMas[i].p){ 
            cout << ++numT << " дерево леса" << endl; 
            displayTree(i); 
        }
    }
    amountTrees = numT; 
    cleanLabels();    
}
//---------------------------------------------
void Forest::cleanLabels()
{
    for (int i = 0; i < capacity; i++){
           fMas[i].lb = 1;            
    }
}
//---------------------------------------------
void Forest::setBigP()
{
    for(int ind = inode; ind >= 1; ind--){ 
        if(fMas[ind].p == 0){
            fMas[ind].bigp = 0;
            //cout << ind <<". bp" << fMas[ind].bigp << endl;
        }
        else{    
            int i;
            int index = ind;
            for(i = 0; fMas[index].lev != 1; i++){
               index = fMas[index].p;
            }
            fMas[ind].bigp = index; //cout << ind<<". bp" << fMas[index].bigp << endl;
        }
    }
}
//---------------------------------------------
void Forest::oneLevOneTree(int lev, int treeroot)
{
    for(int i = inode; i >= 1; i--){ 
        if(treeroot == fMas[i].bigp && label(i) == 1 && fMas[i].lev == lev ){
                //cout << fMas[i].info;
                v.push_back(i);
                fMas[i].lb = 0; //выведен
            }
        }
}
//---------------------------------------------
int Forest::fix(class Btree& b)
{
    int flag = 0;
    //cout << v.size() << endl;
    for(int i = 0; i < v.size()-1; i++){
        if(b.btMas[v[i]].lev > b.btMas[v[i+1]].lev && fMas[v[i]].bigp == fMas[v[i+1]].bigp && fMas[v[i]].lev == fMas[v[i+1]].lev ){
            swap(v[i], v[i+1]);    flag = 1;
        }

    }
    return flag;
}
//---------------------------------------------
bool Forest::isLevel(int lev)
{
    if(lev){
        for(int i = inode; i >= 1; i--){ 
            if(fMas[i].lev == lev) { return true;} 
        }
    return false;
    }
}
//---------------------------------------------
void Forest::horisontalBuild()
{
    int static flag = 0; // 1 level print
  
    int static level = 0;
    level++;
    if (!flag) {
        for(int i = inode; i >= 1; i--){ 
            if(!fMas[i].p){  v.push_back(i); flag = 1;} //cout << fMas[i].info 
        }
    }
    //if(isLevel(2)){
        for(int j = inode; j >= 1; j--){ 
            if(!fMas[j].p){ // j - переключатель деревьев
                oneLevOneTree(level, j); //cout << "rt - " << i << endl;
            }
        }
    
        if(isLevel(level+1)) {
            horisontalBuild();
        }
}

//------------------end of Forest---------------
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
 
