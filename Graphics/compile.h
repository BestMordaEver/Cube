#ifndef COMPILE_H
#define COMPILE_H
#include <string>

class Compiler {
public:
	Compiler();
	static std::string codepath;
	static char output[2048], code[2048];
	static void Compile();
	static void Save();
};
#endif