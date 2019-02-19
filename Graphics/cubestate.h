#ifndef CUBESTATE_H
#define CUBESTATE_H

#include <vector>
#include "spin.h"

class CubeState {
public:
	CubeState();
	void Act(spin act);
	void OrangeRight(),
		OrangeLeft(),
		RedLeft(),
		RedRight(),
		WhiteLeft(),
		WhiteRight(),
		YellowRight(),
		YellowLeft(),
		BlueRight(),
		BlueLeft(),
		GreenLeft(),
		GreenRight();
	int operator[](int i);
	std::vector<int> state;
};

#endif // CUBESTATE_H