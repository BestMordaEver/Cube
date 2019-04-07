#ifndef COMPILE_H
#define COMPILE_H
#include <string>
#include <vector>

class Compiler {
public:
	Compiler();
	static std::string codepath;
	static char output[2048], code[2048];
	static void Compile();
	static void Save();
private:
	static std::vector<std::vector<std::string>> query;
};
#endif