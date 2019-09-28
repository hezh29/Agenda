#include"Date.hpp"
#include<regex>
#include<sstream>
#include<iomanip>

Date::Date(): m_year(0), m_month(0), m_day(0), m_hour(0), 
       m_minute(0){}

Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute): 
       m_year(t_year), m_month(t_month), m_day(t_day), m_hour(t_hour), 
       m_minute(t_minute){}

Date::Date(const std::string &dateString){
    std::regex format("([0-9]{4})-([0-9]{2})-([0-9]{2})/([0-9]{2}):([0-9]{2})");
    std::smatch match;

    if(std::regex_match(dateString,match,format)){
        m_year = std::stoi(match[1].str());
        m_month = std::stoi(match[2].str());
        m_day = std::stoi(match[3].str());
        m_hour = std::stoi(match[4].str());
        m_minute = std::stoi(match[5].str());
    }
    else{
        m_year = 0;
        m_month = 0;
        m_day = 0;
        m_hour = 0;
        m_minute = 0;
    }
}



int Date::getYear(void) const{
    return m_year;
}

void Date::setYear(const int t_year){
    m_year = t_year;
}

int Date::getMonth(void) const{
    return m_month;
}

void Date::setMonth(const int t_month){
    m_month = t_month;
}

int Date::getDay(void) const{
    return m_day;
}

void Date::setDay(const int t_day){
    m_day = t_day;
}

int Date::getHour(void) const{
    return m_hour;
}

void Date::setHour(const int t_hour){
    m_hour = t_hour;
}

int Date::getMinute(void) const{
    return m_minute;
}

void Date::setMinute(const int t_minute){
    m_minute = t_minute;
}

bool Date::isValid(const Date &t_date){
    bool isLeap;
    int dayOfMons[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    isLeap = !(t_date.m_year % 4) && (t_date.m_year % 100) || !(t_date.m_year % 400);
    
    if(isLeap){
        dayOfMons[1]++;
    }

    if( t_date.m_year >= 1000 && t_date.m_year <= 9999 && 
        t_date.m_month > 0 && t_date.m_month <= 12 && 
        t_date.m_day > 0 && t_date.m_day <= dayOfMons[t_date.m_month - 1] && 
        t_date.m_hour >= 0 && t_date.m_hour <= 59 && 
        t_date.m_minute >= 0 && t_date.m_minute <= 59){
            return true;
    }
    else{
        return false;
    }
}

Date Date::stringToDate(const std::string &t_dateString){
        return Date(t_dateString); 
}

std::string Date::dateToString(const Date &t_date){
    std::stringstream ss;
    std::string s;

    if(!isValid(t_date)){
        return "0000-00-00/00:00";
    }
    else{
        ss << std::setfill('0') << std::setw(4) << t_date.m_year << 
            "-"  <<std::setw(2) << t_date.m_month << 
            "-" << std::setw(2) << t_date.m_day << 
            "/" <<std::setw(2) << t_date.m_hour << 
            ":" << std::setw(2) << t_date.m_minute;

        ss >> s;

        return s;
    }
}

Date &Date::operator=(const Date &t_date){
    m_year = t_date.m_year;
    m_month = t_date.m_month;
    m_day = t_date.m_day;
    m_hour = t_date.m_hour;
    m_minute = t_date.m_minute; 

    return *this;
}

bool Date::operator==(const Date &t_date) const{
    if(m_year == t_date.m_year && m_month == t_date.m_month && 
        m_day == t_date.m_day && m_hour == t_date.m_hour && 
        m_minute == t_date.m_minute){
            return true;
    }
    else{
        return false;
    }
}

bool Date::operator>(const Date &t_date) const{
    return Date::dateToString(*this) > Date::dateToString(t_date);
}

bool Date::operator<(const Date &t_date) const{
    return !(*this > t_date || *this == t_date);
}

bool Date::operator>=(const Date &t_date) const{
    return !(*this < t_date);
}

bool Date::operator<=(const Date &t_date) const{
    return !(*this > t_date);
}






