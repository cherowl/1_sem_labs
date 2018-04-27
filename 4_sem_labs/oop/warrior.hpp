#ifndef WARRIOR
#define WARRIOR

#include <iostream>
#include <fstream>
#include "object.hpp"

using namespace std;


//--------------------------------------WARRIOR-------------------------------------------
class Warrior : public Object{
    int power;

public:
    Warrior(shared_ptr<Crown> crown, istream &in);
    ~Warrior();

    int move_to() override;
    int attack() override;
    int &getpower() override;
    // void print_ob_simple();
    
    char draw() override;

    friend istream &operator>>(istream &in, Warrior &wr);
    friend ostream &operator<<(ostream &out, Warrior &wr);
};
//-----------------------------------------------------------------------------------------


//---------------------------------WARRIOR-METHODS------------------------------------------
Warrior::Warrior(shared_ptr<Crown> crown, istream &in): Object(crown, in) {
    in >> *this;
    cout << "Warrior:"<< endl 
         << "    power = " << this->power << endl
         << "Warrior." <<endl; 
}

Warrior::~Warrior() {
    cout << "~Warrior:"<< endl 
         << "    power = " << this->power << endl
         << "~Warrior." <<endl; 
}

char Warrior::draw(){
    if(alive()) return 'w'; 
    else if(!alive()) return 'x';
} 

istream &operator>>(istream &in, Warrior &wr){
    in >> wr.power;
}

ostream &operator<<(ostream &out, Warrior &wr){
    if(wr.getcrown()->getcolor() ==  "green" ) 
        out << "\033[32m";
    if(wr.getcrown()->getcolor() == "red") 
        out << "\033[31m";
    out << wr.draw() << "\033[0m";
    return out;
} 

int Warrior::move_to(){
    char action;
    cin >> action;
    switch(action){
        case 'u':
            gety() += 1;
            break;
        case 'd':
            gety() -= 1;
            break;
        case 'r':
            getx() += 1;
            break;
        case 'l':
            getx() -= 1 ;
            break;
        default:
            return -1;//cout << "Incorrect data!" << '\n';
            break;
    }
}
    
int Warrior::attack(){
    // for(auto &ob: getlist()){
    //     if(ob.x = getx() && ob.y == gety()){
    //         ob.hp -= power;
    //         return 0;
    //     }
    // }
    // return -1; // no target
}

// void Warrior::print_ob_simple(){ 
//     cout << "[ " << getmark() << " " << getid() << " " << getx() << " " << gety() << " " << gethp() << " " << power << " ]" << endl; 
// }

int &Warrior::getpower()
    {return this->power;}


//-----------------------------------------------------------------------------------------


#endif // WARRIOR