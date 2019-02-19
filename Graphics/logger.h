#pragma once
#include<fstream>
#include<time.h>
#include<string>

static class logger {
public:
	static void Start();
	static void ButtonPress(int);
	static void write_action(int);
};