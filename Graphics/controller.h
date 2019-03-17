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
	enum state { prepare, animation, idle, paused };
	void Start();
	static Controller& getInstance();
	void Update(double);
	void Draw(CViewPoint);
	void Disassemble(int);
	int state = 0;
	std::vector<spin> way;
	Solver solver;
	CubeState cubeState;
private:
	void Action(spin, bool);
    void Addchilds(CModel*);
	std::vector<CModel> cubeModel;
	std::vector<CModel*> childs;

	Controller() { childs = std::vector<CModel*>(); };
	Controller(Controller const&) = delete;
	Controller& operator= (Controller const&) = delete;
};

#endif