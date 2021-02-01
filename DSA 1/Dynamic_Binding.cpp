#include <iostream>
using namespace std;
/* The following code is to 
 * understand STATIC Binding */
class Base{
public:
    void say_hello()const{
        cout<<"Hello-I'm a Base class Object"<<endl;
    }
};
class Derived: public Base{
public:
    void say_hello()const{
        cout<<"Hello-I'm a derived class object"<<endl;
    }
};
void greetings(const Base &obj){
    cout<<"Greetings: ";
    obj.say_hello();
}
int main(){
    Base b; 
    b.say_hello(); //works as expected
    return 0;
    
    Derived d;
    d.say_hello(); //works as expected
    
    greetings(b); //works as expected
    greetings(d); //DOESNOT work as expected due to static binding
}