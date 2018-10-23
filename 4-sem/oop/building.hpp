#ifndef BUILDING
#define BUILDING

#include <iostream>
#include <fstream>
#include "object.hpp"
// #include "list.hpp"
#include <vector>

using namespace std;

//--------------------------------------WARRIOR-------------------------------------------
class Building : public Object{
    vector<pair<int, int>> location;

public:
    Building(shared_ptr<Crown> crown, istream &in);
    ~Building();

    // void print_ob_simple();
    char draw() override;    

    friend istream &operator>>(istream &in, Building &bd);
    friend ostream &operator<<(ostream &out, Building &bd);
};
//-----------------------------------------------------------------------------------------


//---------------------------------WARRIOR-METHODS------------------------------------------
Building::Building(shared_ptr<Crown> crown, istream &in): 
                Object(crown, in){
    in >> *this;
    cout << "Building:"<< endl;
    int count = 0; 
    for(const auto &coord: location){
        cout <<"    x" << count << " = " << get<0>(coord) << endl;
        cout <<"    y" << count << " = " << get<1>(coord) << endl;
    }
    cout << "Building." <<endl; 
}

Building::~Building() {
    cout << "~Building:"<< endl;
    int count = 0; 
    for(const auto &coord: location){
        cout <<"    x" << count << " = " << get<0>(coord) << endl;
        cout <<"    y" << count << " = " << get<1>(coord) << endl;
    }
    cout << "~Building." <<endl; 
}

istream &operator>>(istream &in, Building &bd){
    int coord_amount;
    in >> coord_amount;
    for(int i = 0; i < coord_amount; i++){
        int x, y;
        in >> x >> y;
        auto p = make_pair(x, y);
        bd.location.push_back(p);
    }
}

char Building::draw() {
    if(alive()) return 'b'; 
    else if(!alive()) return 'x';
} 

ostream &operator<<(ostream &out, Building &bd){
    if(bd.getcrown()->getcolor() ==  "green" ) 
        out << "\033[32m";
    if(bd.getcrown()->getcolor() == "red")
        out << "\033[31m";
    out << bd.draw() << "\033[0m";
    return out;
}   

// void Building::print_ob_simple() { 
//     cout << "[ " << getmark() << " " << getid() << " " << getx() << " " << gety() << " " << gethp() << " " ;
//     int count = 0; 
//     for(const auto &coord: location){
//         cout << get<0>(coord) << " " << endl;
//         cout << get<1>(coord) << " " << endl;
//     }
//     cout << " ]" << endl; 
// }

//-----------------------------------------------------------------------------------------


#endif // BUILDING