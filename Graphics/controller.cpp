#include "controller.h"
#include <time.h>
#include <algorithm>

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

	cubestate = CubeState();
	std::vector<CModel*> copy;
	transform(cubeModel.begin(), cubeModel.end(), std::back_inserter(copy), [](CModel& model) { return &model; });
	std::sort(copy.begin(), copy.end(), [model = &cubeModel[cubestate[13]]] (CModel const* lhs, CModel const* rhs) {return getDistance(lhs, model) < getDistance(rhs, model); });
	childs.resize(20);
	std::copy(copy.begin() + 7, copy.end(), childs.begin());
	state = 2;
	hardsolver = HardSolver(true); //!!!!!!!!!!!!!!!!
	Disassemble(20);
	way = hardsolver.Solve();
	//solver = Solver();
	//Disassemble(100);
	//way = solver.Solve();
	//step = glm::pi<double>() / 2;
	//RedLeft(false); RedLeft(true); 
	//cubestate.print();
	//RedLeft(false); RedLeft(true); 
	//cubestate.print();
	//WhiteLeft(false); WhiteLeft(true);
	//cubestate.print();
	//step = glm::pi<double>() / 100;
};

void Controller::Update(double dt)
{
    timer += dt;
    switch (state)
    {
	case 0:
		Action(way.front(), false);
		state = 1;
		timer = 0;
		return;
	case 1:
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

void Controller::Action(spin s, bool rotate)     // Rotate false is for preparation, assigns children to centers
{   
	if (s == OR) { OrangeRight(rotate); return; }              // True makes actual rotation
	if (s == OL) { OrangeLeft(rotate); return; }
	if (s == RL) { RedLeft(rotate); return; }
	if (s == RR) { RedRight(rotate); return; }
	if (s == WL) { WhiteLeft(rotate); return; }
	if (s == WR) { WhiteRight(rotate); return; }
	if (s == YR) { YellowRight(rotate); return; }
	if (s == YL) { YellowLeft(rotate); return; }
	if (s == BR) { BlueRight(rotate); return; }
	if (s == BL) { BlueLeft(rotate); return; }
	if (s == GL) { GreenLeft(rotate); return; }
	if (s == GR) { GreenRight(rotate); return; }
}

void Controller::Disassemble(int i)
{
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
}

Controller & Controller::getInstance()
{
	static Controller instance;
	return instance;
}

void Controller::Addchilds(CModel* parent)
{
    sort(childs.begin(), childs.end(), [model = parent](CModel const* lhs, CModel const* rhs) { return getDistance(lhs, model) < getDistance(rhs, model); });
    parent->AddChild(childs[0]);
    parent->AddChild(childs[1]);
    parent->AddChild(childs[2]);
    parent->AddChild(childs[3]);
    parent->AddChild(childs[4]);
    parent->AddChild(childs[5]);
    parent->AddChild(childs[6]);
    parent->AddChild(childs[7]);
}

void Controller::OrangeLeft(bool rotate)
{
    if (rotate)
    {
        cubeModel[cubestate[14]].rotate(glm::vec3(0, 0, step));
    }
    else
    {
        Addchilds(&cubeModel[cubestate[14]]);
		solver.rotate_counter_clock('o');
		cubestate.OrangeLeft();
    }
}

void Controller::OrangeRight(bool rotate)
{
    if (rotate)
    {
        cubeModel[cubestate[14]].rotate(glm::vec3(0, 0, -step));
    }
    else
    {
        Addchilds(&cubeModel[cubestate[14]]);
		solver.rotate_clock('o');
		cubestate.OrangeRight();
    }
}

void Controller::RedRight(bool rotate)
{
    if (rotate)
    {
        cubeModel[cubestate[12]].rotate(glm::vec3(0, 0, step));
    }
    else
    {
        Addchilds(&cubeModel[cubestate[12]]);
		solver.rotate_clock('r');
		cubestate.RedRight();
    }
}

void Controller::RedLeft(bool rotate)
{
    if (rotate)
    {
        cubeModel[cubestate[12]].rotate(glm::vec3(0, 0, -step));
    }
    else
    {
        Addchilds(&cubeModel[cubestate[12]]);
		solver.rotate_counter_clock('r');
		cubestate.RedLeft();
    }
}

void Controller::WhiteLeft(bool rotate)
{
    if (rotate)
    {
        cubeModel[cubestate[10]].rotate(glm::vec3(0, step, 0));
    }
    else
    {
        Addchilds(&cubeModel[cubestate[10]]);
		solver.rotate_counter_clock('w');
		cubestate.WhiteLeft();
    }
}

void Controller::WhiteRight(bool rotate)
{
    if (rotate)
    {
        cubeModel[cubestate[10]].rotate(glm::vec3(0, -step, 0));
    }
    else
    {
        Addchilds(&cubeModel[cubestate[10]]);
		solver.rotate_clock('w');
		cubestate.WhiteRight();
    }
}

void Controller::YellowRight(bool rotate)
{
    if (rotate)
    {
        cubeModel[cubestate[16]].rotate(glm::vec3(0, step, 0));
    }
    else
    {
        Addchilds(&cubeModel[cubestate[16]]);
		solver.rotate_clock('y');
		cubestate.YellowRight();
    }
}

void Controller::YellowLeft(bool rotate)
{
    if (rotate)
    {
        cubeModel[cubestate[16]].rotate(glm::vec3(0, -step, 0));
    }
    else
    {
        Addchilds(&cubeModel[cubestate[16]]);
		solver.rotate_counter_clock('y');
		cubestate.YellowLeft();
    }
}

void Controller::BlueRight(bool rotate)
{
    if (rotate)
    {
        cubeModel[cubestate[4]].rotate(glm::vec3(step, 0, 0));
    }
    else
    {
        Addchilds(&cubeModel[cubestate[4]]);
		solver.rotate_clock('b');
		cubestate.BlueRight();
    }
}

void Controller::BlueLeft(bool rotate)
{
    if (rotate)
    {
        cubeModel[cubestate[4]].rotate(glm::vec3(-step, 0, 0));
    }
    else
    {
        Addchilds(&cubeModel[cubestate[4]]);
		solver.rotate_counter_clock('b');
		cubestate.BlueLeft();
    }
}

void Controller::GreenLeft(bool rotate)
{
    if (rotate)
    {
        cubeModel[cubestate[22]].rotate(glm::vec3(step, 0, 0));
    }
    else
    {
        Addchilds(&cubeModel[cubestate[22]]);
		solver.rotate_counter_clock('g');
		cubestate.GreenLeft();
    }
}

void Controller::GreenRight(bool rotate)
{
    if (rotate)
    {
        cubeModel[cubestate[22]].rotate(glm::vec3(-step, 0, 0));
    }
	else
	{
		Addchilds(&cubeModel[cubestate[22]]);
		solver.rotate_clock('g');
		cubestate.GreenRight();
	}
}