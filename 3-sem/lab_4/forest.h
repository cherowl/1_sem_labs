#pragma once

#include "bt.h"
#include <stack>
#include <vector>
typedef char base;

class Forest{
private:
    struct node {
        base info;
        int p;
        int bigp;
        int lev;
        int lb;
    };

public:
    node fMas[capacity];
    int inode;
    int firstRoot;
    int amountTrees;

    Forest(class Btree b){
        inode = 0;
        firstRoot = b.iroot;
        amountTrees = 0;
        for (int i = 0; i < capacity; i++){
            fMas[i].info = 0;
            fMas[i].p = 0;
            fMas[i].bigp = 0;
            fMas[i].lev = 0;
            fMas[i].lb = 1;            
        }
    }
    bool isNull(int adr);
    base root(int adr); // для непустого бин.дерева
    int parent(int adr); // для непустого бин.дерева
    void print();
    void cons(const base& elem, int parentAdr, int iN);
    void makeForest(class Btree& b);
    int putlevels();
    int lev(int index);
    void out(int ind);
    bool label(int ind);
    int find(int ind);
    void displayTree(int ir);
    void displayF();
    void cleanLabels();
    void setBigP();
    bool isLevel(int lev);
    void oneLevOneTree(int lev, int treeroot);
    void horisontalBuild();
    int fix(class Btree& b);
};
