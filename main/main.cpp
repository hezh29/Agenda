#include"User.hpp"
#include"Meeting.hpp"
#include"Date.hpp"
#include<iostream>


using namespace std;

int main(){


    cout << Date::isValid(Date("1000-10-10/00:00"));
    return 0;
}
