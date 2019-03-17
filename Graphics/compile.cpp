#include "compile.h"
#include "spin.h"
#include "logger.h"
#include "controller.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <algorithm>

std::vector<spin> spiniterable = { OL, OR, RL, RR, WL, WR, YL, YR, BL, BR, GL, GR };
std::string Compiler::codepath = "program.cube";
char Compiler::output[2048], Compiler::code[2048];

Compiler::Compiler() {
	std::ifstream fs(codepath);
	fs.read(code, 2048);
	for (int i = 0; i < 2048; i++)
		code[i] = tolower(code[i]);
	fs.close();
}

void Compiler::Save() {
	std::fstream fs(codepath);
	fs.write(std::string(code).c_str(), std::string(code).size());
	char codebuf[2048];
	fs.close();
	fs.open(codepath);
	fs.read(codebuf, std::string(code).size());
	for (int i = 0; i < std::string(code).size(); i++) {
		codebuf[i] = tolower(codebuf[i]);
		code[i] = tolower(code[i]);
	}
	fs.close();
	if (std::string(code) == std::string(codebuf, std::string(code).size()))
		strcpy(output, "Successfully saved");
	else
		strcpy(output, "Error, file may be corrupted!");
}

void Compiler::Compile() {
	Controller::getInstance().way.clear();

	std::istringstream stream(code);

	std::string trans = "";
	bool compileable = true;
	Logger::LogMsg("Starting syntax analysis\n===================================");
	strcpy(output, "Starting syntax analysis\n");

	if (std::string(code).length() == 0) {
		Logger::LogMsg("No code to analyze, standing by");
		strcat(output, "No code to analyze, standing by\n");
		return;
	}
	else {
		std::string line;
		int linenum = 1;
		std::vector<int> loops;

		std::getline(stream, line);
		if (line != "disassembled" && line != "assembled") {
			Logger::LogMsg("error, line 1: expected setup instruction ('disassembled' or 'assembled'), got " + line);
			strcat(output, ("error, line 1: expected setup instruction ('disassembled' or 'assembled'), got " + line + "\n").c_str());
			compileable = false;
		}
		while (std::getline(stream, line)) {
			linenum++;
			if (line.find("times") != std::string::npos) {
				std::istringstream iss(line);
				std::vector<std::string> subs;
				std::string temp;
				while (iss >> temp)
					subs.emplace_back(temp);
				for (char ch : subs[0])
					if (ch < '0' && ch > '9') {
						Logger::LogMsg("error, line " + std::to_string(linenum) + " : expected integer, got " + subs[0]);
						strcat(output, ("error, line " + std::to_string(linenum) + " : expected integer, got " + subs[0] + "\n").c_str());
						compileable = false;
						break;
					}
				if (subs[1] != "times") {
					Logger::LogMsg("error, line " + std::to_string(linenum) + " : expected 'times', got " + subs[1]);
					strcat(output, ("error, line " + std::to_string(linenum) + " : expected 'times', got " + subs[1] + "\n").c_str());
					compileable = false;
				}
				if (subs.size() > 2) {
					Logger::LogMsg("error, line " + std::to_string(linenum) + " : unexpected symbol after " + subs[1]);
					strcat(output, ("error, line " + std::to_string(linenum) + " : unexpected symbol after " + subs[1] + "\n").c_str());
					compileable = false;
				}
				loops.emplace_back(linenum);
				continue;
			}

			if (line.find("spin") != std::string::npos) {
				std::istringstream iss(line);
				std::vector<std::string> subs;
				std::string temp;
				while (iss >> temp)
					subs.emplace_back(temp);
				if (subs[0] != "spin") {
					Logger::LogMsg("error, line " + std::to_string(linenum) + " : expected 'spin', got " + subs[0]);
					strcat(output, ("error, line " + std::to_string(linenum) + " : expected 'spin', got " + subs[0] + "\n").c_str());
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
					Logger::LogMsg("error, line " + std::to_string(linenum) + " : unexpected symbols after 'spin'");
					strcat(output, ("error, line " + std::to_string(linenum) + " : unexpected symbols after 'spin'\n").c_str());
					compileable = false;
					continue;
				}
				if (subs.size() > 4) {
					Logger::LogMsg("error, line " + std::to_string(linenum) + " : unexpected symbol after " + subs[3]);
					strcat(output, ("error, line " + std::to_string(linenum) + " : unexpected symbol after " + subs[3] + "\n").c_str());
					compileable = false;
				}
				continue;
			}

			if (line == "end") {
				if (loops.empty()) {
					Logger::LogMsg("error, line " + std::to_string(linenum) + " : unexpected symbol " + line);
					strcat(output, ("error, line " + std::to_string(linenum) + " : unexpected symbol " + line + "\n").c_str());
					compileable = false;
				}
				loops.pop_back();
				continue;
			}

			if (line.length() != 0) {
				Logger::LogMsg("error, line " + std::to_string(linenum) + " : unexpected symbol " + line);
				strcat(output, ("error, line " + std::to_string(linenum) + " : unexpected symbol " + line + "\n").c_str());
				compileable = false;
			}
		}

		if (!loops.empty()) {
			while (!loops.empty()) {
				Logger::LogMsg("error, expected 'end' to close loop at line " + std::to_string(loops.back()));
				strcat(output, ("error, expected 'end' to close loop at line " + std::to_string(loops.back()) + "\n").c_str());
				loops.pop_back();
			}
			compileable = false;
		}

		if (!compileable) {
			Logger::LogMsg("Unable to compile the program\n===================================");
			strcat(output, "Unable to compile the program\n");
			return;
		}
		
		stream = std::istringstream(code);
		linenum = 0;

		Logger::LogMsg("Starting semantics analysis\n===================================");
		strcat(output, "Starting semantics analysis\n");
		
		while (std::getline(stream, line)) {
			linenum++;
			if (line.find("times") != std::string::npos) {
				std::istringstream iss(line);
				std::vector<std::string> subs;
				std::string temp;
				while (iss >> temp)
					subs.emplace_back(temp);

				if (std::stoi(subs[0]) > 256 || std::stoi(subs[0]) < 1) {
					Logger::LogMsg("error, line " + std::to_string(linenum) + " : integer out of bounds");
					strcat(output, ("error, line " + std::to_string(linenum) + " : integer out of bounds\n").c_str());
					compileable = false;
				}
			}
		}

		if (!compileable) {
			Logger::LogMsg("Unable to compile the program\n===================================");
			strcat(output, "Unable to compile the program\n");
			return;
		}

		stream = std::istringstream(code);
		std::vector<std::vector<spin>> loopqueue;
		// std::vector<int> loops is empty and can be reused

		Logger::LogMsg("Starting translation\n===================================");
		strcat(output, "Starting translation\n");
		

		while (std::getline(stream, line)) {
			if (line == "disassembled") {
				Controller::getInstance().Start();
				trans += "Start();\n";
				Controller::getInstance().Disassemble(200);
				trans += "Disassemble();\n";
			}
			if (line == "assembled") {
				Controller::getInstance().Start();
				trans += "Start();\n";
			}	

			if (line.find("times") != std::string::npos) {
				std::istringstream iss(line);
				std::vector<std::string> subs;
				std::string temp;
				while (iss >> temp)
					subs.emplace_back(temp);

				loops.emplace_back(std::stoi(subs[0]));
				loopqueue.emplace_back(std::vector<spin>());
				continue;
			}

			if (line == "end") {
				if (loops.size() == 1) {
					for (int i = 0; i < loops[0]; i++)
						std::transform(loopqueue[0].begin(), loopqueue[0].end(), std::back_inserter(Controller::getInstance().way), [](spin s) { return s; });
					loops.pop_back();
					loopqueue.pop_back();
				}
				else {
					for (int i = 0; i < loops.back(); i++)
						std::transform(loopqueue.back().begin(), loopqueue.back().end(), std::back_inserter(loopqueue[loopqueue.size()-2]), [](spin s) { return s; });
					loops.pop_back();
					loopqueue.pop_back();
				}
				continue;
			}

			if (line.find("spin") != std::string::npos) {
				std::istringstream iss(line);
				std::vector<std::string> subs;
				std::string temp;
				while (iss >> temp)
					subs.emplace_back(temp);
				
				spin s;
				for (auto spin : spiniterable) {
					std::string temp = to_string(spin);
					std::transform(temp.begin(), temp.end(), temp.begin(), tolower);
					if (temp == subs[1] + " " + subs[2] + " " + subs[3]) {
						s = spin;
						break;
					}
				}

				if (loops.empty())
					Controller::getInstance().way.emplace_back(s);
				else
					loopqueue.back().emplace_back(s);
				continue;
			}
		}
	}

	if (compileable) {
		Logger::LogMsg("No errors found\n===================================");
		strcat(output, "No errors found\n");
		if (!Controller::getInstance().way.empty())
			Controller::getInstance().state = Controller::prepare;

		for (spin s : Controller::getInstance().way)
			trans += "way.push_back(" + to_string(s, false) + ");\n";

		Logger::LogMsg("Translated code as follows\n===================================" + trans + "===================================\n");
		strcat(output, ("Translated code as follows\n####################\n" + trans + "####################\n").c_str());
	}
	else {
		Logger::LogMsg("Unable to compile the program\n===================================");
		strcat(output, "Unable to compile the program\n");
	}
}
