#include "hardway.h"
#include "controller.h"
#include <forward_list>

int compression = 6;
long long int states = 0;
std::string path = "tree/";
std::ofstream ostr;

HardSolver::HardSolver(bool force)
{
	if (force) { // Generate tree
		std::vector<spin> spins = { OL, OR, RL, RR, WL, WR, YL, YR, BL, BR, GL, GR };
		system("rd /s /q tree");
		system("mkdir tree");

		CubeState currentParent = CubeState();
		std::stringbuf buf = std::stringbuf(std::ios::in | std::ios::binary);
		ostr = std::ofstream("parents", std::ios::out | std::ios::trunc | std::ios::binary);
		ostr << currentParent.getContent();
		ostr.flush();
		ostr.close();

		std::cout << currentParent.getStateName() << std::endl << currentParent.getContent() << std::endl;

		std::ifstream istr(Path(currentParent), std::ios::in | std::ios::binary);	// We look for duplicates in a specific file
		
		istr.get(buf, 10);
		currentParent = CubeState(buf.str());

		std::cout << currentParent.getStateName() << std::endl << currentParent.getContent() << std::endl;

		for (int i = 1; i < 1; i++) { // God's number with restricted central spins and 180 degree spins is 26
			std::ifstream istr("parents", std::ios::in | std::ios::binary);
			do {
				istr.get(buf, 10);
				if (istr.good() && buf.str() != "") {
					CubeState currentParent = CubeState(buf.str());

					for (spin act : spins) {
						CubeState currentChild = CubeState(currentParent, act);	// Constructing child as Act from parent
						if (!exists(currentChild)) {			// We don't need duplicates
							states++;
							ostr.open(Path(currentChild), std::ios::out | std::ios::app | std::ios::binary);
							ostr << currentChild.getContent();
							ostr.flush();
							ostr.close();
							ostr.open("children", std::ios::out | std::ios::app | std::ios::binary);
							ostr << currentChild.getContent();
							ostr.flush();
							ostr.close();
						}
					}
				}
			} while (istr.good() && buf.str() != "");

			istr.close();
			system("del /f /q parents");
			system("ren children parents");
			std::cout << i << " " << states << std::endl;
		}
	}
	//system("del /f /q parents children");
	ostr.close();
}

std::vector<spin> HardSolver::Solve() {
	way.clear();
	if (Controller::getInstance().way.size())				// If you press Re-generate while cube is spinning 
		way.push_back(Controller::getInstance().way[0]);	// this will prevent it from spinning sideways
	
	CubeState state;
	std::string solved = state.getStateName();	// Solved name
	state.state = Controller::getInstance().cubeState.state;
	std::string line;
	std::string name = state.getStateName();		// Current name
	while (name != solved) {
		std::ifstream istr(Path(state), std::ios::in | std::ios::binary);
		do {
			getline(istr, line);	
			state.parent = (spin)(line[27] - (line[27] < 'A' ? 48 : 55));
		} while (line.substr(0, 27) != state.getStateName().substr(0, 27) && istr.good());
		state.Act(state.parent);		// We found current state, use Act to move up the tree
		way.push_back(state.parent);	// and remember the Act
		state.parent = (spin)(0);		// Reset parent to check if solved
		name = state.getStateName();
		istr.close();
		if (way.size() > 30) break;
	}
	return way;
}

std::string HardSolver::Path(CubeState cs)	// Compression defines the spread of children
{										// Compression ~ n files ~ 1 / filesize
	return path + cs.getStateName().substr(0, compression);	
}										// Each file should contain at least 4kb of data

bool HardSolver::exists(CubeState cs) {
	bool exists = false;
	std::string name = cs.getStateName().substr(0, 27);	// We need to compare only state
	std::string line;									// so we ignore Act (statename[27])
	std::ifstream istr(Path(cs), std::ios::in | std::ios::binary);	// We look for duplicates in a specific file
	while (istr.good() && !exists) {
		getline(istr, line);
		exists = line.substr(0, 27) == name;
	}
	istr.close();
	return exists;
}