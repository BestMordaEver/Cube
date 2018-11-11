#include "way.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <string>

vector<spin> spins = { RD, RU, LD, LU, UR, UL, DR, DL, FR, FL, BR, BL };

Way::Way(bool force)
{
	ifstream stream("map.dat");
	if (force || !stream.good()) { // Generate map
		
		CubeState root(0);			// A solved cube
		root.state = {
			26, 25, 24, 23, 22, 21, 20, 19, 18,
			17, 16, 15, 14, 13, 12, 11, 10, 9,
			8, 7, 6, 5, 4, 3, 2, 1, 0
		};
		vector<CubeState*> parents, children;	
		parents.push_back(&root);
		map[doStateName(root)] = &root;

		for (int i = 1; i < 6; i++) { // God's number with restricted central spins and 180 degree spins is 26
			for (CubeState* parent : parents) {
				for (spin act : spins) {
					children.push_back(new CubeState(i));			// Create new state
					children.back()->state = parent->state;			// Copy it from parent
					Act(act, children.back());						// Perform action
					if (map[doStateName(*children.back())]) {		// Observe
						parent->neighbours.insert(pair<spin, CubeState*>(act, map[doStateName(*children.back())]));
						map[doStateName(*children.back())]->neighbours.insert(pair<spin, CubeState*>(Invert(act), parent));
						children.pop_back();			// If exists - it was written earlier on the same depth,
					}									// so just inject it in existing tree
					else {								// If not - create new branch
						map[doStateName(*children.back())] = children.back();
						parent->neighbours.insert(pair<spin, CubeState*>(act, children.back()));
						children.back()->neighbours.insert(pair<spin, CubeState*>(Invert(act), parent));
					}
				}
			}
			parents = children;		// Working with next line of branches
			children.clear();		// Algorythm is breadth-first
		}
	}
	else { // Read map

	}
}

int Way::doStateName(CubeState cs)
{
	string temp = "";
	for (int index : cs.state)
		temp += to_string(index) + " ";
	return hash<string>{} (temp);
}

void Way::Act(spin act, CubeState* cs) {
	if (act == RU) { RightUp(cs); return; }
	if (act == RD) { RightDown(cs); return; }
	if (act == LU) { LeftUp(cs); return; }
	if (act == LD) { LeftDown(cs); return; }
	if (act == UR) { UpRight(cs); return; }
	if (act == UL) { UpLeft(cs); return; }
	if (act == DR) { DownRight(cs); return; }
	if (act == DL) { DownLeft(cs); return; }
	if (act == FR) { FrontRight(cs); return; }
	if (act == FL) { FrontLeft(cs); return; }
	if (act == BR) { BackRight(cs); return; }
	if (act == BL) { BackLeft(cs); return; }
}

spin Way::Invert(spin act) {
	if (act == RU) return RD;
	if (act == RD) return RU;
	if (act == LU) return LD;
	if (act == LD) return LU;
	if (act == UR) return UL;
	if (act == UL) return UR;
	if (act == DR) return DL;
	if (act == DL) return DR;
	if (act == FR) return FL;
	if (act == FL) return FR;
	if (act == BR) return BL;
	if (act == BL) return BR;
}

void Way::RightDown(CubeState* cs)
{
	int temp = cs->state[2];
	cs->state[2] = cs->state[20];
	cs->state[20] = cs->state[26];
	cs->state[26] = cs->state[8];
	cs->state[8] = temp;
	temp = cs->state[5];
	cs->state[5] = cs->state[11];
	cs->state[11] = cs->state[23];
	cs->state[23] = cs->state[17];
	cs->state[17] = temp;
}

void Way::RightUp(CubeState* cs)
{
	int temp = cs->state[2];
	cs->state[2] = cs->state[8];
	cs->state[8] = cs->state[26];
	cs->state[26] = cs->state[20];
	cs->state[20] = temp;
	temp = cs->state[5];
	cs->state[5] = cs->state[17];
	cs->state[17] = cs->state[23];
	cs->state[23] = cs->state[11];
	cs->state[11] = temp;
}

