#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "viewpoint.h"
#include "model.h"
#include "solver.h"
#include "hardway.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

class Controller 
{
public:
	void Start();
	static Controller& getInstance();
	void Update(double dt);
	void Draw(CViewPoint mainCam);
	void Disassemble(int i);
	int state = 0;
	std::vector<spin> way;
	Solver solver;
	HardSolver hardsolver;
	CubeState cubestate;
private:
	Controller() {};
	void Action(spin s, bool rotate);
    void Addchilds(CModel* parent);
	CModel Right, Left, Up, Down, Front, Back, CenterV, CenterH, Middle;
	std::vector<CModel> cubeModel;
	std::vector<CModel*> childs;
	void OrangeRight(bool rotate),
		OrangeLeft(bool rotate),
		RedLeft(bool rotate),
		RedRight(bool rotate),
		WhiteLeft(bool rotate),
		WhiteRight(bool rotate),
		YellowRight(bool rotate),
		YellowLeft(bool rotate),
		BlueRight(bool rotate),
		BlueLeft(bool rotate),
		GreenLeft(bool rotate),
		GreenRight(bool rotate);
public:
};

#endif