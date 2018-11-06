#include "way.h"
#include <iostream>
#include <fstream>
#include <thread>

vector<string> spins = { "RD", "RU", "LD", "LU", "UR", "UL", "DR", "DL", "FR", "FL", "BR", "BL" };

Way::Way(bool force)
{
	ifstream stream("map.dat");
	if (force || !stream.good()) { // Generate map
		
		CubeState root(0);
		root.state = {
			{26, 25, 24, 23, 22, 21, 20, 19, 18},
			{17, 16, 15, 14, 13, 12, 11, 10, 9},
			{8, 7, 6, 5, 4, 3, 2, 1, 0}
		};
		vector<CubeState*> parents, children;
		parents.push_back(&root);

		for (int i = 1; i < 27; i++) {
			for (CubeState* parent : parents) {
				for (string act : spins) {
					children.push_back(new CubeState(i));
					Act(act, children.back());
					if (map[doStateName(*children.back())]) {

					}
					else {
						map[doStateName(*children.back())] = children.back();
						parent->neighbours.insert(pair<string, CubeState*>(act, children.back()));
						children.back()->state = parent->state;
						children.back()->neighbours.insert(pair<string, CubeState*>(Invert(act), parent));
					}
				}
			}
			parents = children;
			children.clear();
		}
	}
	else { // Read map

	}
}

string Way::doStateName(CubeState cs)
{
	string temp = "";
	for (vector<int> line : cs.state)
		for (int index : line)
			temp += to_string(index) + " ";
	return temp;
}

void Way::Act(string act, CubeState* cs) {
	if (act == "RU") { RU(cs); return; }
	if (act == "RD") { RD(cs); return; }
	if (act == "LU") { LU(cs); return; }
	if (act == "LD") { LD(cs); return; }
	if (act == "UR") { UR(cs); return; }
	if (act == "UL") { UL(cs); return; }
	if (act == "DR") { DR(cs); return; }
	if (act == "DL") { DL(cs); return; }
	if (act == "FR") { FR(cs); return; }
	if (act == "FL") { FL(cs); return; }
	if (act == "BR") { BR(cs); return; }
	if (act == "BL") { BL(cs); return; }
}

string Way::Invert(string act) {
	if (act == "RU") return "RD";
	if (act == "RD") return "RU";
	if (act == "LU") return "LD";
	if (act == "LD") return "LU";
	if (act == "UR") return "UL";
	if (act == "UL") return "UR";
	if (act == "DR") return "DL";
	if (act == "DL") return "DR";
	if (act == "FR") return "FL";
	if (act == "FL") return "FR";
	if (act == "BR") return "BL";
	if (act == "BL") return "BR";
}

void Way::RD(CubeState* cs)
{
	int temp = cs->state[0][2];
	cs->state[0][2] = cs->state[2][2];
	cs->state[2][2] = cs->state[2][8];
	cs->state[2][8] = cs->state[0][8];
	cs->state[0][8] = temp;
	temp = cs->state[0][5];
	cs->state[0][5] = cs->state[1][2];
	cs->state[1][2] = cs->state[2][5];
	cs->state[2][5] = cs->state[1][8];
	cs->state[1][8] = temp;
}

void Way::RU(CubeState* cs)
{
	int temp = cs->state[0][2];
	cs->state[0][2] = cs->state[0][8];
	cs->state[0][8] = cs->state[2][8];
	cs->state[2][8] = cs->state[2][2];
	cs->state[2][2] = temp;
	temp = cs->state[0][5];
	cs->state[0][5] = cs->state[1][8];
	cs->state[1][8] = cs->state[2][5];
	cs->state[2][5] = cs->state[1][2];
	cs->state[1][2] = temp;
}

void Way::LD(CubeState* cs)
{
	int temp = cs->state[0][0];
	cs->state[0][0] = cs->state[2][0];
	cs->state[2][0] = cs->state[2][6];
	cs->state[2][6] = cs->state[0][6];
	cs->state[0][6] = temp;
	temp = cs->state[0][3];
	cs->state[0][3] = cs->state[1][0];
	cs->state[1][0] = cs->state[2][3];
	cs->state[2][3] = cs->state[1][6];
	cs->state[1][6] = temp;
}

