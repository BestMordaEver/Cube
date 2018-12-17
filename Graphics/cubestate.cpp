#include "cubestate.h"
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <bitset>
#include <iostream>
//86792973
const int av[] = { 0, 0, 1, 1, 0, 2, 2, 3, 3, 4, 0, 5, 0, 0, 0, 6, 0, 7, 4, 8, 5, 9, 0, 10, 6, 11, 7 },
corners[] = { 0, 2, 6, 8, 18, 20, 24, 26 },	// Don't even ask
sides[] = { 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25 };

CubeState::CubeState()
{
	state = { // Default and solved
	0, 1, 2, 3, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25, 26
	};
	parent = (spin)0;
}

CubeState::CubeState(std::string charset) {
	state = { 
	0, 1, 2, 3, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25, 26
	};
	std::string bitset;
	
	for (int i = 0; i < 10; i++) {
		bitset += std::bitset<8>((int)charset[i]-1).to_string();
		std::cout << std::bitset<8>((int)charset[i]-1).to_string() << std::endl;
	}
		
	
	for (int i = 0; i < 8; i++) 
		state[corners[i]] = std::bitset<8>(bitset.substr(i * 3, 3)).to_ulong();

	for (int i = 0; i < 12; i++) 
		state[sides[i]] = std::bitset<8>(bitset.substr(i * 4 + 27, 4)).to_ulong();

	parent = (spin)std::bitset<8>(bitset.substr(72, 4)).to_ulong();
}

CubeState::CubeState(CubeState s, spin act)
{
	state = s.state;
	parent = act;	// parent.Act(act) == this
	Act(act);
	++parent;		// this.Act(++act) == parent
}

int CubeState::operator[](int i) { return state[i]; }

void CubeState::Act(spin act) {
	switch (act) {
	case OL: OrangeLeft(); return;
	case OR: OrangeRight(); return;
	case RL: RedLeft(); return;
	case RR: RedRight(); return;
	case WL: WhiteLeft(); return;
	case WR: WhiteRight(); return;
	case YL: YellowLeft(); return;
	case YR: YellowRight(); return;
	case BL: BlueLeft(); return;
	case BR: BlueRight(); return;
	case GL: GreenLeft(); return;
	case GR: GreenRight(); return;
	}
}

std::string CubeState::getStateName()
{
	std::stringstream ss;
	copy(state.begin(), state.end(), std::ostream_iterator<char>(ss));
	std::string temp = ss.str() + (char)parent;
	for (auto it = temp.begin(); it != temp.end(); it++)
		*it += *it < 10 ? 48 : 55;	// if Statename[i] < 10 = 0-9 else A-Z
	return temp;					// (int)'0' = 49, (int)'A' = 54
}

std::string CubeState::getContent() {
	std::bitset<80> container(0);
	for (int i = 0; i < 8; i++) {
		int temp = av[state[corners[i]]];
		container[i * 3] = temp % 2;
		temp >>= 1;
		container[i * 3 + 1] = temp % 2;
		temp >>= 1;
		container[i * 3 + 2] = temp;
	}

	for (int i = 0; i < 12; i++) {
		int temp = av[state[sides[i]]];	// I laugh in your face
		container[i * 4 + 24] = temp % 2;
		temp >>= 1;
		container[i * 4 + 25] = temp % 2;
		temp >>= 1;
		container[i * 4 + 26] = temp % 2;
		temp >>= 1;
		container[i * 4 + 27] = temp;
	}

	int temp = parent;	
	container[72] = temp % 2;
	temp >>= 1;
	container[73] = temp % 2;
	temp >>= 1;
	container[74] = temp % 2;
	temp >>= 1;
	container[75] = temp;
	std::string result;

	for (int i = 0; i < 10; i++) 
		result += std::bitset<8>(container.to_string().substr(i, i * 8)).to_ulong() + 1;
	
 	return result;
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
	int temp = state[0];
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
	state[9] = state[19];
	state[19] = state[11];
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
	state[11] = state[19];
	state[19] = state[9];
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
	temp = state[19];
	state[19] = state[21];
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
	state[19] = state[23];
	state[23] = state[25];
	state[25] = state[21];
	state[21] = temp;
}