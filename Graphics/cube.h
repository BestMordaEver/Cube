#ifndef CUBE_H
#define CUBE_H

class Cube{
public:
	Cube();
	enum Section { blue = 'b', orange = 'o', green = 'g', red = 'r', white = 'w', yellow = 'y' };
	enum Side {F, R, B, L, U, D };
	void print(bool b);
	void RU(), RD(), LU(), LD(), UR(), UL(), DR(), DL(), FR(), FL(), BR(), BL(), MR(), ML(), CU(), CR(), CD(), CL();
private:
	Section cube[54];
	int getIndex(Side c, int x, int y);
	Section getSection(Side s, int x, int y);
	void setSection(Section n, Side c, int x, int y);
	void cubeReset();

};
#endif