void Way::LU(CubeState* cs)
{
	int temp = cs->state[0][2];
	cs->state[0][0] = cs->state[0][6];
	cs->state[0][6] = cs->state[2][6];
	cs->state[2][6] = cs->state[2][0];
	cs->state[2][0] = temp;
	temp = cs->state[0][3];
	cs->state[0][3] = cs->state[1][6];
	cs->state[1][6] = cs->state[2][3];
	cs->state[2][3] = cs->state[1][0];
	cs->state[1][0] = temp;
}

void Way::UR(CubeState* cs)
{
	int temp = cs->state[0][0];
	cs->state[0][0] = cs->state[2][0];
	cs->state[2][0] = cs->state[2][2];
	cs->state[2][2] = cs->state[0][2];
	cs->state[0][2] = temp;
	temp = cs->state[0][1];
	cs->state[0][1] = cs->state[1][0];
	cs->state[1][0] = cs->state[2][1];
	cs->state[2][1] = cs->state[1][2];
	cs->state[1][2] = temp;
}

void Way::UL(CubeState* cs)
{
	int temp = cs->state[0][0];
	cs->state[0][0] = cs->state[0][2];
	cs->state[0][2] = cs->state[2][2];
	cs->state[2][2] = cs->state[2][0];
	cs->state[2][0] = temp;
	temp = cs->state[0][1];
	cs->state[0][1] = cs->state[1][2];
	cs->state[1][2] = cs->state[2][1];
	cs->state[2][1] = cs->state[1][0];
	cs->state[1][0] = temp;
}

void Way::DR(CubeState* cs)
{
	int temp = cs->state[0][6];
	cs->state[0][6] = cs->state[2][6];
	cs->state[2][6] = cs->state[2][8];
	cs->state[2][8] = cs->state[0][8];
	cs->state[0][8] = temp;
	temp = cs->state[0][7];
	cs->state[0][7] = cs->state[1][6];
	cs->state[1][6] = cs->state[2][7];
	cs->state[2][7] = cs->state[1][8];
	cs->state[1][8] = temp;
}

void Way::DL(CubeState* cs)
{
	int temp = cs->state[0][6];
	cs->state[0][6] = cs->state[0][8];
	cs->state[0][8] = cs->state[2][8];
	cs->state[2][8] = cs->state[2][6];
	cs->state[2][6] = temp;
	temp = cs->state[0][7];
	cs->state[0][7] = cs->state[1][8];
	cs->state[1][8] = cs->state[2][7];
	cs->state[2][7] = cs->state[1][6];
	cs->state[1][6] = temp;
}

void Way::FR(CubeState* cs)
{
	int temp = cs->state[0][0];
	cs->state[0][0] = cs->state[0][6];
	cs->state[0][6] = cs->state[0][8];
	cs->state[0][8] = cs->state[0][2];
	cs->state[0][2] = temp;
	temp = cs->state[0][1];
	cs->state[0][1] = cs->state[0][3];
	cs->state[0][3] = cs->state[0][7];
	cs->state[0][7] = cs->state[0][5];
	cs->state[0][5] = temp;
}

void Way::FL(CubeState* cs)
{
	int temp = cs->state[0][0];
	cs->state[0][0] = cs->state[0][2];
	cs->state[0][2] = cs->state[0][8];
	cs->state[0][8] = cs->state[0][6];
	cs->state[0][6] = temp;
	temp = cs->state[0][1];
	cs->state[0][1] = cs->state[0][5];
	cs->state[0][5] = cs->state[0][7];
	cs->state[0][7] = cs->state[0][3];
	cs->state[0][3] = temp;
}

void Way::BR(CubeState* cs)
{
	int temp = cs->state[2][0];
	cs->state[2][0] = cs->state[2][6];
	cs->state[2][6] = cs->state[2][8];
	cs->state[2][8] = cs->state[2][2];
	cs->state[2][2] = temp;
	temp = cs->state[2][1];
	cs->state[2][1] = cs->state[2][3];
	cs->state[2][3] = cs->state[2][7];
	cs->state[2][7] = cs->state[2][5];
	cs->state[2][5] = temp;
}

void Way::BL(CubeState* cs)
{
	int temp = cs->state[2][0];
	cs->state[2][0] = cs->state[2][2];
	cs->state[2][2] = cs->state[2][8];
	cs->state[2][8] = cs->state[2][6];
	cs->state[2][6] = temp;
	temp = cs->state[2][1];
	cs->state[2][1] = cs->state[2][3];
	cs->state[2][3] = cs->state[2][7];
	cs->state[2][7] = cs->state[2][5];
	cs->state[2][5] = temp;
}

CubeState::CubeState(int d)
{
	depth = d;
}
