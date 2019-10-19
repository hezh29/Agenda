#include"AgendaService.hpp"

AgendaService::AgendaService(){
    m_storage = Storage::getInstance();
}

AgendaService::~AgendaService(){
    m_storage->sync();
}

bool AgendaService::userLogIn(const std::string &userName, const std::string &password){
    auto users = m_storage->queryUser(
        [&](const User & user) -> bool {
            if(user.getName() == userName){
                if(user.getPassword() == password){
                    return true;
                }
            }

            return false;
        }
    );

    if(users.size() == 1){
        return true;
    }
    else{
        return false;
    }
}

bool AgendaService::userRegister(const std::string &userName, const std::string &password, const std::string &email, const std::string &phone){
    auto users = m_storage->queryUser(
        [&userName](const User & user) -> bool {
            if(user.getName() == userName){
                return true;
            }

            return false;
        }
    );

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
        m_storage->updateMeeting(
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
            }
        );

        m_storage->deleteMeeting(
            [&userName](const Meeting & meeting) -> bool{
                if(meeting.getSponsor() == userName){
                    return true;
                }
                else if(meeting.getParticipator().size() == 0){
                    return true;
                }
                else{
                    return false;
                }
            }
        );

        m_storage->deleteUser(
            [&userName](const User &user) -> bool{
                if(user.getName() == userName){
                    return true;
                }
                else{
                    return false;
                }
            }
        );

        return true;

    }
    else{
        return false;
    }
}

std::list<User> AgendaService::listAllUsers(void) const{
    auto users = m_storage->queryUser([](const User &user) -> bool{return true;});

    return users;
}



bool AgendaService::createMeeting(const std::string &userName, const std::string &title, const std::string &startDate, const std::string &endDate, const std::vector<std::string> &participator){
        
    auto m_participator = participator;

    if(!(Date::isValid(startDate) && Date::isValid(endDate)) || Date(startDate) >= Date(endDate)){
        return false;
    }

    auto users = m_storage->queryUser(
        [&userName](const User &user) -> bool{
            if(user.getName() == userName){
                return true;
            }
            else{
                return false;
            }
        }
    );

    for(auto i = m_participator.begin(); i != m_participator.end();){

        if(userName == *i){
            i = m_participator.erase(i);
            continue;
        }

        for(auto j = i + 1; j != participator.end();){
            if(*j == *i){
                j = m_participator.erase(j);
            }
            else{
                j++;
            }
        }

        auto p_users = m_storage->queryUser(
            [&i](const User &user) -> bool{
                if(user.getName() == *i ){
                    return true;
                }
                else{
                    return false;
                }
            }
        );

        if(p_users.size() == 0){
            i = m_participator.erase(i);
            continue;
        }

        i++;
    }


    auto meetings = m_storage->queryMeeting(
        [&](const Meeting &meeting) -> bool{
            if(title == meeting.getTitle()){
                return true;
            }
            else if(meeting.getSponsor() == userName || meeting.isParticipator(userName)){
                if(!(meeting.getEndDate() <= startDate || meeting.getStartDate() >= endDate)){
                    return true;
                }
            }
            else{
                for(auto p_user : m_participator){
                    if(meeting.getSponsor() == p_user || meeting.isParticipator(p_user)){
                        if(!(meeting.getEndDate() <= startDate || meeting.getStartDate() >= endDate)){
                            return true;
                        }
                    }
                }
            }

            return false;
        }
    );

    if(users.size() != 0 && meetings.size() == 0 && m_participator.size() != 0){
        m_storage->createMeeting(Meeting(userName, m_participator, startDate, endDate, title));
    }
    else{
        return false;
    }
}

bool AgendaService::addMeetingParticipator(const std::string &userName, const std::string &title, const std::string &participator){

    auto meetings = m_storage->queryMeeting(
        [&participator](const Meeting meeting) -> bool{
            if(meeting.getSponsor() == participator || meeting.isParticipator(participator)){
                return true;
            }
            else{
                return false;
            }
        }
    );

    auto count = m_storage->updateMeeting(
        [&userName, &title, &participator, &meetings](const Meeting & meeting) -> bool{
            if(userName == meeting.getSponsor() && title == meeting.getTitle() && !(meeting.isParticipator(participator)) && !(meeting.getSponsor() == participator)){
                for(auto m : meetings){
                    if(meeting.getStartDate() < m.getEndDate() && meeting.getEndDate() > m.getStartDate()){
                        return false;
                    }
                }

                return true;
            }
            else{
                return false;
            }
        }, 
        [&participator](Meeting &meeting) -> void{
            meeting.addParticipator(participator);
        }
    );


    if(count != 0){
        return true;
    }
    else{
        return false;
    }
}

