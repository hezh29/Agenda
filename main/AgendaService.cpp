#include"AgendaService.hpp"

AgendaService::AgendaService(){
    m_storage = Storage::getInstance();
}

AgendaService::~AgendaService(){

}

bool AgendaService::userLogIn(const std::string &userName, const std::string &password){
    auto users = m_storage->queryUser([&](const User & user) -> bool {
        if(user.getName() == userName){
            if(user.getPassword() == password){
                return true;
            }
        }

        return false;
    });

    if(users.size() == 1){
        return true;
    }
    else{
        return false;
    }
}

bool AgendaService::userRegister(const std::string &userName, const std::string &password, const std::string &email, const std::string &phone){
    auto users = m_storage->queryUser([&userName](const User & user) -> bool {
        if(user.getName() == userName){
            return true;
        }

        return false;
    });

    if(users.size() == 0){
        m_storage->createUser({userName, password, email, phone});
        return true;
    }
    else{
        return false;
    }
}

bool AgendaService::deleteUser(const std::string &userName, const std::string &password){
    if(userLogIn(userName, password)){
        auto meetings =  m_storage->updateMeeting(
            [&userName](const Meeting & meeting) -> bool{
                if(meeting.isParticipator(userName)){
                    return true;
                }
                else{
                    return false;  
                }
            }, 
            [&userName](Meeting & meeting) -> void{
                meeting.removeParticipator(userName);
            });


        m_storage->deleteMeeting([&userName](const Meeting & meeting) -> bool{
            if(meeting.getSponsor() == userName){
                return true;
            }
            else if(meeting.getParticipator().size() == 0){
                return true;
            }
            else{
                return false;
            }
        });

    }
    else{
        return false;
    }
}

