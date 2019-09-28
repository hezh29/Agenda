#include"User.hpp"
#include<iostream>

using namespace std;

int main(){
    User u("a", "b", "c", "d");
    cout << u.getEmail() << u.getName() << u.getPassword() << u.getPhone()<< endl;
    return 0;
}
