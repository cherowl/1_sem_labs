// Шаблонный линейный двунаправленный список со вставкой элементов в начало
#include <iostream>

using namespace std;


//--------------Elem------------------------------
template <typename T>
class Elem{
public:
    T info;
    Elem* next;
    Elem* prev;
    Elem(T info = decltype(info)(0), Elem *next = nullptr, Elem *prev=nullptr) : info(info), next(next),prev(prev) {}
    T& get_info(){ return info; }
    const T& get_info() const { return info; }
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
    List() : head (nullptr), tail(nullptr) {};
    ~List();
    
    bool is_empty();  
    size_t get_size();
    Elem<T> * get_head();
    T& get_tail();    
    // Elem<T> *init(T value);
    Elem<T> *find(size_t index);
    void insert_after(T value, size_t index);
    void insert_head (T value);
    void insert_tail (T value);
    void delete_elem(size_t index);
    void print(); 
    T operator [] (size_t index);
};
//------------------------------------------------


//-------------------Iterator-------------------------
template <typename T>
class Iter{    
    friend List<T>;                                                                                         
    List<T> *p_list;     
    size_t iter; 

public:
    Iter(List<T> *ptr) : p_list(ptr), iter(0) {};
    T operator*();
    List<T> *operator->();
    void operator++(int);
    void operator--(int);
};
//------------------------------------------------


//-------------------IteratorMethods-------------------------
template <typename T>
T Iter<T>::operator*()  
{ 
    T val = p_list->find(iter)->get_info();
    return val;  
}   

template <typename T>
List<T> *Iter<T>::operator->() 
{ 
    return p_list;
}

template <typename T>
void Iter<T>::operator++(int)
{
    if (p_list->is_empty() || p_list->get_size() == 1) {
        cerr << "It isn't available to increment 0 or 1 object" << endl; return;
    }
    if (iter == p_list->get_size()-1){
        cerr << "It isn't available to increment the latest element" << endl; return;
    }
    static Elem<T> *tmp = p_list->get_head();
    tmp = tmp->next;
    iter++;
}

template <typename T>
void Iter<T>::operator--(int)
{
     if (p_list->is_empty() || p_list->get_size() == 1) {
        cerr << "It isn't available to decrement 0 or 1 object" << endl; return;
    }
    if (iter == 0){
        cerr << "It isn't available to decrement the first element" << endl; return;
    }
    static Elem<T> *tmp = p_list->get_head();
    tmp = tmp->prev;
    iter--;
}
//------------------------------------------------


//--------------ListMethods------------------------
template <typename T>
T List<T>::operator[] (size_t index)
{

    T value = find(index)->get_info();
    return value;
}

// template <typename T>
// Elem<T> *List<T>::init(T value)
// {
//     Elem<T> *p = new Elem<T>; 
//     p->info = value;
//     p->next = nullptr;
//     p->prev = nullptr;
//     return p;
// }

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
Elem<T> *List<T>::get_head()
{
    return head;
}

template <typename T>
T& List<T>::get_tail()
{
    return tail->get_info();
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
    // cout << "   head = " << get_head() << "   tail = " << get_tail() << endl;
}  
//----------------------------------------------------


//-----------------MAIN----------------------------
int main(){
    List <int> list;
    for (int i = 0; i < 1; i++){
        list.insert_head(i);
    }
    list.print();
    list.insert_tail(222); 
    list.print();  
    list.insert_after(8,1);
    list.print();   
    list.insert_after(299,299);
    list.print();    
    list.insert_after(2002, 0);    
    list.print();
    list.insert_head(333);    
    list.print();        
    list.delete_elem(2);   
    list.print(); 

    cout<< list[0] <<endl;

    // for( List<int> &elem : list){
    //     elem++;
    // }

    
    // int i;
    // Iter<int> iter(&list);
    // for (i = 0; i<3; i++){
    //     // iter++;
    //     cout << iter[i] << endl;
    // }

    
}
//------------------------------------------------

    