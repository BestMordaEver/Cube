#include "logger.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "controller.h"

time_t t = time(NULL);
struct tm tm = *localtime(&t);
std::string logname = "logs/" + std::to_string(tm.tm_mday) + "." + std::to_string(tm.tm_mon+1) + "." + std::to_string(tm.tm_year+1900) + "-" + std::to_string(tm.tm_hour) + "." + std::to_string(tm.tm_min) + "." + std::to_string(tm.tm_sec) + ".txt";

void logger::Start() {
	system("mkdir logs");
	std::ofstream stream(logname, std::ios::app);
	stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << " Aplication started, reading instructions" << std::endl;
	if (!std::fstream("program.cube").good())
		stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << " No instructions, standing by" << std::endl;
	else
		stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << " Found instructions" << std::endl;
	stream.close();
}

void logger::ButtonPress(int bp) {
	std::string info;
	switch (bp) {
	case 0: info = " MANUAL INPUT - Stop"; break;
	case 1: info = " MANUAL INPUT - Continue"; break;
	case 2: info = " MANUAL INPUT - Generate"; break;
	case 3: info = " MANUAL INPUT - Pause"; break;
	case 4: info = " MANUAL INPUT - " + to_string(Controller::getInstance().way.back()); break;
	}

	time_t t = time(NULL);
	tm = *localtime(&t);
	std::ofstream stream(logname, std::ios::app);
	stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << info << std::endl;
	stream.close();
}

void logger::LogAction(spin act) {
	std::string info = " " + to_string(act);
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	std::ofstream stream(logname, std::ios::app);
	stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << info << std::endl;
	stream.close();
}

void logger::LogDisassembly(bool isDisassembling) {
	std::string info = isDisassembling ? " Starting disasembly" : " Disassembly finished, starting to solve";
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	std::ofstream stream(logname, std::ios::app);
	stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << info << std::endl;
	stream.close();
}

void logger::LogMsg(std::string msg) {
	std::ofstream stream(logname, std::ios::app);
	stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << " " << msg << std::endl;
	stream.close();
}