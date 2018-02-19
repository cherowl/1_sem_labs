// Шаблонный линейный двунаправленный список со вставкой элементов в начало
#include <iostream>

using namespace std;


//------------------List--------------------------
template <typename T>
class List
{   
    template <typename T1>
    struct Elem{
	    T1 info;
        Elem* next;
	    Elem* prev;

        Elem(T1 value){
            Elem* next = nullptr;
	        Elem* prev = nullptr;
            T1 info = value;
            cout << "New node was created: " << info << endl;
        }
    };

    Elem <T>* head; 
    Elem <T>* end;
    int size;

public: 
    List(){
        head = nullptr;
        end = nullptr;
        size = 0;
    }
    ~List(){
        remove_all();
    }
    bool is_empty();  
    size_t get_size();
    bool set(T value, size_t index);
    bool insert_head (T value);
    bool insert_tail (T value);
    bool remove_elem();
    void remove_all();
    void print(); 
};
//------------------------------------------------


//-----------------MAIN----------------------------
int main(){
    class List <int> list();
    if (list.is_empty()) cout << "Empty!" <<endl;

}
//------------------------------------------------



//--------------ListMethods------------------------
template <typename T>
bool class List <T>::is_empty() // 0 - not empty, 1 - empty 
{
    return head;
}

template <typename T>
size_t class List <T>::get_size()
{
    return size;
}

template <typename T>
bool class List <T>::set(T value, size_t index)
{
    // Iter i(head); 
    // i.find(index);

}

template <typename T>
bool class List <T>::insert_head (T value)
{
    // Elem <T>* tmp = head;
    // Elem <T>* newElem = new Elem(value);
    // if ( is_empty () ){ 
    //     newElem->next = tail;
    //     newElem->prev = head;
    //     head->next = newElem; 
    //     return 0;    
    // }    

    // if ( !is_empty() ){
    //     newElem->next = head->next;  // elem that was the first

    // }
    // int len = get_size();
    // if ( !(cur->prev) ){
    //     newElem->next = cur;
    //     head = newElem;
    //     cur = newElem;
    //     return 0;
    // }
    // Elem* tmp = cur->prev;
    // newElem->next = cur->next;
    // newElem->prev = cur->prev;       
    // tmp->next = newElem;
    // cur = newElem; 
    // return 0;
}

template <typename T> 
bool class List <T>::insert_tail(T value) //0 - success, 1 - err
{
//     Elem <T>* newElem =  new Elem(value); // (?) is it equvailent : new Elem and creating new object of class Elem
//     if ( is_empty () ){ // list is empty - so, adding the value to the begging
//         head = newElem;
//         cur = newElem; 
//         return 0;    
//     }
//     newElem->next = cur->next;
//     newElem->prev = cur;

//     if ( cur->next )        
//          cur->next->prev = newElem;

//     cur->next = newElem;
//     cur = newElem; 
//    return 0;
}

template <typename T> 
bool class List <T>::remove_elem() //0 - success, 1 - err
{
    // Elem <T>* tmp = head;
    // if ( is_empty () ) return -1;
    // Elem* next = cur++;
    // Elem* prev = cur--;
    // Elem* del = cur;
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
void class List <T>::remove_all()
{
    // Elem <T>* tmp = head;
    // while ( tmp ){
    //     tmp->next = tmp->next->next;
    //     tmp->next->prev = 
    //     tmp->prev = nullptr;

    // }

}

template <typename T> 
void class List <T>::print()
{
    Elem* p = head;
    cout << "[ ";
    while( p ){
        cout << p* << " ";
        p++;
    }
    cout << "]" << endl;
}  
//----------------------------------------------------