void Way::LeftDown(CubeState* cs)
{
	int temp = cs->state[0];
	cs->state[0] = cs->state[18];
	cs->state[18] = cs->state[24];
	cs->state[24] = cs->state[6];
	cs->state[6] = temp;
	temp = cs->state[3];
	cs->state[3] = cs->state[9];
	cs->state[9] = cs->state[21];
	cs->state[21] = cs->state[15];
	cs->state[15] = temp;
}

void Way::LeftUp(CubeState* cs)
{
	int temp = cs->state[2];
	cs->state[0] = cs->state[6];
	cs->state[6] = cs->state[24];
	cs->state[24] = cs->state[18];
	cs->state[18] = temp;
	temp = cs->state[3];
	cs->state[3] = cs->state[15];
	cs->state[15] = cs->state[21];
	cs->state[21] = cs->state[9];
	cs->state[9] = temp;
}

void Way::UpRight(CubeState* cs)
{
	int temp = cs->state[0];
	cs->state[0] = cs->state[18];
	cs->state[18] = cs->state[20];
	cs->state[20] = cs->state[2];
	cs->state[2] = temp;
	temp = cs->state[1];
	cs->state[1] = cs->state[9];
	cs->state[9] = cs->state[19];
	cs->state[19] = cs->state[11];
	cs->state[11] = temp;
}

void Way::UpLeft(CubeState* cs)
{
	int temp = cs->state[0];
	cs->state[0] = cs->state[2];
	cs->state[2] = cs->state[20];
	cs->state[20] = cs->state[18];
	cs->state[18] = temp;
	temp = cs->state[1];
	cs->state[1] = cs->state[11];
	cs->state[11] = cs->state[19];
	cs->state[19] = cs->state[9];
	cs->state[9] = temp;
}

void Way::DownRight(CubeState* cs)
{
	int temp = cs->state[6];
	cs->state[6] = cs->state[24];
	cs->state[24] = cs->state[26];
	cs->state[26] = cs->state[8];
	cs->state[8] = temp;
	temp = cs->state[7];
	cs->state[7] = cs->state[15];
	cs->state[15] = cs->state[25];
	cs->state[25] = cs->state[17];
	cs->state[17] = temp;
}

void Way::DownLeft(CubeState* cs)
{
	int temp = cs->state[6];
	cs->state[6] = cs->state[8];
	cs->state[8] = cs->state[26];
	cs->state[26] = cs->state[24];
	cs->state[24] = temp;
	temp = cs->state[7];
	cs->state[7] = cs->state[17];
	cs->state[17] = cs->state[25];
	cs->state[25] = cs->state[15];
	cs->state[15] = temp;
}

void Way::FrontRight(CubeState* cs)
{
	int temp = cs->state[0];
	cs->state[0] = cs->state[6];
	cs->state[6] = cs->state[8];
	cs->state[8] = cs->state[2];
	cs->state[2] = temp;
	temp = cs->state[1];
	cs->state[1] = cs->state[3];
	cs->state[3] = cs->state[7];
	cs->state[7] = cs->state[5];
	cs->state[5] = temp;
}

void Way::FrontLeft(CubeState* cs)
{
	int temp = cs->state[0];
	cs->state[0] = cs->state[2];
	cs->state[2] = cs->state[8];
	cs->state[8] = cs->state[6];
	cs->state[6] = temp;
	temp = cs->state[1];
	cs->state[1] = cs->state[5];
	cs->state[5] = cs->state[7];
	cs->state[7] = cs->state[3];
	cs->state[3] = temp;
}

void Way::BackRight(CubeState* cs)
{
	int temp = cs->state[18];
	cs->state[18] = cs->state[24];
	cs->state[24] = cs->state[26];
	cs->state[26] = cs->state[20];
	cs->state[20] = temp;
	temp = cs->state[19];
	cs->state[19] = cs->state[21];
	cs->state[21] = cs->state[25];
	cs->state[25] = cs->state[23];
	cs->state[23] = temp;
}

void Way::BackLeft(CubeState* cs)
{
	int temp = cs->state[18];
	cs->state[18] = cs->state[20];
	cs->state[20] = cs->state[26];
	cs->state[26] = cs->state[24];
	cs->state[24] = temp;
	temp = cs->state[19];
	cs->state[19] = cs->state[21];
	cs->state[21] = cs->state[25];
	cs->state[25] = cs->state[23];
	cs->state[23] = temp;
}

CubeState::CubeState(int d)
{
	depth = d;
}
