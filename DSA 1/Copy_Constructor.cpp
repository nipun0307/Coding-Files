#include <iostream>
using namespace std;
#include <string>
class Player{
public:
    string name;
    int health;
    int xp;
    string get_name(){return name;}
    int get_health(){return health;}
    int get_xp(){ return xp;}
    Player(string name_val="None",int health_val=0, int xp_val=0);
    //copy constructor
    Player(const Player &source);
    //Destructor
    ~Player();
};
Player::Player(string name_val,int health_val,int xp_val)
    : name{name_val},health{health_val},xp{xp_val}{}

Player::Player(const Player &source)
    :name{source.name},health{source.health},xp{source.xp}{}
void display_player(Player p){
    cout<<"Name: "<<p.get_name()<<endl;
    cout<<"Health: "<<p.get_health()<<endl;
    cout<<"XP: "<<p.get_xp()<<endl;
}
//nt main(){
  //  display_player(empty);
    