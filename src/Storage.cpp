#include<fstream>
#include<regex>
#include"Storage.hpp"
#include"Path.hpp"

std::shared_ptr<Storage> Storage::m_instance = NULL;

Storage::Storage(){
    readFromFile();
    m_dirty = false;
}

bool Storage::readFromFile(void){
    m_userList.clear();
    m_meetingList.clear();

    std::ifstream ifile;

//Meeting    
    ifile.open(Path::meetingPath);

    if(ifile.is_open()) {
        std::string s;
        std::regex format("\"(.*)\",\"(.*)\",\"(.*)\",\"(.*)\",\"(.*)\"");
        std::smatch match; 

        while(std::getline(ifile, s)) {
            Meeting m;
            std::regex_match(s,match,format);
            m.setSponsor(match[1].str());
            std::string s_paticipators = match[2].str();
            m.setStartDate(match[3].str());
            m.setEndDate(match[4].str());
            m.setTitle(match[5].str());
            
            int pos = 0, count = 0;

            while(pos + count < s_paticipators.size()){
                if(s_paticipators.at(pos + count) != '&'){
                    count++;
                }
                else{
                    m.addParticipator(s_paticipators.substr(pos, count));
                    pos = pos + count + 1;
                    count = 0;
                }
            }

            m.addParticipator(s_paticipators.substr(pos, count));

            m_meetingList.push_back(m);
        }

        ifile.close();

    }
    else{
        return false;
    }

//User
    ifile.open(Path::userPath);

    if(ifile.is_open()) {
        std::string s;
        std::regex format("\"(.*)\",\"(.*)\",\"(.*)\",\"(.*)\"");
        std::smatch match; 

        while(std::getline(ifile, s)) {
            std::regex_match(s,match,format);
            m_userList.push_back(User(match[1].str(), match[2].str(), 
                match[3].str(), match[4].str()));
        }

        ifile.close();

    }
    else{
        return false;
    }

    return true;
}

bool Storage::writeToFile(void){
    std::ofstream ofile;
//meeting
    ofile.open(Path::meetingPath);

    if(ofile.is_open()){
        std::string s_meetingList;

        for(auto meeting : m_meetingList){
            s_meetingList += "\"" + meeting.getSponsor() + "\",\"";

            for(auto i : meeting.getParticipator()){
                s_meetingList += i + "&";
            }

            s_meetingList.pop_back();
            s_meetingList += "\",\"" + Date::dateToString(meeting.getStartDate()) + "\",\"" + Date::dateToString(meeting.getEndDate()) + "\",\"" + meeting.getTitle() + "\"\n";

        }
        
        ofile << s_meetingList;

        ofile.close();
    }
    else{
        return false;
    }

// //User
    ofile.open(Path::userPath);


    if(ofile.is_open()){
        std::string s_userList;

        for(auto user : m_userList){
            s_userList += "\"" + user.getName() + "\",\"" + user.getPassword() + "\",\"" + user.getEmail() + "\",\"" + user.getPhone() + "\"\n";
        }

        ofile << s_userList;

        ofile.close();
    }
    else{
        return false;
    }

    return true;
}


std::shared_ptr<Storage> Storage::getInstance(void){
    if(Storage::m_instance.get() == NULL){
        Storage::m_instance.reset(new Storage);
    }

    return Storage::m_instance;
}

Storage::~Storage(){
    writeToFile();
}

void Storage::createUser(const User &t_user){
    m_userList.push_back(t_user);
    m_dirty = true;
}

std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const{
    std::list<User> fittedUsers;

    for(auto user : m_userList){
        if(filter(user)){
            fittedUsers.push_back(user);
        }
    }

    return fittedUsers;
}

int Storage::updateUser(std::function<bool(const User &)> filter, std::function<void(User &)> switcher){
    int count = 0;

    for(auto &user : m_userList){
        if(filter(user)){
            switcher(user);
            count++;
        }
    }

    if(count > 0){
        m_dirty = true;
    }

    return count;
}

int Storage::deleteUser(std::function<bool(const User &)> filter){
    int count = 0;

    for(auto i = m_userList.begin(); i != m_userList.end();){
        if(filter(*i)){
            i = m_userList.erase(i);
            count++;
        }
        else{
            i++;
        }
    }

    if(count > 0){
        m_dirty = true;
    }

    return count;
}

void Storage::createMeeting(const Meeting &t_meeting){
    m_meetingList.push_back(t_meeting);
    m_dirty = true;
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const{
    std::list<Meeting> fittedMeeting;

    for(auto meeting : m_meetingList){
        if(filter(meeting)){
            fittedMeeting.push_back(meeting);
        }
    }

    return fittedMeeting;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter, std::function<void(Meeting &)> switcher){
    int count = 0;

    for(auto &metting : m_meetingList){
        if(filter(metting)){
            switcher(metting);
            count++;
        }
    }

    if(count > 0){
        m_dirty = true;
    }

    return count;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter){
    int count = 0;

    for(auto i = m_meetingList.begin(); i != m_meetingList.end();){
        if(filter(*i)){
            i = m_meetingList.erase(i);
            count++;
        }
        else{
            i++;
        }
    }

    if(count > 0){
        m_dirty = true;
    }

    return count;
}

bool Storage::sync(void){
    if(m_dirty = true){
        if(writeToFile()){
            m_dirty = false;

            return true;
        }
        else{
            return false;
        }
    }
    else{
        return true;
    }
}