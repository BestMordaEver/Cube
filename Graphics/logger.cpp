#include "logger.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "controller.h"

using namespace std;
time_t t = time(NULL);
struct tm tm = *localtime(&t);
string logname = "logs/" + to_string(tm.tm_mday) + "." + to_string(tm.tm_mon+1) + "." + to_string(tm.tm_year+1900) + "-" + to_string(tm.tm_hour) + "." + to_string(tm.tm_min) + "." + to_string(tm.tm_sec) + ".txt";

void logger::Start() {
	system("mkdir logs");
	ofstream stream(logname, ios_base::app);
	stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << " Aplication started" << endl;
	stream.close();
}

void logger::ButtonPress(int bp) {
	string info;
	switch (bp) {
	case 0: info = " MANUAL INPUT - Stop"; break;
	case 1: info = " MANUAL INPUT - Continue"; break;
	case 2: info = " MANUAL INPUT - Generate"; break;
	case 3: info = " MANUAL INPUT - Pause"; break;
	case 4: info = " MANUAL INPUT - " + to_string(Controller::getInstance().way.back()); break;
	}

	time_t t = time(NULL);
	tm = *localtime(&t);
	ofstream stream(logname, ios_base::app);
	stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << info << endl;
	stream.close();
}

void logger::LogAction(spin act) {
	string info = " " + to_string(act);
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	ofstream stream(logname, ios_base::app);
	stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << info << endl;
	stream.close();
}

void logger::LogDisassembly(bool isDisassembling) {
	string info = isDisassembling ? " Starting disasembly" : " Disassembly finished, starting to solve";
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	ofstream stream(logname, ios_base::app);
	stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << info << endl;
	stream.close();
}