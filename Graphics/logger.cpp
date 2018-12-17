#include "logger.h"
#include<iostream>
#include<fstream>
#include<time.h>
#include<string>

using namespace std;

	void logger::write_start() {
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		ofstream stream("log.txt", ios_base::app);
		stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << " Aplicattion start" << endl;
		stream.close();
	}
	void logger::write_bpress(int bp) {
		string info;
		if (bp == 0) {
			info = " Press Stop";
		}
		else if (bp == 1) {
			info = " Press Continue";
		}
		else if (bp == 2) {
			info = " Press Generate";
		}
		else if (bp == 3) {
			info = " Press Pause";
		}

		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		ofstream stream("log.txt", ios_base::app);
		stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << info << endl;
		stream.close();
	}
	void logger::write_action(int action) {
		static string info_prev = "";
		string info;
		if (action == 1) {
			info = " Spin orange side to the right";
		}
		else if (action == 0) {
			info = " Spin orange side to the left";
		}
		else if (action == 2) {
			info = " Spin red side to the left";
		}
		else if (action == 3) {
			info = " Spin red side to the right";
		}
		else if (action == 4) {
			info = " Spin white side to the left";
		}
		else if (action == 5) {
			info = " Spin white side to the right";
		}
		else if (action == 7) {
			info = " Spin yellow side to the right";
		}
		else if (action == 6) {
			info = " Spin yellow side to the left";
		}
		else if (action == 9) {
			info = " Spin blue side to the right";
		}
		else if (action == 8) {
			info = " Spin blue side to the left";
		}
		else if (action == 10) {
			info = " Spin green side to the left";
		}
		else if (action == 11) {
			info = " Spin green side to the right";
		}
		if (!info._Equal(info_prev)) {
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			ofstream stream("log.txt", ios_base::app);
			stream << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << info << endl;
			stream.close();
		}
		info_prev = info;
	}
	


