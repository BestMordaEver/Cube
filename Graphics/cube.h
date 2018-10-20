#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <functional>

class Cube{
public:
	Cube();
	enum Section { blue = 'b', orange = 'o', green = 'g', red = 'r', white = 'w', yellow = 'y' };
	enum Side {F, R, B, L, U, D };
	void print(bool b);
	Section getSection(Side s, int x, int y);
	void RU(), RD(), LU(), LD(), UR(), UL(), DR(), DL(), FR(), FL(), BR(), BL(), MR(), ML(), CU(), CR(), CD(), CL();
private:
	std::vector<std::function<void()>> Spins;
	Section cube[54];
	int getIndex(Side c, int x, int y);
	void setSection(Section n, Side c, int x, int y);
	void cubeReset();
};
#endif