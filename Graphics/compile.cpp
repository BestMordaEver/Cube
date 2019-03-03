#include "compile.h"
#include "spin.h"
#include "logger.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

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

void Compiler::SyntaxAnalysis() {
	std::istringstream stream(code);

	bool compileable = true;
	Logger::LogMsg("Starting syntax analysis");
	strcpy(output, "Starting syntax analysis\n");

	if (std::string(code).length() == 0) {
		Logger::LogMsg("No code to analyze, standing by");
		strcat(output, "No code to analyze, standing by\n");
		return;
	}
	else
	{
		std::string line;
		int linenum = 1;
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
					subs.push_back(temp);
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
				continue;
			}

			if (line.find("spin") != std::string::npos) {
				std::istringstream iss(line);
				std::vector<std::string> subs;
				std::string temp;
				while (iss >> temp)
					subs.push_back(temp);
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

			if (line != "end" && line.length() != 0) {
				Logger::LogMsg("error, line " + std::to_string(linenum) + " : unexpected symbol " + line);
				strcat(output, ("error, line " + std::to_string(linenum) + " : unexpected symbol " + line + "\n").c_str());
				compileable = false;
			}
		}
	}
	if (compileable) {
		Logger::LogMsg("No errors found");
		strcat(output, "No errors found\n");
	}
	else {
		Logger::LogMsg("Unable to compile the program");
		strcat(output, "Unable to compile the program\n");
	}
}