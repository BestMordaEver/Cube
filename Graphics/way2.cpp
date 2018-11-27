#include "way2.h"
#include "controller.h"
#include <string>
#include <fstream>

vector<spin> spins = { OL, OR, RR, RL, WL, WR, YR, YL, BR, BL, GL, GR };

HardWay::HardWay(bool force)
{
	if (force) { // Generate map
		
		vector<CubeState*> parents, children;
		parents.push_back(&CubeState(0));
		write(parents.back());

		for (int i = 1; i < 26; i++) { // God's number with restricted central spins and 180 degree spins is 26
			for (CubeState* parent : parents) {
				for (spin act : spins) {
					children.push_back(new CubeState(i));			// Create new state
					children.back()->state = parent->state;			// Copy it from parent
					children.back()->Act(act);						// Perform action
					if (map[children.back()->doStateName()]) {		// Observe
						parent->neighbours.insert(pair<spin, CubeState*>(act, map[children.back()->doStateName()]));
						map[children.back()->doStateName()]->neighbours.insert(pair<spin, CubeState*>(++act, parent));
						children.pop_back();			// If exists - it was written earlier on the same depth,
					}									// so just inject it in existing tree
					else {								// If not - create new branch
						map[children.back()->doStateName()] = children.back();
						parent->neighbours.insert(pair<spin, CubeState*>(act, children.back()));
						children.back()->neighbours.insert(pair<spin, CubeState*>(++act, parent));
					}
				}
			}
			parents = children;		// Working with next line of branches
			children.clear();		// Algorythm is breadth-first
		}
	}
}

vector<spin> HardWay::Solve() {
	
}

void HardWay::write(CubeState* cs) {
	ofstream str = ofstream(path + to_string(cs->doStateName()));
	//str.write(cs->state, cs->state.size());
}

CubeState HardWay::read(string s) {

}