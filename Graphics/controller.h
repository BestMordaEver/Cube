#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "viewpoint.h"
#include "model.h"
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
	void Action(std::string s, bool rotate);
private:
	CModel Right, Left, Up, Down, Front, Back, CenterV, CenterH, Middle;
	std::vector<CModel> cubeModel;
    std::vector<CModel*> childs;
	CModel cuuube;
	void RU(bool rotate), RD(bool rotate), LU(bool rotate), LD(bool rotate), UR(bool rotate), UL(bool rotate), DR(bool rotate), DL(bool rotate), FR(bool rotate), FL(bool rotate), BR(bool rotate), BL(bool rotate), MR(bool rotate), ML(bool rotate), CU(bool rotate), CR(bool rotate), CD(bool rotate), CL(bool rotate);
};

#endif