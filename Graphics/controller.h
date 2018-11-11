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
	void Update(double dt);
	void Draw(CViewPoint mainCam);
	void Assemble(bool rotate);
	void Disassemble(int i);
	void Action(spin s, bool rotate);
private:
    void Addchilds(CModel* parent);
	CModel Right, Left, Up, Down, Front, Back, CenterV, CenterH, Middle;
	std::vector<CModel> cubeModel;
    std::vector<CModel*> childs;
	CModel cuuube;
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