#pragma once

const int capacity = 30;
typedef char base;	

class Btree{
    private:
        struct node {
        	base info;
            int p;
        	int lt;
        int rt;
        	int lev;
        };
    public:
        node btMas[capacity];
        int inode;
        int iroot;
        int changingLev;
    Btree(){
            inode = 0;
            iroot = 0;
            changingLev = 0;
            for (int i = 0; i < capacity; i++){
                btMas[i].info = 0;
                btMas[i].p = 0;
                btMas[i].lt = 0;
                btMas[i].rt = 0;
                btMas[i].lev = 0;
            }
    }       
    bool isNull(int binAdress);
    base root(int binAdress); // для непустого бин.дерева
    int left(int binAdress); // для непустого бин.дерева
    int right(int binAdresse); // для непустого бин.дерева
    int parent(int adr);	// для непустого бин.дерева
    int cons(const base &elem, int left, int right);
    void print(int len);
    void displayBT(int binAdress, int n); 
    int height (int binRoot);
    void putlevels(int p, int iroot);       
    int checkP( int checking);
    void setParent(); 
    friend class Forest;  
};
