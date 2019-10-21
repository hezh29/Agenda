#include "AgendaUI.hpp"
#include<iomanip>
#include<vector>
#include<string>

AgendaUI::AgendaUI(){
	isLogin = false;
}

void AgendaUI::OperationLoop(void){
	while (true) {
		startAgenda();
		if (!executeOperation(getOperation())) {
			break;
		}
	}
}

void AgendaUI::startAgenda(void){
	for (int i = 0; i < 47; i++) {
		std::cout << "-";
	}
	std::cout << "Agenda";
	for (int i = 0; i < 47; i++) {
		std::cout << "-";
	}
	std::cout << std::endl << "Action :" << std::endl;

	if (isLogin) {
		std::cout <<
			"o    - log out Agenda\n" <<
			"dc   - delete Agenda account\n" <<
			"lu   - list all Agenda user\n" <<
			"cm   - create a meeting\n" <<
			"amp  - add meeting participator\n" <<
			"rmp  - remove meeting participator\n" <<
			"rqm  - request to quit meeting\n" <<
			"la   - list all meetings\n" <<
			"las  - list all sponsor meetings\n" <<
			"lap  - list all paticipator meetings\n" <<
			"qm   - query meeting by title\n" <<
			"qt   - query meeting by time interval\n" <<
			"dm   - delete meeting by title\n" <<
			"da   - delete all meetings\n";
	}
	else {
		std::cout << 
			"l    - log in Agenda by user name and password\n" <<
			"r    - register an Agenda account\n" <<
			"q    - quit Agenda\n";
	}

	for (int i = 0; i < 100; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
}

std::string AgendaUI::getOperation(){
	std::string operation;
	if (isLogin) {
		std::cout << "Agenda@" << m_userName << " :~# ";
	}
	else {
		std::cout << "Agenda :~$ ";
	}
	//std::getline(std::cin, operation);
	std::cin >> operation;
	return operation;
}

bool AgendaUI::executeOperation(std::string t_operation){
	if (isLogin) {
		if (t_operation == "o")
			userLogOut();
		else if (t_operation == "dc")
			deleteUser();
		else if (t_operation == "lu")
			listAllUsers();
		else if (t_operation == "cm")
			createMeeting();
		else if (t_operation == "amp")
			addParticipator();
		else if (t_operation == "rmp")
			removeParticipator();
		else if (t_operation == "rqm")
			quitMeeting();
		else if (t_operation == "la")
			listAllMeetings();
		else if (t_operation == "las")
			listAllSponsorMeetings();
		else if (t_operation == "lap")
			listAllParticipateMeetings();
		else if (t_operation == "qm")
			queryMeetingByTitle();
		else if (t_operation == "qt")
			queryMeetingByTimeInterval();
		else if (t_operation == "dm")
			deleteMeetingByTitle();
		else if (t_operation == "da")
			deleteAllMeetings();
	}
	else {
		if (t_operation == "l")
			userLogIn();
		else if (t_operation == "r")
			userRegister();
		else if (t_operation == "q")
			return false;
	}

	return true;
}

void AgendaUI::userLogIn(void){
	std::cout << "[log in] [username] [password]" << std::endl << "[log in] ";
	std::string username, password;
	std::cin >> username >> password;

	if (m_agendaService.userLogIn(username, password)) {
		m_userName = username;
		m_userPassword = password;
		isLogin = true;
		std::cout << "[log in] Succeed!" << std::endl;
	}
	else {
		std::cout << "[log in] Password error or user doesn't exit!" << std::endl;
	}
}

void AgendaUI::userRegister(void){
	std::cout << std::endl << "[register] [user name] [password] [email] [phone]" << std::endl << "[register] ";
	std::string username, password, email, phone;
	std::cin >> username >> password >> email >> phone;

	if (m_agendaService.userRegister(username, password, email, phone)) {
		std::cout << "[register] Succeed!" << std::endl;
	}
	else {
		std::cout << "[register] This username has been registered!" << std::endl;
	}
}

void AgendaUI::userLogOut(void){
	isLogin = false;
	m_userName.clear();
	m_userPassword.clear();
}

void AgendaUI::quitAgenda(void){
}

void AgendaUI::deleteUser(void){
	if (m_agendaService.deleteUser(m_userName, m_userPassword)) {
		userLogOut();
		std::cout << "[delete Agenda account] Succeed!\n";
	}
}

void AgendaUI::listAllUsers(void){
	std::cout << "[list all users]\n\n";
	std::cout << std::left << 
		std::setw(20) << "name" << 
		std::setw(20) << "email" << 
		std::setw(20) << "phone" << std::endl;

	for (auto user : m_agendaService.listAllUsers()) {
		std::cout << 
			std::setw(20) << user.getName() << 
			std::setw(20) << user.getEmail() << std::setw(20) << 
			user.getPhone() << std::endl;
	}
}

void AgendaUI::createMeeting(void){
	std::cout << "[create meeting] [the number of participators]\n";
	std::cout << "[create meeting] ";
	int num;
	std::cin >> num;
	std::vector<std::string> participators;
	for (int i = 1; i <= num; i++) {
		std::cout << "[create meeting] [please enter the participator " << i << " ]\n";
		std::cout << "[create meeting] ";
		std::string participator;
		std::cin >> participator;
		participators.push_back(participator);
	}
	std::cout << "[create meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mmdd/hh:mm)]\n";
	std::cout << "[create meeting] ";
	std::string title, startTime, endTime;
	std::cin >> title >> startTime >> endTime;
	if (m_agendaService.createMeeting(m_userName, title, startTime, endTime, participators)) {
		std::cout<<"[create meeting] Succeed!\n";
	}
	else {
		std::cout << "[create meeting] Error!\n";
	}
}

void AgendaUI::listAllMeetings(void){
	std::cout << "[list all meetings]\n\n";

	printMeetings(m_agendaService.listAllMeetings(m_userName));
}

void AgendaUI::listAllSponsorMeetings(void){
	std::cout << "[list all sponsor meetings]\n\n";

	printMeetings(m_agendaService.listAllSponsorMeetings(m_userName));
}

void AgendaUI::listAllParticipateMeetings(void){
	std::cout << "[list all participate meetings]\n\n";

	printMeetings(m_agendaService.listAllParticipateMeetings(m_userName));
}

void AgendaUI::queryMeetingByTitle(void){
	std::cout << "[query meetings] [title]\n";
	std::cout << "[query meetings] ";
	std::string title;
	std::cin >> title;
	std::cout << "[query meetings]\n\n";
	printMeetings(m_agendaService.meetingQuery(m_userName, title));
}

void AgendaUI::queryMeetingByTimeInterval(void){
	std::cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
	std::cout << "[query meetings] ";
	std::string startTime, endTime;
	std::cin >> startTime >> endTime;
	std::cout << "[query meetings]\n\n";

	printMeetings(m_agendaService.meetingQuery(m_userName, startTime, endTime));
}

void AgendaUI::deleteMeetingByTitle(void){
	std::cout << "[delete meeting] [title]\n";
	std::cout << "[delete meeting] ";
	std::string title;
	std::cin >> title;
	if (m_agendaService.deleteMeeting(m_userName, title)) {
		std::cout << "[delete meeting] Succeed!\n";
	}
	else {
		std::cout << "[delete meeting] Error!\n";
	}

}

void AgendaUI::deleteAllMeetings(void){
	if (m_agendaService.deleteAllMeetings(m_userName)) {
		std::cout << "[delete all meeting] Succeed!\n";
	}
	else {
		std::cout << "[delete all meeting] Error!\n";
	}
}

void AgendaUI::addParticipator(void){
	std::cout << "[add participator] [meeting title] [participator username]\n";
	std::cout << "[add participator] ";
	std::string title, name;
	std::cin >> title >> name;
	if (m_agendaService.addMeetingParticipator(m_userName, title, name)) {
		std::cout << "[add participator] Succeed!\n";
	}
	else {
		std::cout << "[add participator] Error!\n";
	}
}

void AgendaUI::removeParticipator(void){
	std::cout << "[remove participator] [meeting title] [participator username]\n";
	std::cout << "[remove participator] ";
	std::string title, name;
	std::cin >> title >> name;
	if (m_agendaService.removeMeetingParticipator(m_userName, title, name)) {
		std::cout << "[remove participator] Succeed!\n"; 
	}
	else {
		std::cout << "[remove participator] Error!\n";
	}
}

void AgendaUI::quitMeeting(void){
	std::cout << "[quit meeting] [meeting title]\n";
	std::cout << "[quit meeting] ";
	std::string title;
	std::cin >> title;
	if (m_agendaService.quitMeeting(m_userName, title)) {
		std::cout << "[quit meeting] Succeed!\n";
	}
	else {
		std::cout << "[quit meeting] Error!\n";
	}
}

void AgendaUI::printMeetings(std::list<Meeting> t_meetings){
	std::cout << std::left <<
		std::setw(19) << "title" <<
		std::setw(19) << "sponsor" <<
		std::setw(19) << "start time" <<
		std::setw(19) << "end time" <<
		std::setw(19) << "participaootors" << std::endl;
	for (auto meeting : t_meetings) {
		std::cout << std::left <<
			std::setw(19) << meeting.getTitle() <<
			std::setw(19) << meeting.getSponsor() <<
			std::setw(19) << Date::dateToString(meeting.getStartDate()) <<
			std::setw(19) << Date::dateToString(meeting.getEndDate());
		std::string participators;
		for (auto user : meeting.getParticipator()) {
			participators += user + ",";
		}
		participators.pop_back();
		std::cout << participators << std::endl;
	}
}
