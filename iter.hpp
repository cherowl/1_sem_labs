#ifndef ITER_HPP
#define ITER_HPP
#include <iostream>
#include "list.hpp"

using namespace std;

template <typename T> class ELem;
template <typename T> class List;

//-------------------Iterator-------------------------
template <typename T>
class Iter{    
    friend class List<T>; 
    friend class Elem<T>;               
    Elem<T> *elm; 

public:
    Iter(Elem<T> *ptr) : elm(ptr) {};
    
    Elem<T> &operator*();
    Elem<T> *operator->();
    Iter operator++(); 
    Iter operator--();
    bool operator!=(Iter const& r);
    Iter &operator=(const Iter  &r);
};
//------------------------------------------------


//-------------------IteratorMethods-------------------------
template <typename T>
Elem<T> &Iter<T>::operator*()  { return *elm; }

template <typename T>
Elem<T> *Iter<T>::operator->() { return elm; }

template <typename T>
Iter<T> Iter<T>::operator++()
{
    // if (p_list->is_empty() || p_list->get_size() == 1) {
    //     cerr << "It isn't available to increment 0 or 1 object" << endl; return;
    // }
    // if (iter == p_list->get_size()-1){
    //     cerr << "It isn't available to increment the latest element" << endl; return;
    // }
    if(elm) elm = elm->next;
    return *this;
}

template <typename T>
Iter<T> Iter<T>::operator--()
{
    //  if (is_empty() || get_size() == 1) {
    //     cerr << "It isn't available to decrement 0 or 1 object" << endl; return;
    // }
    // if (iter == 0){
    //     cerr << "It isn't available to decrement the first element" << endl; return;
    // }
    if(elm) elm = elm->prev;
    return *this;
}

template <typename T>
Iter<T> &Iter<T>::operator=(const Iter<T>  &r)
{
    //Если попытка сделать объект равным себе же, просто возвращаем указатель на него
    if(&r == this)
        return *this;
    return Iter(this.get() = r.get());
}

template <typename T>
bool Iter<T>::operator!=(Iter<T> const& r)
{
    std::cout << "op!=" << std::endl;
    return !(elm == r.elm);
}

//------------------------------------------------

#endif //ITER_HPP