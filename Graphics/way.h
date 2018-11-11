#ifndef WAY_H
#define WAY_H

#include <vector>
#include <map>

using namespace std; 

enum spin { RD, RU, LD, LU, UR, UL, DR, DL, FR, FL, BR, BL };

struct CubeState {
	CubeState(int d);
	vector<int> state;
	map<spin, CubeState*> neighbours;
	int depth;
};

class Way
{
public:
	Way(bool force = false);
	map<int, CubeState*> map;

private:
	int doStateName(CubeState cs);
	void Act(spin act, CubeState* cs);
	spin Invert(spin act);
	void RightUp(CubeState* cs), 
		RightDown(CubeState* cs), 
		LeftUp(CubeState* cs), 
		LeftDown(CubeState* cs), 
		UpRight(CubeState* cs), 
		UpLeft(CubeState* cs), 
		DownRight(CubeState* cs), 
		DownLeft(CubeState* cs), 
		FrontRight(CubeState* cs),
		FrontLeft(CubeState* cs),
		BackRight(CubeState* cs), 
		BackLeft(CubeState* cs);
};

#endif // WAY_H
