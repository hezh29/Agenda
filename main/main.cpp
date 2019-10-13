#include"Storage.hpp"
#include<iostream>


using namespace std;

int main(){

    auto storage = Storage::getInstance();
    cout << storage->updateMeeting([](const Meeting a) -> bool{if(a.getSponsor()[0] == 'G')return true;return false;}, [](Meeting &a) -> void{a.setTitle("p");});

    // for(auto i : us){
    // cout << i.getSponsor() << endl;

    //     for(auto p : i.getParticipator()){
    //         cout << p << endl;
    //     }
    // cout << Date::dateToString(i.getStartDate()) << endl;

    // cout << Date::dateToString(i.getEndDate()) << endl;
    // cout << i.getTitle() << endl<<endl;
    // }

    Meeting m;
    
    // m.setSponsor("Geralt of Rivia");
    // m.setParticipator({"Naked Snake","Lara Croft"});
    // m.setStartDate(Date("2016-07-10/15:00"));
    // m.setEndDate({"2016-07-10/18:00"});
    // m.setTitle("Want a few rounds of Gwent?");
    //  storage->createMeeting(m);
    //  cout << storage->sync();

    return 0;
}
