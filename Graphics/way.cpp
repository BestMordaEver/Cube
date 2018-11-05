#include "way.h"
#include <iostream>
#include <fstream>

vector<string> spins = { "RD", "RU", "LD", "LU", "UR", "UL", "DR", "DL", "FR", "FL", "BR", "BL" };

Way::Way(int d) {
	depth = d;
}

Way::Way(bool force)
{
	ifstream stream("map.dat");
	if (force || !stream.good()) { // Generate map
		depth = 0;
		state = {
			{26, 25, 24, 23, 22, 21, 20, 19, 18},
			{17, 16, 15, 14, 13, 12, 11, 10, 9},
			{8, 7, 6, 5, 4, 3, 2, 1, 0}
		};
		doStateName();

		vector<Way*> parents, children;
		parents.push_back(this);
		map.push_back(this);

		for (int i = 1; i < 27; i++) {
			for (Way* parent : parents) {
				bool flag = true;
				for (vector<Way*>::iterator it = map.begin(); it < map.end()-1; it++) {
					if (*it == map.back()) {
						if ((*it)->depth < map.back()->depth)
							map.back() = *it;
						else
							*it = map.back();
						flag = false;
						break;
					}
				}
				if (flag) {
					for (string act : spins) {
						map.push_back(new Way(i));
						children.push_back(map.back());
						parent->neighbours.insert(pair<string, Way*>(act, map.back()));
						map.back()->map.~vector();
						map.back()->state = parent->state;
						map.back()->Act(act);
						map.back()->neighbours.insert(pair<string, Way*>(Invert(act), parent));
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

bool Way::operator==(Way other)
{
	return (doStateName() == other.doStateName());
}

string Way::doStateName()
{
	string temp = "";
	for (vector<int> line : state)
		for (int index : line)
			temp += to_string(index) + " ";
	stateName = temp;
	return temp;
}

void Way::Act(string act) {
	if (act == "RU") { RU(); return; }
	if (act == "RD") { RD(); return; }
	if (act == "LU") { LU(); return; }
	if (act == "LD") { LD(); return; }
	if (act == "UR") { UR(); return; }
	if (act == "UL") { UL(); return; }
	if (act == "DR") { DR(); return; }
	if (act == "DL") { DL(); return; }
	if (act == "FR") { FR(); return; }
	if (act == "FL") { FL(); return; }
	if (act == "BR") { BR(); return; }
	if (act == "BL") { BL(); return; }
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

void Way::RD()
{
	int temp = state[0][2];
	state[0][2] = state[2][2];
	state[2][2] = state[2][8];
	state[2][8] = state[0][8];
	state[0][8] = temp;
	temp = state[0][5];
	state[0][5] = state[1][2];
	state[1][2] = state[2][5];
	state[2][5] = state[1][8];
	state[1][8] = temp;
}

void Way::RU()
{
	int temp = state[0][2];
	state[0][2] = state[0][8];
	state[0][8] = state[2][8];
	state[2][8] = state[2][2];
	state[2][2] = temp;
	temp = state[0][5];
	state[0][5] = state[1][8];
	state[1][8] = state[2][5];
	state[2][5] = state[1][2];
	state[1][2] = temp;
}

void Way::LD()
{
	int temp = state[0][0];
	state[0][0] = state[2][0];
	state[2][0] = state[2][6];
	state[2][6] = state[0][6];
	state[0][6] = temp;
	temp = state[0][3];
	state[0][3] = state[1][0];
	state[1][0] = state[2][3];
	state[2][3] = state[1][6];
	state[1][6] = temp;
}

void Way::LU()
{
	int temp = state[0][2];
	state[0][0] = state[0][6];
	state[0][6] = state[2][6];
	state[2][6] = state[2][0];
	state[2][0] = temp;
	temp = state[0][3];
	state[0][3] = state[1][6];
	state[1][6] = state[2][3];
	state[2][3] = state[1][0];
	state[1][0] = temp;
}

void Way::UR()
{
	int temp = state[0][0];
	state[0][0] = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = state[0][2];
	state[0][2] = temp;
	temp = state[0][1];
	state[0][1] = state[1][0];
	state[1][0] = state[2][1];
	state[2][1] = state[1][2];
	state[1][2] = temp;
}

void Way::UL()
{
	int temp = state[0][0];
	state[0][0] = state[0][2];
	state[0][2] = state[2][2];
	state[2][2] = state[2][0];
	state[2][0] = temp;
	temp = state[0][1];
	state[0][1] = state[1][2];
	state[1][2] = state[2][1];
	state[2][1] = state[1][0];
	state[1][0] = temp;
}

void Way::DR()
{
	int temp = state[0][6];
	state[0][6] = state[2][6];
	state[2][6] = state[2][8];
	state[2][8] = state[0][8];
	state[0][8] = temp;
	temp = state[0][7];
	state[0][7] = state[1][6];
	state[1][6] = state[2][7];
	state[2][7] = state[1][8];
	state[1][8] = temp;
}

void Way::DL()
{
	int temp = state[0][6];
	state[0][6] = state[0][8];
	state[0][8] = state[2][8];
	state[2][8] = state[2][6];
	state[2][6] = temp;
	temp = state[0][7];
	state[0][7] = state[1][8];
	state[1][8] = state[2][7];
	state[2][7] = state[1][6];
	state[1][6] = temp;
}

void Way::FR()
{
	int temp = state[0][0];
	state[0][0] = state[0][6];
	state[0][6] = state[0][8];
	state[0][8] = state[0][2];
	state[0][2] = temp;
	temp = state[0][1];
	state[0][1] = state[0][3];
	state[0][3] = state[0][7];
	state[0][7] = state[0][5];
	state[0][5] = temp;
}

void Way::FL()
{
	int temp = state[0][0];
	state[0][0] = state[0][2];
	state[0][2] = state[0][8];
	state[0][8] = state[0][6];
	state[0][6] = temp;
	temp = state[0][1];
	state[0][1] = state[0][5];
	state[0][5] = state[0][7];
	state[0][7] = state[0][3];
	state[0][3] = temp;
}

void Way::BR()
{
	int temp = state[2][0];
	state[2][0] = state[2][6];
	state[2][6] = state[2][8];
	state[2][8] = state[2][2];
	state[2][2] = temp;
	temp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = state[2][7];
	state[2][7] = state[2][5];
	state[2][5] = temp;
}

void Way::BL()
{
	int temp = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = state[2][8];
	state[2][8] = state[2][6];
	state[2][6] = temp;
	temp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = state[2][7];
	state[2][7] = state[2][5];
	state[2][5] = temp;
}