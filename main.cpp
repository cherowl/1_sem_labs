// Шаблонный линейный двунаправленный список со вставкой элементов в начало
#include <iostream>
#include <assert.h>

using namespace std;

//--------------Elem------------------------------
template <typename T>
class Elem{
public:
    T info;
    Elem*next;
    Elem*prev;
};
//-----------------------------------------------


//------------------List--------------------------
template <typename T>
class List
{   
    friend Elem<T>;
    Elem<T> *head; 
    Elem<T> *tail;

public: 
    List(){
        head = nullptr;
        tail = nullptr;
    }
    ~List(){
        remove_all();
    }
    bool is_empty();  
    size_t get_size();
    Elem<T> *init(T value);
    Elem<T> *find(size_t index);
    void set(T value, size_t index);
    void insert_head (T value);
    void insert_tail (T value);
    void remove_elem();
    void remove_all();
    void print(); 
};
//------------------------------------------------


//--------------ListMethods------------------------
template <typename T>
Elem<T> *List <T>::init(T value)
{
    Elem<T> *p = new Elem<T>; 
    p->info = value;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

template <typename T>
bool List <T>::is_empty() 
{
   return !head;
}

template <typename T>
size_t List <T>::get_size()
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
Elem<T> *List <T>::find(size_t index)
{
    Elem<T> *tmp = head;
    int i = 0;
    while (tmp){
        if (index == i) return tmp;
        tmp = tmp->next;
        i++;
    }
    assert('index is not found');
}

template <typename T>
void List <T>::set(T value, size_t index)
{
    if( index == 0 || is_empty()){
        insert_head(value);
    }
    else if( index >= get_size() ){
        insert_tail(value);
    }
    else {
        Elem<T> *newElem = init(value);
        Elem<T> *tmp = find(index);
       
        newElem->next = tmp->next;
        newElem->prev = tmp;
        tmp->next = newElem;
    }
    
}

template <typename T>
void List <T>::insert_head (T value)
{
    Elem<T> *newElem = init(value);
    if ( is_empty() ){ 
        head = newElem;
    }    
    else {
        newElem->next = head->next;
        newElem->prev = head;
        head->next = newElem;
    }
    tail = newElem;

}

template <typename T> 
void List<T>::insert_tail(T value) 
{
    if ( is_empty () ){ 
        insert_head(value);   
    }
    else{
        Elem<T> *newElem = init(value);
        tail->next = newElem;
    }
}

template <typename T> 
void List <T>::remove_elem() 
{
    // Elem<T> *tmp = head;
    // if ( is_empty () ) return -1;
    // Elem*next = cur++;
    // Elem*prev = cur--;
    // Elem*del = cur;
    // if ( prev ){
    //     prev->next = next;
    //     cur = prev;
    // }
    // else if ( !prev){
    //     head = next;
    //     cur = next;
    // }
    // if ( next ){
    //     next->prev = prev;
    //     cur = next;
    // }
    // free(del);
    // return 0;
}

template <typename T> 
void List <T>::remove_all()
{
    // Elem<T> *tmp = head;
    // if( is_empty() ){
    //     while ( tmp ){
    //         tmp = tmp->next;
    //         delete head;
    //         head = tail;
    //     }
    // }
    if( !is_empty() ){
        while ( head ){
            tail = head->next;
            delete head;
            head = tail;
        }
    }   
    
}

template <typename T> 
void List <T>::print()
{
    Elem <T> *tmp = head;
    cout << "[ ";
    while(tmp){
        cout << tmp->info << " ";
        tmp = tmp->next;
    }
    cout << "]" << endl;
}  
//----------------------------------------------------


//-----------------MAIN----------------------------
int main(){
    List <int> list;

    list.insert_head(4);
    cout << list.get_size() << endl;
    list.print();
    
    list.insert_tail(55);
    list.print();
    list.set(8,1);
    list.print();
    list.remove_all();
    list.print();    
    list.insert_head(3);
    list.insert_tail(55);
    list.print();
    
}
//------------------------------------------------

