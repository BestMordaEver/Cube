#ifndef WAY2_H
#define WAY2_H

#include <vector>
#include <map>
#include "spin.h"
#include "cubestate.h"

using namespace std;

class HardWay
{
public:
	HardWay(bool force = false);
	map<int, CubeState*> map;

private:
	int doStateName(CubeState cs);
};

#endif // WAY2_H