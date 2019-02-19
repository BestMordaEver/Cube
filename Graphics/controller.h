#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "viewpoint.h"
#include "logger.h"
#include "model.h"
#include "solver.h"
#include "cubestate.h"
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
	CubeState cubeState;
private:
	void Action(spin s, bool rotate);
    void Addchilds(CModel* parent);
	std::vector<CModel> cubeModel;
	std::vector<CModel*> childs;

	Controller() { childs = std::vector<CModel*>(); };
	Controller(Controller const&) = delete;
	Controller& operator= (Controller const&) = delete;
};

#endif