#include"User.hpp"
#include"Meeting.hpp"
#include"Date.hpp"
#include<iostream>


using namespace std;

int main(){
   Meeting m;
    m.addParticipator("m");
    m.addParticipator("m");
    m.addParticipator("n");
    m.removeParticipator("m");

    cout << m.isParticipator("n");
    return 0;
}
