#pragma once
#include<time.h>
#include"spin.h"

class Logger {
public:
	static void Start();
	static void ButtonPress(int);
	static void LogAction(spin s);
	static void LogDisassembly(bool);
	static void LogMsg(std::string);
};