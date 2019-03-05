#include "compile.h"
#include "spin.h"
#include <vector>
#include <sstream>
#include <algorithm>

std::vector<spin> spiniterable = { OL, OR, RL, RR, WL, WR, YL, YR, BL, BR, GL, GR };

void Compiler::SyntaxAnalysis() {
	std::string codepath = "program.cube", code = "";
	std::ifstream fs(codepath);
	while (fs.good()) {
		code += tolower(fs.get());
	}
	fs.close();
	code.resize(code.size() - 1);
	std::istringstream stream(code);

	bool compileable = true;
	logger::LogMsg("Starting syntax analysis\n===================================");

	if (code.length() == 0)
		logger::LogMsg("No code to analyze, standing by");
	else
	{
		std::string line;
		int linenum = 1;
		std::getline(stream, line);
		if (line != "disassembled" && line != "assembled") {
			logger::LogMsg("error, line 1: expected setup instruction ('disassembled' or 'assembled'), got " + line);
			compileable = false;
		}
		while (std::getline(stream, line)) {
			linenum++;
			if (line.find("times") != std::string::npos) {
				std::istringstream iss(line);
				std::vector<std::string> subs;
				std::string temp;
				while (iss >> temp)
					subs.push_back(temp);
				for (char ch : subs[0])
					if (ch < '0' && ch > '9') {
						logger::LogMsg("error, line " + std::to_string(linenum) + " : expected integer, got " + subs[0]);
						compileable = false;
						break;
					}
				if (subs[1] != "times") {
					logger::LogMsg("error, line " + std::to_string(linenum) + " : expected 'times', got " + subs[1]);
					compileable = false;
				}
				if (subs.size() > 2) {
					logger::LogMsg("error, line " + std::to_string(linenum) + " : unexpected symbol after " + subs[1]);
					compileable = false;
				}
				continue;
			}

			if (line.find("spin") != std::string::npos) {
				std::istringstream iss(line);
				std::vector<std::string> subs;
				std::string temp;
				while (iss >> temp)
					subs.push_back(temp);
				if (subs[0] != "spin") {
					logger::LogMsg("error, line " + std::to_string(linenum) + " : expected 'spin', got " + subs[0]);
					compileable = false;
				}

				bool spinable = false;
				for (auto spin : spiniterable) {
					std::string temp = to_string(spin);
					std::transform(temp.begin(), temp.end(), temp.begin(), tolower);
					if (temp == subs[1] + " " + subs[2] + " " + subs[3]) {
						spinable = true;
						break;
					}
				}
				if (!spinable) {
					logger::LogMsg("error, line " + std::to_string(linenum) + " : unexpected symbols after 'spin'");
					compileable = false;
					continue;
				}
				if (subs.size() > 4) {
					logger::LogMsg("error, line " + std::to_string(linenum) + " : unexpected symbol after " + subs[3]);
					compileable = false;
				}
				continue;
			}

			if (line != "end" && line.length() != 0) {
				logger::LogMsg("error, line " + std::to_string(linenum) + " : unexpected symbol " + line);
				compileable = false;
			}
		}
	}
	if (compileable)
		logger::LogMsg("No errors found\n===================================");
	else
		logger::LogMsg("Unable to compile the program\n===================================");
}