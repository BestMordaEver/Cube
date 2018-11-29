#include "hardway.h"
#include "controller.h"
#include <forward_list>

int compression = 15;
string path = "tree/";

HardSolver::HardSolver(bool force)
{
	if (force) { // Generate tree
		vector<spin> spins = { OL, OR, RL, RR, WL, WR, YL, YR, BL, BR, GL, GR };
		system("rd /s /q tree");
		system("mkdir tree");

		forward_list<CubeState*> parents, children;
		parents.emplace_front(new CubeState());

		for (int i = 1; i < 26; i++) { // God's number with restricted central spins and 180 degree spins is 26
			for (CubeState* parent : parents) {
				for (spin act : spins) {
					children.emplace_front(new CubeState(parent, act));	// Constructing child as Act from parent
					if (exists(children.front())) {			// We don't need duplicates
						children.pop_front();
					}
					else {
						ostr = ofstream(Path(children.front()), fstream::out | fstream::app);
						ostr << children.front()->doStateName() << endl;
						ostr.flush();
 						ostr.close();
					}
				}
			}
			parents.swap(children);	// Algorithm is breadth-first
			children.clear();		// this allows to ignore duplicates
			cout << i << endl;
		}
	}
	ostr.close();
}

vector<spin> HardSolver::Solve() {
	way.clear();
	if (Controller::getInstance().way.size())				// If you press Re-generate while cube is spinning 
		way.push_back(Controller::getInstance().way[0]);	// this will prevent it from spinning sideways
	
	CubeState state;
	string solved = state.doStateName();	// Solved name
	state.state = Controller::getInstance().cubestate.state;
	char line[64];
	string name = state.doStateName();		// Current name
	while (name != solved) {
		ifstream istr(Path(&state), fstream::in);
		do {
			istr.getline(line, 64);	// Statename[i] < 10 = 0-9 else A-Z
			state.parent = (spin)(line[27] - (line[27] < 'A' ? 48 : 55));
		} while (line != state.doStateName());	// (int)'0' = 49, (int)'A' = 54
		state.Act(state.parent);	// We found current state, use Act to move up the tree
		way.push_back(state.parent);// and remember the Act
		state.parent = (spin)(0);	// Reset parent to check if solved
		name = state.doStateName();	
		istr.close();
	}
	return way;
}

string HardSolver::Path(CubeState * cs)	// Compression defines the spread of children
{										// Compression ~ n files ~ 1 / filesize
	return path + cs->doStateName().substr(0, compression);	
}										// Each file should contain at least 4kb of data

bool HardSolver::exists(CubeState* cs) {
	bool exists = false;
	string name = cs->doStateName().substr(0, 27);	// We need to compare only state
	char line[32];									// so we ignore Act (statename[27])
	ifstream istr(Path(cs), fstream::in);			// We look for duplicates in a specific file
	while (istr.good() && !exists) {
		istr.getline(line, 28);
		exists = line == name;
		//if (exists)
			//cout << line << endl;
	}
	istr.close();
	return exists;
}