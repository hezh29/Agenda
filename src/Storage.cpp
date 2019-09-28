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
    
    ifile.open(Path::meetingPath);
    if(ifile.is_open()) {
        std::string s;
        std::regex format("\"(.*)\",\"(.*)\",\"(.*)\",\"(.*)\",\"(.*)\"");
        std::smatch match;
        while(std::getline(ifile, s)) {
            std::regex_match(s,match,format);
            m_meetingList.push_back(Meeting(match[1].str()))
        }
    }
    else{
        return false;
    }
}
