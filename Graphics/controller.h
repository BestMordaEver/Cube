#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "viewpoint.h"
#include "model.h"
#include "cube.h"
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
	void Update(double dt);
	void Draw(CViewPoint mainCam);
private:
	CModel Right, Left, Up, Down, Front, Back, CenterV, CenterH, Middle;
	std::vector<CModel> cubeModel;
	Cube cubeMatrix;
	double animationLock;
	void RU(), RD(), LU(), LD(), UR(), UL(), DR(), DL(), FR(), FL(), BR(), BL(), MR(), ML(), CU(), CR(), CD(), CL();
};

#endif