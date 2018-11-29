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
	string Path(CubeState* cs);
	ofstream ostr;
	bool exists(CubeState * cs);
};

#endif // HARDWAY_H