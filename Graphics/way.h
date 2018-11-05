#ifndef WAY_H
#define WAY_H

#include <vector>
#include <map>
#include <string>

using namespace std; 

class Way
{
public:
	Way(int d);
	Way(bool force = false);
	string stateName;
	vector<vector<int>> state;
	map<string, Way*> neighbours;
	vector<Way*> map;
	int depth;
	bool operator==(Way other);
private:
	string doStateName();
	void Act(string act);
	string Invert(string act);
	void RU(), RD(), LU(), LD(), UR(), UL(), DR(), DL(), FR(), FL(), BR(), BL();
};

#endif // WAY_H
