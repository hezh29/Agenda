#include<fstream>
#include<regex>
#include"Storage.hpp"
#include"Path.hpp"



Storage::Storage(){
    readFromFile();
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
        Meeting m;

        while(std::getline(ifile, s)) {
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
}
