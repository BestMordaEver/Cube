#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "viewpoint.h"
#include "model.h"
#include "way.h""
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
	void Assemble();
	void Action(spin s, bool rotate);
	static int Controller::state;
	static vector<spin> Controller::way;
	static Way Controller::solver;
private:
    void Addchilds(CModel* parent);
	CModel Right, Left, Up, Down, Front, Back, CenterV, CenterH, Middle;
	vector<CModel> cubeModel;
    vector<CModel*> childs;
	void RightUp(bool rotate),
		RightDown(bool rotate),
		LeftUp(bool rotate),
		LeftDown(bool rotate),
		UpRight(bool rotate),
		UpLeft(bool rotate),
		DownRight(bool rotate),
		DownLeft(bool rotate),
		FrontRight(bool rotate),
		FrontLeft(bool rotate),
		BackRight(bool rotate),
		BackLeft(bool rotate);
};

#endif