#include "hardway.h"
#include "controller.h"
#include <forward_list>
#include <Windows.h>

vector<spin> spins = { OL, OR, RL, RR, WL, WR, YL, YR, BL, BR, GL, GR };

HardWay::HardWay(bool force)
{
	if (force) { // Generate map
		ostr = ofstream(path, fstream::out);
		forward_list<CubeState*> parents, children;
		parents.emplace_front(new CubeState());
		write(parents.front());
		for (int i = 1; i < 26; i++) { // God's number with restricted central spins and 180 degree spins is 26
			for (CubeState* parent : parents) {
				for (spin act : spins) {
					children.emplace_front(new CubeState(parent, act));
					if (exists(children.front())) {
						children.pop_front();
					}
					else {
						write(children.front());
					}
				}
			}
			parents.swap(children);		// Working with next line of branches
			children.clear();			// Algorithm is breadth-first
			cout << i;
		}
	}
	ostr.close();
}

vector<spin> HardWay::Solve() {
	way.clear();
	if (Controller::way.size())
		way.push_back(Controller::way[0]);
	
	CubeState state;
	string solved = state.doStateName();
	state.state = Controller::cubestate.state;
	char line[64];
	string name = state.doStateName();
	while (name != solved) {
		ifstream istr(path, fstream::in);
		cout << name << endl;
		do {
			istr.getline(line, 64);
			state.parent = (spin)(line[27]-50);
		} while (line != state.doStateName());
		state.Act(++state.parent);
		way.push_back(state.parent);
		cout << state.parent << endl;
		state.parent = (spin)(solved[27]-50);
		name = state.doStateName();
		istr.close();
	}
	return way;
}

void HardWay::write(CubeState* cs) {
	ostr << cs->doStateName() << endl;
}

bool HardWay::exists(CubeState* cs) {
	bool flag = false;
	string name = cs->doStateName();
	char line[64];
	ifstream istr(path, fstream::in);
	while (istr.good() && !flag) {
		istr.getline(line, 64);
		flag = line == name;
	}
	istr.close();
	return flag;
}