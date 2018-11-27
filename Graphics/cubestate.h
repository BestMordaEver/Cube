#ifndef CUBESTATE_H
#define CUBESTATE_H

#include <vector>
#include <map>
#include "spin.h"

class CubeState {
public:
	CubeState(int d);
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
	int operator[](int i) {
		return state[i];
	}
private:
	vector<int> state;
	map<spin, CubeState*> neighbours;
	int depth;
};

#endif // CUBESTATE_H