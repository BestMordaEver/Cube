#include "compile.h"
#include "spin.h"
#include "logger.h"
#include "controller.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <algorithm>

std::vector<std::string> colors = { "red", "blue", "orange", "green", "white", "yellow" };
std::vector<spin> spiniterable = { OL, OR, RL, RR, WL, WR, YL, YR, BL, BR, GL, GR };
std::string Compiler::codepath = "program.cube";
char Compiler::output[2048], Compiler::code[2048];
std::vector<std::vector<std::string>> Compiler::query = std::vector<std::vector<std::string>>();


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
	std::istringstream stream(code);
	std::string line;
	query.clear();

	while (std::getline(stream, line))
	{
		std::istringstream iss(line);
		std::vector<std::string> subs;
		std::string temp;
		while (iss >> temp)
			subs.emplace_back(temp);
		query.emplace_back(subs);
	}

	Controller::getInstance().way.clear();

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
		std::vector<int> loops;

		if (query[0][0] != "disassembled" && query[0][0] != "assembled") {
			Logger::LogMsg("error, line 1: expected setup instruction ('disassembled' or 'assembled'), got " + query[0][0]);
			strcat(output, ("error, line 1: expected setup instruction ('disassembled' or 'assembled'), got " + query[0][0] + "\n").c_str());
			compileable = false;
		}
		for (int linenum = 1; linenum < query.size(); linenum++) {
			if (query[linenum][0][0] > '0' && query[linenum][0][0] < '9') {
				for (char ch : query[linenum][0])
					if (ch < '0' && ch > '9') {
						Logger::LogMsg("error, line " + std::to_string(linenum+1) + " : expected integer, got " + query[linenum][0]);
						strcat(output, ("error, line " + std::to_string(linenum+1) + " : expected integer, got " + query[linenum][0] + "\n").c_str());
						compileable = false;
					}
				if (query[linenum][1] != "times") {
					Logger::LogMsg("error, line " + std::to_string(linenum+1) + " : expected 'times', got " + query[linenum][1]);
					strcat(output, ("error, line " + std::to_string(linenum+1) + " : expected 'times', got " + query[linenum][1] + "\n").c_str());
					compileable = false;
				}
				if (query[linenum].size() > 2) {
					Logger::LogMsg("error, line " + std::to_string(linenum+1) + " : unexpected command after " + query[linenum][1]);
					strcat(output, ("error, line " + std::to_string(linenum+1) + " : unexpected command after " + query[linenum][1] + "\n").c_str());
					compileable = false;
				}
				loops.emplace_back(linenum+1);
				continue;
			}

			if (query[linenum][0] == "spin") {
				if (query[linenum].size() > 4) {
					Logger::LogMsg("error, line " + std::to_string(linenum+1) + " : unexpected command after" + query[linenum][3]);
					strcat(output, ("error, line " + std::to_string(linenum+1) + " : unexpected command after" + query[linenum][3] + "\n").c_str());
					compileable = false;
					continue;
				}

				bool spinable = false;
				{
					for (auto color : colors) 
						if (color == query[linenum][1]) {
							spinable = true;
							break;
						}
					if (!spinable) {
						Logger::LogMsg("error, line " + std::to_string(linenum+1) + " : expected valid color, got " + query[linenum][1]);
						strcat(output, ("error, line " + std::to_string(linenum+1) + " : expected valid color, got " + query[linenum][1] + "\n").c_str());
						compileable = false;
						continue;
					}
					if (query[linenum][2] != "to") {
						Logger::LogMsg("error, line " + std::to_string(linenum+1) + " : expected 'to', got " + query[linenum][2]);
						strcat(output, ("error, line " + std::to_string(linenum+1) + " : expected 'to', got " + query[linenum][2] + "\n").c_str());
						compileable = false;
						continue;
					}
					if (query[linenum][3] != "right" && query[linenum][3] != "left") {
						Logger::LogMsg("error, line " + std::to_string(linenum+1) + " : expected valid side, got " + query[linenum][3]);
						strcat(output, ("error, line " + std::to_string(linenum+1) + " : expected valid side, got " + query[linenum][3] + "\n").c_str());
						compileable = false;
						continue;
					}
				}
				continue;
			}

			if (query[linenum][0] == "end") {
				if (loops.empty()) {
					Logger::LogMsg("error, line " + std::to_string(linenum+1) + " : unexpected 'end', no preceeding loops");
					strcat(output, ("error, line " + std::to_string(linenum+1) + " : unexpected 'end', no preceeding loops\n").c_str());
					compileable = false;
					continue;
				} 
				else {
					loops.pop_back();
					continue;
				}
			}

			if (query[linenum][0].length() != 0) {
				Logger::LogMsg("error, line " + std::to_string(linenum+1) + " : unexpected command " + query[linenum][0]);
				strcat(output, ("error, line " + std::to_string(linenum+1) + " : unexpected command " + query[linenum][0] + "\n").c_str());
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
		
		Logger::LogMsg("Starting semantics analysis\n===================================");
		strcat(output, "Starting semantics analysis\n");
		
		for (int linenum = 0; linenum < query.size(); linenum++) {
			if (query[linenum][1] == "times") {
				if (std::stoi(query[linenum][0]) > 256 || std::stoi(query[linenum][0]) < 2) {
					Logger::LogMsg("error, line " + std::to_string(linenum+1) + " : integer out of bounds");
					strcat(output, ("error, line " + std::to_string(linenum+1) + " : integer out of bounds\n").c_str());
					compileable = false;
				}
			}
		}

		if (!compileable) {
			Logger::LogMsg("Unable to compile the program\n===================================");
			strcat(output, "Unable to compile the program\n");
			return;
		}

		std::vector<std::vector<spin>> loopqueue;
		// std::vector<int> loops is empty and can be reused

		Logger::LogMsg("Starting translation\n===================================");
		strcat(output, "Starting translation\n");
		

		for (int linenum = 0; linenum < query.size(); linenum++) {
			if (query[linenum][0] == "disassembled") {
				Controller::getInstance().Start();
				trans += "Start();\n";
				Controller::getInstance().Disassemble(200);
				trans += "Disassemble();\n";
			}
			else if (query[linenum][0] == "assembled") {
				Controller::getInstance().Start();
				trans += "Start();\n";
			}	

			if (query[linenum][1] == "times") {
				loops.emplace_back(std::stoi(query[linenum][0]));
				loopqueue.emplace_back(std::vector<spin>());
				continue;
			}

			if (query[linenum][0] == "end") {
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

			if (query[linenum][0] == "spin") {
				spin s;
				for (auto spin : spiniterable) {
					std::string temp = to_string(spin);
					std::transform(temp.begin(), temp.end(), temp.begin(), tolower);
					if (temp == query[linenum][1] + " " + query[linenum][2] + " " + query[linenum][3]) {
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
