#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
// #include <cstdlib>
#include "iter.hpp"

using namespace std;

template <typename T> class List;
template <typename T> class Iter;

//--------------Elem------------------------------
template <typename T>
class Elem
{
    friend class List<T>;
    friend class Iter<T>; 

    T info;
    Elem* next;
    Elem* prev;

public:
    Elem(T info = decltype(info)(0), Elem *n = nullptr, Elem *p = nullptr) : info(info), next(n),prev(p) {}
    T& get(){ return info; } // getter and setter too because of &
    const T& get() const { return info; } 
};
//-----------------------------------------------

//------------------List--------------------------
template <typename T>
class List
{   
    // friend class Elem<T>;
    friend class Iter<T>;

    Elem<T> *head; 
    Elem<T> *tail;

public: 
    List() : head (nullptr), tail(nullptr) {};
    ~List();
    
    bool is_empty();  
    void insert_after(T value, size_t index);
    void insert_head (T value);
    void insert_tail (T value);
    void print(); 
    void delete_elem(size_t index);
    size_t get_size();
    Elem<T> *find(size_t index);

    T operator [] (size_t index);
    List<T> &operator= (const List<T>  &r);

    Elem<T> *get_head() { return head; }
    Elem<T> *get_tail() { return tail; }

    Iter<T> begin() { return Iter<T>(head); }
    Iter<T> end() { return Iter<T>(nullptr); }
};
//------------------------------------------------


//--------------ListMethods------------------------
template <typename T>
T List<T>::operator[] (size_t index)
{

    T value = find(index)->get();
    return value;
}

template <typename T>
List<T> &List<T>::operator= (const List<T>  &r)
{
    if(&r == this)
        return *this;
    return this->head.get() = r->head.get() ;
}

template <typename T>
bool List<T>::is_empty() 
{
   return !head;
}

template <typename T>
size_t List<T>::get_size()
{
    size_t count = 0;
    Elem<T> *tmp = head;
    while(tmp){
        tmp = tmp->next;
        count++; 
    }
    return count;
}

template <typename T>
Elem<T> *List<T>::find(size_t index)
{
    Elem<T> *tmp = head;
    int i = 0;
    while (tmp){
        if (index == i) return tmp;
        tmp = tmp->next;
        i++;
    }
    cerr << "Error in find: the index was not found" << endl;
    exit(1); 
}

template <typename T>
void List<T>::insert_after(T value, size_t index)
{
    index += 1;
    if( is_empty()){
        insert_head(value);
    }
    else if( index >= get_size() ){
        insert_tail(value);
    }
    else if( index < get_size() ){ 
        Elem<T> *tmp = find(index-1);
        Elem<T> *newElem = new Elem<T>(value, tmp->next, tmp);
        // newElem->next = tmp->next;
        // newElem->prev = tmp;
        tmp->next = newElem;
    }
    
}

template <typename T>
void List<T>::insert_head (T value)
{
    Elem<T> *newElem = new Elem<T>(value);
    if ( is_empty() ){ 
        head = newElem;
        tail = newElem;
    }    
    else {
        head->prev = newElem;
        newElem->next = head;
        head = newElem;
    }
}

template <typename T> 
void List<T>::insert_tail(T value) 
{
    if ( is_empty () ){ 
        insert_head(value);   
    }
    else{
        Elem<T> *newElem = new Elem<T>(value,nullptr,tail);
        // newElem->prev = tail;
        tail->next = newElem;
        tail = newElem;
    }
}

template <typename T> 
void List<T>::delete_elem(size_t index) 
{
    Elem<T> *del = head;
    if ( !is_empty() ){
        Elem<T> *del = find (index);
        if(index == 0){ // del == head 
            if(get_size() == 1){ // del == head == tail, index - checked
                head->next = nullptr;
                head->prev = nullptr;
                head = tail = nullptr; 
                delete del;
                return;
            }
            else {
                del->next = head->next;
                head = del->next;
            }
        }
        else if(index < get_size()){
            if (index == get_size()-1){  // del == tail
                tail = del->prev;
                if(get_size() == 2){  // 2 elem : no del->prev->prev
                    cout << "che" <<endl;
                    head = tail;
                }
                else {
                    tail->prev = del->prev->prev;
                }
            }
            else {
                del->prev->next = del->next;
                del->next->prev = del->prev;                   
            }
        }
        tail->next = nullptr;
        delete del;
    }
    else {cerr << "delete_elem: The list is empty\n"; exit(1);}
}

template <typename T> 
List<T>::~List()
{ 
    cout << "Destructor was called\n";
    if( !is_empty() ){
        while ( head ){
            tail = head->next;
            delete head;
            head = tail;
        }
    }    
    else { cerr << "destructor : The list is already empty" << endl; exit(1); }
}

template <typename T> 
void List<T>::print()
{
    if(is_empty()) {cout << "The list is empty" << endl; return;}
    Elem <T> *tmp = head;
    cout << "[ ";
    while(tmp){
        cout << tmp->info << " ";
        tmp = tmp->next;
    }
    cout << "]"<<endl;
    // cout << "   head = " << get_head()() << "   tail = " << get_tail() << endl;
}  
//----------------------------------------------------

#endif //LIST_HPP