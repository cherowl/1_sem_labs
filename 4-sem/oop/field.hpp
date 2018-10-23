#ifndef FIELD
#define FIELD
#include <vector>
#include "object.hpp"
#include "iter.hpp"
#include "warrior.hpp"
#include "building.hpp"

using namespace std;

class Warrior;

//--------------------------------------FIELD----------------------------------------------
class Field
{

    int x_size;
    int y_size;

    weak_ptr<Crown> crown_red;
    weak_ptr<Crown> crown_green;

    char **map;
    List<Object *> list;

  public:
    // Field( int x_size, int y_size   );
    Field() {}
    ~Field();

    void init();
    void print_field(ostream &out);
    void print_list();
    // void add_to_map(int x, int y);
    void read_file(istream &f);
    Object *get_obj(int x, int y);
    int type_of_point(int x, int y);
    // void check_map();
    bool is_obj(int x, int y);
    int find_ob_index(int x, int y);
    void read_from_file(istream &in);

    List<Object *> &getlist();  
    int &get_x_size();
    int &get_y_size();
    char **getmap();


    // friend int Warrior::attack(Field&);
    friend istream &operator>>(istream &in, Field &fd);
    friend ostream &operator<<(ostream &out, const Field &fd);
};
//-----------------------------------------------------------------------------------------

//---------------------------------FIELD-METHODS-------------------------------------------
void Field::init()
{
    cout << "Field:" << endl
         << "    x_size = " << x_size << endl
         << "    y_size = " << y_size << endl;

    //  create a clean map
    int i = 0;
    map = new char *[y_size];

    for (int i = 0; i < y_size; i++)
    {
        map[i] = new char[x_size];
    }
    for (int i = 0; i < x_size; i++)
    {
        for (int j = 0; j < y_size; j++)
        {
            map[i][j] = '.';
        }
    }
    // //create containers for armies
    //     for(i = 0; i < 2; i++){
    //         List<Object*>* some = new List<Object*>;
    //         list.insert_tail(some);
    //     }
}

// void Field::add_to_map(int x, int y)
//     { map[x][y] = 'o'; }

Field::~Field()
{
    cout << "~Field:" << endl
         << "    x_size = " << x_size << endl
         << "    y_size = " << y_size << endl;
}

bool Field::is_obj(int x, int y)
{
    int index = find_ob_index(x, y);
    if (index == -1)
        return false; // not found
    if (!list[index]->alive())
        list.delete_elem(index);
    else
        return true;
}

Object *Field::get_obj(int x, int y) //map[j][i]-ok
{
    int ind = find_ob_index(x, y);
    if (ind == -1)
        return nullptr;
    return list.find(ind)->get();
}

int Field::find_ob_index(int x, int y)
{
    int count = 0;
    for (const auto &obj : list)
    {
        if (obj.get()->getx() == x && obj.get()->gety() == y)
        {
            return count;
        }
        count++;
    }
    return -1; // not found
}

// int Field::type_of_point(int x, int y)
// {
//     for(auto &obj : list){
//         if(obj.get()->getx() == x && obj.get()->gety() == y)
//             return obj.get()->which_army(); // 0 - green, 1 - red
//     }
//     return -1; //not found
// }

// void Field::check_map()
// {
//     for(auto &cont: list){
//         for(auto &obj : *(cont.get())){
//             if(obj.get()->gethp() <= 0) {
//                 map[obj.get()->gety()][obj.get()->getx()] = 'x';
//             }
//         }
//     }
// }

void Field::print_list()
{
    for (auto &ob : list)
    {
        ob.get()->print_ob_simple();
    }
}

void Field::print_field(ostream &out)
{
    //borders
    out << endl;
    for (int i = 0; i < y_size; i++)
    {
        if (i == 0)
            out << "  ";
        out << i;
    }
    out << endl;
    for (int i = 0; i < y_size; i++)
    {
        if (i == 0 || i == y_size - 1)
        {
            if (i == 0)
                out << "  ";
            out << "+";
        }
        else
            out << "-";
    }
    out << endl;

    //fill field
    for (int i = 0; i < y_size; i++)
    {
        out << i << "|";
        for (int j = 0; j < x_size; j++)
        {
            if (!is_obj(j, i))
                out << '.';
            else{
                out << *get_obj(j, i);
            }
        }
        out << "|" << endl;
    }

    //borders
    for (int i = 0; i < y_size; i++)
    {
        if (i == 0 || i == y_size - 1)
        {
            if (i == 0)
                out << "  ";
            out << "+";
        }
        else
            out << "-";
    }
    out << endl;
    for (int i = 0; i < y_size; i++)
    {
        if (i == 0)
            out << "  ";
        out << i;
    }
    out << endl;
    out << endl;
}

void Field::read_from_file(istream &in)
{
    int flag_init = 0;
    int obj_amount = 0;
    char which_army_mark;
    char type;
    string color;

    // in >> *this;
    for (int j = 0; j < 2; j++)
    {
        in >> obj_amount >> which_army_mark;
        if (which_army_mark == 'r')
            color = "red";
        if (which_army_mark == 'g')
            color = "green";

        for (int i = 0; i < obj_amount; i++)
        {
            static shared_ptr<Crown> tmp;
            if (!flag_init)
            {
                tmp = shared_ptr<Crown>(new Crown(color));
                this->crown_red = tmp;
                flag_init = 1;
            }
            in >> type;
            in.unget();
            Object *ob;
            if (type == 'o') ob = new Object(tmp, in);
            if (type == 'w') ob = new Warrior(tmp, in);
            if (type == 'b') {
                ob = new Building(tmp, in);
            }
            list.insert_tail(ob);
        }
        flag_init = 0;
    }
    cout << "Field.\n";
}

ostream &operator<<(ostream &out, Field &fd)
{
    fd.print_field(out);
    return out;
}

istream &operator>>(istream &in, Field &fd)
{
    in >> fd.x_size >> fd.y_size;
    fd.init();
    fd.read_from_file(in);
    return in;
}

int &Field::get_x_size()
{
    return x_size;
}

int &Field::get_y_size()
{
    return y_size;
}

char **Field::getmap()
{
    return map;
}

List<Object *> &Field::getlist()
{
    return list;
}

//-----------------------------------------------------------------------------------------
#endif //FIELD