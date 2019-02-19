#include "cubestate.h"
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <bitset>
#include <iostream>

CubeState::CubeState()
{
	state = { // Default and solved
	0, 1, 2, 3, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25, 26
	};
}

int CubeState::operator[](int i) { return state[i]; }

void CubeState::Act(spin act) {
	int temp;
	switch (act) {
	case OL: 
		temp = state[2];
		state[2] = state[20];
		state[20] = state[26];
		state[26] = state[8];
		state[8] = temp;
		temp = state[5];
		state[5] = state[11];
		state[11] = state[23];
		state[23] = state[17];
		state[17] = temp; 
		return;

	case OR: 
		temp = state[2];
		state[2] = state[8];
		state[8] = state[26];
		state[26] = state[20];
		state[20] = temp;
		temp = state[5];
		state[5] = state[17];
		state[17] = state[23];
		state[23] = state[11];
		state[11] = temp; 
		return;

	case RL: 
		temp = state[0];
		state[0] = state[6];
		state[6] = state[24];
		state[24] = state[18];
		state[18] = temp;
		temp = state[3];
		state[3] = state[15];
		state[15] = state[21];
		state[21] = state[9];
		state[9] = temp;
		return;

	case RR: 
		temp = state[0];
		state[0] = state[18];
		state[18] = state[24];
		state[24] = state[6];
		state[6] = temp;
		temp = state[3];
		state[3] = state[9];
		state[9] = state[21];
		state[21] = state[15];
		state[15] = temp;
		return;

	case WL: 
		temp = state[0];
		state[0] = state[18];
		state[18] = state[20];
		state[20] = state[2];
		state[2] = temp;
		temp = state[1];
		state[1] = state[9];
		state[9] = state[19];
		state[19] = state[11];
		state[11] = temp;
		return;

	case WR: 
		temp = state[0];
		state[0] = state[2];
		state[2] = state[20];
		state[20] = state[18];
		state[18] = temp;
		temp = state[1];
		state[1] = state[11];
		state[11] = state[19];
		state[19] = state[9];
		state[9] = temp; 
		return;

	case YL: 
		temp = state[6];
		state[6] = state[8];
		state[8] = state[26];
		state[26] = state[24];
		state[24] = temp;
		temp = state[7];
		state[7] = state[17];
		state[17] = state[25];
		state[25] = state[15];
		state[15] = temp;
		return;

	case YR: 
		temp = state[6];
		state[6] = state[24];
		state[24] = state[26];
		state[26] = state[8];
		state[8] = temp;
		temp = state[7];
		state[7] = state[15];
		state[15] = state[25];
		state[25] = state[17];
		state[17] = temp;
		return;

	case BL: 
		temp = state[0];
		state[0] = state[2];
		state[2] = state[8];
		state[8] = state[6];
		state[6] = temp;
		temp = state[1];
		state[1] = state[5];
		state[5] = state[7];
		state[7] = state[3];
		state[3] = temp;
		return;

	case BR: 
		temp = state[0];
		state[0] = state[6];
		state[6] = state[8];
		state[8] = state[2];
		state[2] = temp;
		temp = state[1];
		state[1] = state[3];
		state[3] = state[7];
		state[7] = state[5];
		state[5] = temp;
		return;

	case GL: 
		temp = state[18];
		state[18] = state[24];
		state[24] = state[26];
		state[26] = state[20];
		state[20] = temp;
		temp = state[19];
		state[19] = state[21];
		state[21] = state[25];
		state[25] = state[23];
		state[23] = temp;
		return;

	case GR: 
		temp = state[18];
		state[18] = state[20];
		state[20] = state[26];
		state[26] = state[24];
		state[24] = temp;
		temp = state[19];
		state[19] = state[23];
		state[23] = state[25];
		state[25] = state[21];
		state[21] = temp;
		return;
	}
}