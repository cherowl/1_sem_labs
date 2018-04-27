#include <typeinfo> // cout << typeid(...).name()
#include "field.hpp"

using namespace std;

int Object::count_ob;
int Object::cur_amount;

void cinclear()
{
    cin.clear(ios::goodbit); // if the latest input was wrong - flushing bufer
    cin.ignore(65535, '\n');
}

int menu()
{
    char choice;
    int key = 1;
    while(key){
        cout << "Would you like to load data from file? (y/n)\n";
        cin >> choice;
        if (choice == 'y') { key = 0; return 1; }
        if(choice == 'n') { key = 0; return 0; }
        else { cout << "ERROR! Incorrect input, try again.\n"; continue; }
    }
}

int check_for_win(Field &fd){
// // 0 - red won, 1- green won, -1 - continue game
//     int red_total = fd.getlist()->get_size(); //cout<<"red_ "<<red_total<<endl;
//     int green_total = fd.getlist()->get_size();    

//     for(auto& elem: *(fd.getlist()[0])){
//         if(!elem.get()->alive()) 
//             red_total--;
//     }
//     for(auto& elem: *(fd.getlist()[1])){
//         if(!elem.get()->alive()) 
//             green_total--;
//     }   
//     if(!green_total) 
//             return 1;
//     if(!red_total) 
//             return 0;
//     return -1; // continue gamme   
}

//-----------------MAIN----------------------------
int main()
{
    filebuf filename;
    auto flagfile = filename.open("input_new", ios::in);
    if(!flagfile){ cout << " ERROR with file!\n "; exit(1); }
    istream fin(&filename);
    //ifstream fin("file");
   
    int x_load = 0;
    int y_load = 0;
    int army_number = 0;
       
    Field fd;
    fin >> fd;   
    fd.print_field(cout);
    cout << "See the list :\n"; fd.print_list();

    int exit_key = 0; // all is good
    int flag = 0;
    int finish = 0;
    
    // int flag_exit = 0;
    // while(!flag_exit){
        int a = 0, x = 0, y = 0, ind = 0;
        char c[1];
        int flag_finish = 0;
        while(!flag_finish){
            cinclear();
            // string army;
            // cout << "Select the army (red/green): " <<endl; 
            // cin >> army;
            cout << "Select a target (enter x y - unsigned int numbers separated by space) or q to exit: " << endl;
            cin >> c[0];
            if ( *c == 'q') {flag_finish = 1; break;}    
            x = atoi(c); 
            cin >> y;
            ind = fd.find_ob_index(x,y);
            if(ind == -1) { 
                cout << "Selected target wasn't found. Try again (maybe inccorect input)." <<endl; 
                cin.clear(); continue;
            }
            if (fd.is_obj(x,y) == 1) {
                cout << "Selected target is ";
                char action;
                switch(fd.get_obj(x,y)->getmark()){
                    case 'o':
                        cout << "object.\nPress i to see the information [q to quit]: \n";   
                        cin >> action;
                        switch(action){
                            case 'q': 
                                flag_finish = 1; 
                                break;
                            case 'i':
                                cout << "Hit points: " << fd.get_obj(x,y)->gethp() << endl;
                                cout << "Army it belongs to: " << fd.get_obj(x,y)->getcrown()->getcolor() << endl;
                                break;
                            default:
                                exit_key = 1; //cout <<"Unknown command\n";
                                break;
                        }
                        break;
//fix warrior info
                    case 'w':
                        cout << "warrior.\n";
                        while(!finish){
                            cin.clear();
                            cout << "To attack press 'a', 'm'-to move, to see the info-'i' [any other button to finish]: ";
                            cin >> action; cout <<"yeeoeo: " << action<<endl;
                            switch(action){
                            case 'i':
                                cout << "Hit points: " << fd.get_obj(x,y)->gethp() << endl;
                                cout << "Power: " << fd.get_obj(x,y)->getpower() << endl;                                
                                cout << "Army it belongs to: " << fd.get_obj(x,y)->getcrown()->getcolor() << endl;
                                break;
                            case 'm':                      
                                cout << "To move it up press 'u', down-'d', right-'r', left-'l': ";
                                if (fd.get_obj(x,y)->move_to()==-1) break; 
                                cout << endl << fd;
                                break;
// fix attack
                            case 'a':
                                fd.get_obj(x,y)->attack();
                                cout << fd;
                                break;

                            default:
                                break;
                        }
                    }
                    break;
                    case 'b':
                        cout << "building.\nPress i to see the information [q to quit]: \n";   
                        char action;
                        cin >> action;
                        switch(action){
                            case 'q': 
                                flag_finish = 1; 
                                break;
                            case 'i':
                                cout << "Hit points: " << fd.get_obj(x,y)->gethp() << endl;
                                cout << "Army it belongs to: " << fd.get_obj(x,y)->getcrown()->getcolor() << endl;
                                break;
                            default:
                                exit_key = 1; //cout <<"Unknown command\n";
                                break;
                        }                   
                        break;
                    default:
                        exit_key = 1; //cout <<"Unknown behavior\n";
                        flag_finish = 1;
                        break;
                }
            } else {
                cout << "No: doesn't exist or was killed.\n"; 
                flag_finish = 1;
            }
        }

 //fix   
    // int check = check_for_win(fd);
    // if(check == 1) {cout << "\n!!!The red army won!!!\n"; break; }
    // else if(check == 0){cout << "\n!!!The green army won!!!\n"; break;}
    // else continue;

//     while(1){
//         // cinclear();
//         cout << "Continue or quit? (c/q): ";
//         char switch_on;
//         cin >> switch_on; 
//         if (switch_on == 'c') break;
//         else if (switch_on == 'q') { flag_exit = 1; break;}
//         else { cout << "ERROR! Incorrect input, try again.\n"; cinclear(); continue; }
//     }
// }

// fix coments for exit
    cout << "Exit key: " << exit_key << endl;
    // file.close();
    filename.close();
    return 0;   
}
//------------------------------------------------

//fix hp<0