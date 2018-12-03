#include "hardway.h"
#include "controller.h"
#include <forward_list>

int compression = 6;
std::string path = "tree/";

HardSolver::HardSolver(bool force)
{
	if (force) { // Generate tree
		std::vector<spin> spins = { OL, OR, RL, RR, WL, WR, YL, YR, BL, BR, GL, GR };
		system("rd /s /q tree");
		system("mkdir tree");

		std::forward_list<std::unique_ptr<CubeState>> parents, children;
		parents.emplace_front(std::unique_ptr<CubeState>(new CubeState()));

		for (int i = 1; i < 26; i++) { // God's number with restricted central spins and 180 degree spins is 26
			for (auto it = parents.begin(); it != parents.end(); ) {
				for (spin act : spins) {
					children.emplace_front(std::unique_ptr<CubeState>(new CubeState((*it).get(), act)));	// Constructing child as Act from parent
					if (exists(children.front().get())) {			// We don't need duplicates
						children.pop_front();
					}
					else {
						ostr = std::ofstream(Path(children.front().get()), std::fstream::out | std::fstream::app);
						ostr << children.front()->doStateName() << std::endl;
 						ostr.close();
					}
				}
				it++;
				parents.pop_front();
			}
			parents.swap(children);
			std::cout << i << " " << std::distance(parents.begin(), parents.end()) << std::endl;
		}
	}
	ostr.close();
}

std::vector<spin> HardSolver::Solve() {
	way.clear();
	if (Controller::getInstance().way.size())				// If you press Re-generate while cube is spinning 
		way.push_back(Controller::getInstance().way[0]);	// this will prevent it from spinning sideways
	
	CubeState state;
	std::string solved = state.doStateName();	// Solved name
	state.state = Controller::getInstance().cubestate.state;
	std::string line;
	std::string name = state.doStateName();		// Current name
	while (name != solved) {
		std::ifstream istr(Path(&state), std::fstream::in);
		do {
			getline(istr, line);	
			state.parent = (spin)(line[27] - (line[27] < 'A' ? 48 : 55));
		} while (line.substr(0, 27) != state.doStateName() && istr.good());	
		state.Act(state.parent);		// We found current state, use Act to move up the tree
		way.push_back(state.parent);	// and remember the Act
		state.parent = (spin)(0);		// Reset parent to check if solved
		name = state.doStateName();
		istr.close();
	}
	return way;
}

std::string HardSolver::Path(CubeState * cs)	// Compression defines the spread of children
{										// Compression ~ n files ~ 1 / filesize
	return path + cs->doStateName().substr(0, compression);	
}										// Each file should contain at least 4kb of data

bool HardSolver::exists(CubeState* cs) {
	bool exists = false;
	std::string name = cs->doStateName().substr(0, 27);	// We need to compare only state
	std::string line;									// so we ignore Act (statename[27])
	std::ifstream istr(Path(cs), std::fstream::in);			// We look for duplicates in a specific file
	while (istr.good() && !exists) {
		getline(istr, line);
		exists = line.substr(0, 27) == name;
	}
	istr.close();
	return exists;
}