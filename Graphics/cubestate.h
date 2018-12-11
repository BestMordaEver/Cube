#ifndef CUBESTATE_H
#define CUBESTATE_H

#include <vector>
#include "spin.h"

class CubeState {
public:
	CubeState();
	CubeState(std::string charset);
	CubeState(CubeState s, spin act);
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
	std::string getStateName(), getContent();
	int operator[](int i);
	std::vector<int> state;
	spin parent;
};

#endif // CUBESTATE_H