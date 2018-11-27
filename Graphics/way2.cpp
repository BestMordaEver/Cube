#include "way2.h"
#include <fstream>
#include <string>

vector<spin> spins = { OL, OR, RR, RL, WL, WR, YR, YL, BR, BL, GL, GR };

HardWay::HardWay(bool force)
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
						map[doStateName(*children.back())]->neighbours.insert(pair<spin, CubeState*>(++act, parent));
						children.pop_back();			// If exists - it was written earlier on the same depth,
					}									// so just inject it in existing tree
					else {								// If not - create new branch
						map[doStateName(*children.back())] = children.back();
						parent->neighbours.insert(pair<spin, CubeState*>(act, children.back()));
						children.back()->neighbours.insert(pair<spin, CubeState*>(++act, parent));
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

int HardWay::doStateName(CubeState cs)
{
	string temp = "";
	for (int index : cs.state)
		temp += to_string(index) + " ";
	return hash<string>{} (temp);
}