bool AgendaService::removeMeetingParticipator(const std::string &userName, const std::string &title, const std::string &participator){
    auto count = m_storage->updateMeeting(
        [&userName, &title, &participator](const Meeting & meeting) -> bool{
            if(userName == meeting.getSponsor() && title == meeting.getTitle() && meeting.isParticipator(participator)){
                return true;
            }
            else{
                return false;
            }
        }, 
        [&participator](Meeting &meeting) -> void{
            meeting.removeParticipator(participator);
        }
    );

    m_storage->deleteMeeting(
        [](const Meeting & meeting) -> bool{
            if(meeting.getParticipator().size() == 0){
                return true;
            }
            else{
                return false;
            }
        }
    );

    if(count != 0){
        return true;
    }
    else{
        return false;
    }
}

bool AgendaService::quitMeeting(const std::string &userName, const std::string &title){
    auto count = m_storage->updateMeeting(
        [&userName, &title](const Meeting & meeting) -> bool{
            if(title == meeting.getTitle() && meeting.isParticipator(userName)){
                return true;
            }
            else{
                return false;
            }
        }, 
        [&userName](Meeting &meeting) -> void{
            meeting.removeParticipator(userName);
        }
    );

    m_storage->deleteMeeting(
        [](const Meeting & meeting) -> bool{
            if(meeting.getParticipator().size() == 0){
                return true;
            }
            else{
                return false;
            }
        }
    );

    if(count != 0){
        return true;
    }
    else{
        return false;
    }
}

std::list<Meeting> AgendaService::meetingQuery(const std::string &userName, const std::string &title) const{
    return m_storage->queryMeeting(
        [&userName, &title](const Meeting meeting) -> bool{
            if(title == meeting.getTitle() && (userName == meeting.getSponsor() || meeting.isParticipator(userName))){
                return true;
            }
            else{
                return false;
            }
        }
    );
}

std::list<Meeting> AgendaService::meetingQuery(const std::string &userName, const std::string &startDate, const std::string &endDate) const{
    if(Date::isValid(startDate) && Date::isValid(endDate) && Date(startDate) <= Date(endDate)){
        auto meetings = m_storage->queryMeeting(
            [&userName, &startDate, &endDate](const Meeting meeting) -> bool{
                if((meeting.getStartDate() <= endDate && meeting.getEndDate() >= startDate) && (userName == meeting.getSponsor() || meeting.isParticipator(userName))){
                    return true;
                }
                else{
                    return false;
                }
            }
        );

        return meetings;
    }
    else{
        return std::list<Meeting>();
    }
}

std::list<Meeting> AgendaService::listAllMeetings(const std::string &userName) const{
    auto meetings = m_storage->queryMeeting(
        [&userName](const Meeting meeting) -> bool{
            if(userName == meeting.getSponsor() || meeting.isParticipator(userName)){
                return true;
            }
            else{
                return false;
            }
        }
    );

    return meetings;
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string &userName) const{
    auto meetings = m_storage->queryMeeting(
        [&userName](const Meeting meeting) -> bool{
            if(userName == meeting.getSponsor()){
                return true;
            }
            else{
                return false;
            }
        }
    );

    return meetings;
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(const std::string &userName) const{
    auto meetings = m_storage->queryMeeting(
        [&userName](const Meeting meeting) -> bool{
            if(meeting.isParticipator(userName)){
                return true;
            }
            else{
                return false;
            }
        }
    );

    return meetings;
}

bool AgendaService::deleteMeeting(const std::string &userName, const std::string &title){
    auto count = m_storage->deleteMeeting(
        [&userName, &title](const Meeting meeting) -> bool{
            if(meeting.getSponsor() == userName && meeting.getTitle() == title){
                return true;
            }
            else{
                return false;
            }
        }
    );

    if(count != 0){
        return true;
    }
    else{
        return false;
    }
}

bool AgendaService::deleteAllMeetings(const std::string &userName){
    auto count = m_storage->deleteMeeting(
        [&userName](const Meeting meeting) -> bool{
            if(meeting.getSponsor() == userName){
                return true;
            }
            else{
                return false;
            }
        }
    );

    if(count != 0){
        return true;
    }
    else{
        return false;
    }
}

void AgendaService::startAgenda(void){}
void AgendaService::quitAgenda(void){
    m_storage->sync();
}