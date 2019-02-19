#ifndef CUBESTATE_H
#define CUBESTATE_H

#include <vector>
#include "spin.h"

class CubeState {
public:
	CubeState();
	void Act(spin);
	int operator[](int);
	std::vector<int> state;
};

#endif // CUBESTATE_H