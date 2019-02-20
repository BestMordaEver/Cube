#include "controller.h"
#include "logger.h"
#include "compile.h"
#include <time.h>
#include <algorithm>
#include <fstream>

std::vector<GLfloat> square = {
    // Blue
    -0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,

    // Orange
    -0.5f, 0.5f, 0.5f,  1.0f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.5f,  1.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.5f,  1.0f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.5f,  1.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.5f,  1.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.5f,  1.0f, 0.5f, 0.0f,

    // Green
    0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,

    // Red
    -0.5f, 0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

    // White
    -0.5f, 0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,  1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f,  1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,  1.0f, 1.0f, 1.0f,

    // Yellow
    -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.2f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.2f,
    -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 0.2f,
    0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 0.2f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.2f,
    -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 0.2f
};

int animstate = 0;
double timer = 0, counter = 0;
double step = glm::pi<double>() / 100;

float getDistance(CModel const* lhs, CModel const* rhs)
{
    return glm::distance(lhs->getPosition(), rhs->getPosition());
}

void Controller::Start()
{
	Compiler::SyntaxAnalysis();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cubeModel.emplace_back(square);
				cubeModel.back().setPosition(glm::vec3(-1.0f + i, 1.0f - j, -1.0f + k) * 1.05f, cubeModel.back().getEulers());
			}
		}
	}
	cubeState = CubeState();
	std::vector<CModel*> copy;
	transform(cubeModel.begin(), cubeModel.end(), std::back_inserter(copy), [](CModel& model) { return &model; });
	std::sort(copy.begin(), copy.end(), [model = &cubeModel[cubeState[13]]] (CModel const* lhs, CModel const* rhs) {return getDistance(lhs, model) < getDistance(rhs, model); });
	childs.resize(20);
	std::copy(copy.begin() + 7, copy.end(), childs.begin());
	state = contactive;
	Disassemble(100);
	way = solver.Solve();
};

void Controller::Update(double dt)
{
    timer += dt;
    switch (state)
    {
	case contactive:
		Action(way.front(), false);
		state = 1;
		timer = 0;
		return;
	case animactive:
		if (timer > counter)
		{
			Action(way.front(), true);
			counter += step / 2;  // Tweak this to control animation speed. 
			animstate++;
		}
		if (animstate == 50)
		{
			state = 0;
			timer = 0;
			counter = 0;
			animstate = 0;
			for (int j = 0; j < cubeModel.size(); j++)
				cubeModel[j].clearChilds();
			way.erase(way.begin());
			if (way.size() == 0) 
				state = 2;  // Assembled
		}
		return;
    }
}

void Controller::Draw(CViewPoint mainCam)
{
    for (int i = 0; i < cubeModel.size(); i++)
        mainCam.drawModel(cubeModel[i]);
}

void Controller::Action(spin s, bool rotate)     // Rotate false is for preparation, assigns children to centers. True makes actual rotation
{   
	glm::vec3 spinvec;
	int section = 0;
	switch (s) {
	case OR: section = 14; spinvec = glm::vec3(0, 0, -step); break;
	case OL: section = 14; spinvec = glm::vec3(0, 0, step); break;
	case RL: section = 12; spinvec = glm::vec3(0, 0, step); break;
	case RR: section = 12; spinvec = glm::vec3(0, 0, -step); break;
	case WL: section = 10; spinvec = glm::vec3(0, step, 0); break;
	case WR: section = 10; spinvec = glm::vec3(0, -step, 0); break;
	case YR: section = 16; spinvec = glm::vec3(0, step, 0); break;
	case YL: section = 16; spinvec = glm::vec3(0, -step, 0); break;
	case BR: section = 4; spinvec = glm::vec3(step, 0, 0); break;
	case BL: section = 4; spinvec = glm::vec3(-step, 0, 0); break;
	case GL: section = 22; spinvec = glm::vec3(step, 0, 0); break;
	case GR: section = 22; spinvec = glm::vec3(-step, 0, 0); break;
	}

	if (rotate)
	{
		cubeModel[cubeState[section]].rotate(spinvec);
	}
	else
	{
		logger::LogAction(s);
		Addchilds(&cubeModel[cubeState[section]]);
		solver.rotate(s);
		cubeState.Act(s);
	}
}

void Controller::Disassemble(int i)
{
	logger::LogDisassembly(true);
	step = glm::pi<double>() / 2;
	srand(time(NULL));
	for (; i > 0; i--)
	{
		int temp = rand() % 12;
		Action((spin)temp, false); Action((spin)temp, true);
		for (int j = 0; j < cubeModel.size(); j++)
			cubeModel[j].clearChilds();
	}
	step = glm::pi<double>() / 100;
	logger::LogDisassembly(false);
}

void Controller::Addchilds(CModel* parent)
{
	std::sort(childs.begin(), childs.end(), [model = parent](CModel const* lhs, CModel const* rhs) { return getDistance(lhs, model) < getDistance(rhs, model); });
    parent->AddChild(childs[0]);
    parent->AddChild(childs[1]);
    parent->AddChild(childs[2]);
    parent->AddChild(childs[3]);
    parent->AddChild(childs[4]);
    parent->AddChild(childs[5]);
    parent->AddChild(childs[6]);
    parent->AddChild(childs[7]);
}

Controller &Controller::getInstance()
{
	static Controller instance;
	return instance;
}