#include "cubestate.h"

CubeState::CubeState(int d)
{
	depth = d;
	state = {
	0, 1, 2, 3, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25, 26
	};
}

void CubeState::Act(spin act) {
	if (act == OR) { OrangeRight(); return; }
	if (act == OL) { OrangeLeft(); return; }
	if (act == RL) { RedLeft(); return; }
	if (act == RR) { RedRight(); return; }
	if (act == WL) { WhiteLeft(); return; }
	if (act == WR) { WhiteRight(); return; }
	if (act == YR) { YellowRight(); return; }
	if (act == YL) { YellowLeft(); return; }
	if (act == BR) { BlueRight(); return; }
	if (act == BL) { BlueLeft(); return; }
	if (act == GL) { GreenLeft(); return; }
	if (act == GR) { GreenRight(); return; }
}

void CubeState::OrangeLeft()
{
	int temp = state[2];
	state[2] = state[20];
	state[20] = state[26];
	state[26] = state[8];
	state[8] = temp;
	temp = state[5];
	state[5] = state[11];
	state[11] = state[23];
	state[23] = state[17];
	state[17] = temp;
}

void CubeState::OrangeRight()
{
	int temp = state[2];
	state[2] = state[8];
	state[8] = state[26];
	state[26] = state[20];
	state[20] = temp;
	temp = state[5];
	state[5] = state[17];
	state[17] = state[23];
	state[23] = state[11];
	state[11] = temp;
}

void CubeState::RedRight()
{
	int temp = state[0];
	state[0] = state[18];
	state[18] = state[24];
	state[24] = state[6];
	state[6] = temp;
	temp = state[3];
	state[3] = state[9];
	state[9] = state[21];
	state[21] = state[15];
	state[15] = temp;
}

void CubeState::RedLeft()
{
	int temp = state[2];
	state[0] = state[6];
	state[6] = state[24];
	state[24] = state[18];
	state[18] = temp;
	temp = state[3];
	state[3] = state[15];
	state[15] = state[21];
	state[21] = state[9];
	state[9] = temp;
}

void CubeState::WhiteLeft()
{
	int temp = state[0];
	state[0] = state[18];
	state[18] = state[20];
	state[20] = state[2];
	state[2] = temp;
	temp = state[1];
	state[1] = state[9];
	state[9] = state[20];
	state[20] = state[11];
	state[11] = temp;
}

void CubeState::WhiteRight()
{
	int temp = state[0];
	state[0] = state[2];
	state[2] = state[20];
	state[20] = state[18];
	state[18] = temp;
	temp = state[1];
	state[1] = state[11];
	state[11] = state[20];
	state[20] = state[9];
	state[9] = temp;
}

void CubeState::YellowRight()
{
	int temp = state[6];
	state[6] = state[24];
	state[24] = state[26];
	state[26] = state[8];
	state[8] = temp;
	temp = state[7];
	state[7] = state[15];
	state[15] = state[25];
	state[25] = state[17];
	state[17] = temp;
}

void CubeState::YellowLeft()
{
	int temp = state[6];
	state[6] = state[8];
	state[8] = state[26];
	state[26] = state[24];
	state[24] = temp;
	temp = state[7];
	state[7] = state[17];
	state[17] = state[25];
	state[25] = state[15];
	state[15] = temp;
}

void CubeState::BlueRight()
{
	int temp = state[0];
	state[0] = state[6];
	state[6] = state[8];
	state[8] = state[2];
	state[2] = temp;
	temp = state[1];
	state[1] = state[3];
	state[3] = state[7];
	state[7] = state[5];
	state[5] = temp;
}

void CubeState::BlueLeft()
{
	int temp = state[0];
	state[0] = state[2];
	state[2] = state[8];
	state[8] = state[6];
	state[6] = temp;
	temp = state[1];
	state[1] = state[5];
	state[5] = state[7];
	state[7] = state[3];
	state[3] = temp;
}

void CubeState::GreenLeft()
{
	int temp = state[18];
	state[18] = state[24];
	state[24] = state[26];
	state[26] = state[20];
	state[20] = temp;
	temp = state[20];
	state[20] = state[21];
	state[21] = state[25];
	state[25] = state[23];
	state[23] = temp;
}

void CubeState::GreenRight()
{
	int temp = state[18];
	state[18] = state[20];
	state[20] = state[26];
	state[26] = state[24];
	state[24] = temp;
	temp = state[19];
	state[19] = state[21];
	state[21] = state[25];
	state[25] = state[23];
	state[23] = temp;
}