#include "hardway.h"
#include "controller.h"
#include <forward_list>
#include <thread>
#include <fstream>
#include <mutex>
#include <condition_variable>

const int compression = 15, threadsC = 4;
std::string path = "tree/";
CubeState* threadCube[threadsC];
std::vector<spin> spins = { OL, OR, RL, RR, WL, WR, YL, YR, BL, BR, GL, GR };
std::forward_list<CubeState*> parents, children;
std::ofstream ostr;
std::vector<std::thread> threads;
std::mutex mtx;
std::condition_variable cv;
int readyCount = 0;

void Ready() {
	if (++readyCount == threadsC) {
		readyCount = 0;
		for (int i = 0; i < threadsC - 1; i++)
			for (int j = i + 1; j < threadsC; j++)
				if (threadCube[i] && threadCube[j] && threadCube[i]->doStateName().substr(0, 27) == threadCube[j]->doStateName().substr(0, 27)) {
					delete(threadCube[j]);
					threadCube[j] = NULL;
				}
		std::unique_lock<std::mutex> lck(mtx);
		cv.notify_all();
	}
	else
		cv.wait(std::unique_lock<std::mutex>(mtx));
}

HardSolver::HardSolver(bool force)
{
	if (force) { // Generate tree
		system("rd /s /q tree");
		system("mkdir tree");

		parents.emplace_front(new CubeState());

		for (int i = 1; i < 26; i++) { // God's number with restricted central and 180 degree spins is 26
			for (auto it = parents.begin(); it != parents.end(); ) {
				threads.emplace_back(&HardSolver::ThreadTask, this, 0, *it);
				threads.emplace_back(&HardSolver::ThreadTask, this, 1, *it);
				threads.emplace_back(&HardSolver::ThreadTask, this, 2, *it);
				threads.emplace_back(&HardSolver::ThreadTask, this, 3, *it);

				for (std::thread& t : threads) t.join();
				threads.clear();

				it++;
				parents.pop_front();
			}
			parents.swap(children);	// Algorithm is breadth-first which allows to discard duplicates without any problems
			//std::cout << i << std::endl;
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
			getline(istr, line);	// Statename[i] < 10 = 0-9 else A-Z
			state.parent = (spin)(line[27] - (line[27] < 'A' ? 48 : 55));
		} while (line.substr(0, 27) != state.doStateName() && istr.good());	// (int)'0' = 49, (int)'A' = 54
		state.Act(state.parent);	// We found current state, use Act to move up the tree
		way.push_back(state.parent);// and remember the Act
		state.parent = (spin)(0);	// Reset parent to check if solved
		name = state.doStateName();
		istr.close();
	}
	return way;
}

void HardSolver::ThreadTask(int ind, CubeState* parent) {
	for (int i = ind * 3; i < ind * 3 + 3; i++) {
		std::cout << "Starting " << i << std::endl;

		threadCube[ind] = new CubeState(parent, spins[i]);	// Constructing child as Act from parent
		Ready();	// Waiting for everybody else to create their child

		if (exists(threadCube[ind])) 	// We don't need duplicates
			threadCube[ind] = NULL;
		else {
			ostr.open(Path(threadCube[ind]), std::fstream::out | std::fstream::app);
			ostr << threadCube[ind]->doStateName() << std::endl;
			ostr.flush();
			ostr.close();
			children.push_front(threadCube[ind]);
		}
			
		std::cout << "Done with " << i << std::endl;
	}
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