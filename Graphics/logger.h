#pragma once
#include<fstream>
#include<time.h>
#include<string>
#include"spin.h"

static class logger {
public:
	static void Start();
	static void ButtonPress(int);
	static void LogAction(spin s);
	static void LogDisassembly(bool);
};