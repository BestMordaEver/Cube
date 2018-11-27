#ifndef CUBESTATE_H
#define CUBESTATE_H

#include <vector>
#include <map>
#include "spin.h"

class CubeState {
public:
	CubeState(int d);
	int depth;
	std::vector<int> state;
	std::map<spin, CubeState*> neighbours;
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
	int doStateName();
	int operator[](int i) {return state[i];	}
};

#endif // CUBESTATE_H