#ifndef HARDWAY_H
#define HARDWAY_H

#include <vector>
#include <fstream>
#include "spin.h"
#include "cubestate.h"

using namespace std;

class HardWay
{
public:
	HardWay(bool force = false);
	vector<spin> Solve();
	vector<spin> way;
private:
	string path = "tree";
	ofstream ostr;
	void write(CubeState* cs);
	bool exists(CubeState * cs);
};

#endif // HARDWAY_H