#pragma once
#include<fstream>
#include<time.h>
#include<string>

static class logger {
public:
	static void write_start();
	static void write_bpress(int);
	static void write_action(int);
};