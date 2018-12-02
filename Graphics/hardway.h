#ifndef HARDWAY_H
#define HARDWAY_H

#include <vector>
#include <fstream>
#include "spin.h"
#include "cubestate.h"

class HardSolver
{
public:
	HardSolver(bool force = false);
	std::vector<spin> Solve();
	std::vector<spin> way;
private:
	std::string Path(CubeState * cs);
	std::ofstream ostr;
	bool exists(CubeState * cs);
};

#endif // HARDWAY_H