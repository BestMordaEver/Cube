#ifndef WAY_H
#define WAY_H

#include <vector>
#include <map>
#include <string>

using namespace std; 

struct CubeState {
	CubeState(int d);
	vector<vector<int>> state;
	map<string, CubeState*> neighbours;
	int depth;
};

class Way
{
public:
	Way(bool force = false);
	map<string, CubeState*> map;
private:
	string doStateName(CubeState cs);
	void Act(string act, CubeState* cs);
	string Invert(string act);
	void RU(CubeState* cs), RD(CubeState* cs), LU(CubeState* cs), LD(CubeState* cs), UR(CubeState* cs), UL(CubeState* cs), DR(CubeState* cs), DL(CubeState* cs), FR(CubeState* cs), FL(CubeState* cs), BR(CubeState* cs), BL(CubeState* cs);
};

#endif // WAY_H
