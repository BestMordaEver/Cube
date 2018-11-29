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
	Controller();
	Controller(int a);
	void Update(double dt);
	void Draw(CViewPoint mainCam);
	void Disassemble(int i);
	void Action(spin s, bool rotate);
	static int Controller::state;
	static vector<spin> Controller::way;
	static Solver Controller::solver;
	static HardWay Controller::hardsolver;
	static CubeState Controller::cubestate;
private:
    void Addchilds(CModel* parent);
	CModel Right, Left, Up, Down, Front, Back, CenterV, CenterH, Middle;
	vector<CModel> cubeModel;
    vector<CModel*> childs;
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
};

#endif