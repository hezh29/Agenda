#include"AgendaService.hpp"
#include"Storage.hpp"
#include<iostream>


using namespace std;

int main(){
    // auto s = Storage::getInstance();

    // for(auto i:s->queryMeeting([](const Meeting & m)->bool{return true;})){
    //     cout<<i.getTitle()<<endl;
    //     for(auto j:  i.getParticipator()){
    //         cout << j<<endl;
    //     }
    //     cout<<endl;
    // }
    // int k;
    // cin>>k;

    AgendaService m_service;

    // m_service.userRegister("na", "pb", "ec", "hd");
    // m_service.userRegister("nb", "pb", "ec", "hd");
    // m_service.userRegister("nc", "pc", "ec", "hd");
    // m_service.userRegister("nd", "pc", "ec", "hd");
    // m_service.userRegister("ne", "pc", "ec", "hd");
    // m_service.userRegister("nf", "pc", "ec", "hd");


    // cout <<m_service.createMeeting("na", "tb", "2016-08-01/00:00", "2016-08-01/12:00", {"nb", "na", "nd"});
    // cout<<m_service.createMeeting("na", "tf", "2026-08-01/00:00", "2026-08-01/12:00", {"nb", "nd", "nc"});
    // cout<<m_service.createMeeting("na", "tg", "2036-08-01/00:00", "2036-08-01/12:00", {"nb", "ng"});

    // cout<<m_service.createMeeting("nc", "tc", "2056-08-01/11:00", "2056-09-01/12:00", { "na"});

    // cout<<m_service.createMeeting("nc", "tt", "2046-08-01/11:00", "2046-09-01/12:00", { "ne" });
    // cout<<m_service.createMeeting("nc", "tca", "204-08-01/11:00", "2046-09-01/12:00", { "na"});
    // cout<<m_service.createMeeting("nc", "tcc", "2086-08-01/11:00", "2076-09-01/12:00", { "na"});
    // cout<<m_service.createMeeting("nc", "tcf", "2046-08-01/11:00", "2046-09-01/12:00", { "na"});
    // cout<<m_service.quitMeeting("na", "tc");
    cout<<m_service.addMeetingParticipator("na", "tf", "ne");



    



    return 0;
}
