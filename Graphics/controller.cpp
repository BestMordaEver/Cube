#include "controller.h"
#include "way.h"
#include <time.h>
#include <algorithm>

std::vector<GLfloat> square = {
    // Blue
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

    // Orange
    -0.5f, 0.5f, -0.5f,  0.8f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.5f,  0.8f, 0.5f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.8f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.5f,  0.8f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.5f,  0.8f, 0.5f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.8f, 0.5f, 0.0f,

    // Green
    -0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,

    // Red
    0.5f, 0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
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

std::vector<int> way;

std::vector<std::vector<int>> indices = {
	{8, 7, 6, 5, 4, 3, 2, 1, 0},
	{17, 16, 15, 14, 13, 12, 11, 10, 9},
    {26, 25, 24, 23, 22, 21, 20, 19, 18}
};

static int state = 0, animstate = 0;
static double timer = 0, counter = 0;
double step = glm::pi<double>() / 100;

float getDistance(CModel const* lhs, CModel const* rhs)
{
    return glm::distance(lhs->getPosition(), rhs->getPosition());
}

Controller::Controller()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cubeModel.emplace_back(square);
                cubeModel.back().setPosition(glm::vec3(-1.0f + k, -1.0f + j, -1.0f + i) * 1.05f, cubeModel.back().getEulers());
            }
        }
    }
    std::vector<CModel*> copy;
    std::transform(cubeModel.begin(), cubeModel.end(), std::back_inserter(copy), [](CModel& model) { return &model; });
    std::sort(copy.begin(), copy.end(), [model = &cubeModel[indices[1][4]]](CModel const* lhs, CModel const* rhs) {return getDistance(lhs, model) < getDistance(rhs, model); });
    childs.resize(20);
    std::copy(copy.begin() + 7, copy.end(), childs.begin());

	Way hell = Way(true);

    //Disassemble(20);
};

void Controller::Update(double dt)
{
    timer += dt;
    if (way.size() == 0)
        state = 2; // Assembled
    switch (state)
    {
        case 0:
			Assemble(false);
            state = 1;
            timer -= dt;
			return;
        case 1:
            if (timer > counter)
            {
                Assemble(true);
                counter += step / 2;  // Tweak this to control animation speed. 
                animstate++;
            }
            if (animstate == 50)
            {
                state = 0;
                timer = 0;
                counter = 0;
                animstate = 0;
                for (int i = 0; i < cubeModel.size(); i++)
                    cubeModel[i].clearChilds();

                //way.insert(way.begin(), way.back());       // This line loops course of actions, remove once done debugging
                way.pop_back();
            }
            return;
    }                             // This is only for manual inputs
    //std::string act;            // To activate this mode, comment current Update func and uncomment here
    //std::cin >> act;            // Valid inputs are listed below, MUST BE UPPERCASE, invalid are ignored
    //Action(act, false); Action(act, true);
    //for (int j = 0; j < cubeModel.size(); j++)
    //	cubeModel[j].clearChilds();

}

void Controller::Draw(CViewPoint mainCam)
{
    for (auto i = 0; i < cubeModel.size(); i++)
        mainCam.drawModel(cubeModel[i]);          // Only parts that move
}

void Controller::Action(std::string s, bool rotate)     // Rotate false is for preparation, assigns children to centers
{   
	if (s == "RU") { RU(rotate); return; }              // True makes actual rotation
	if (s == "RD") { RD(rotate); return; }              // rn rotation is fixed in int step, change on your own risk
	if (s == "LU") { LU(rotate); return; }
	if (s == "LD") { LD(rotate); return; }
	if (s == "UR") { UR(rotate); return; }
	if (s == "UL") { UL(rotate); return; }
	if (s == "DR") { DR(rotate); return; }
	if (s == "DL") { DL(rotate); return; }
	if (s == "FR") { FR(rotate); return; }
	if (s == "FL") { FL(rotate); return; }
	if (s == "BR") { BR(rotate); return; }
	if (s == "BL") { BL(rotate); return; }
}

void Controller::Assemble(bool rotate)
{              
	switch (way.back())
	{
	case 1: Action("RD", rotate); return;
	case 0: Action("RU", rotate); return;
	case 3: Action("LU", rotate); return;
	case 2: Action("LD", rotate); return;
	case 5: Action("UR", rotate); return;
	case 4: Action("UL", rotate); return;
	case 7: Action("DR", rotate); return;
	case 6: Action("DL", rotate); return;
	case 9: Action("FR", rotate); return;
	case 8: Action("FL", rotate); return;
	case 11: Action("BR", rotate); return;
	case 10: Action("BL", rotate); return;
	}
}

void Controller::Disassemble(int i)
{
	step = glm::pi<double>() / 2;
	way.clear();
	srand(time(NULL));
	for (; i > 0; i--)
	{
		if (i % 2 == 0)
			way.push_back(rand() % 6);
		else
			way.push_back(rand() % 6 + 6);
		switch (way.back())
		{
		case 0: Action("RD", false); Action("RD", true); break;
		case 1: Action("RU", false); Action("RU", true); break;
		case 2: Action("LU", false); Action("LU", true); break;
		case 3: Action("LD", false); Action("LD", true); break;
		case 4: Action("UR", false); Action("UR", true); break;
		case 5: Action("UL", false); Action("UL", true); break;
		case 6: Action("DR", false); Action("DR", true); break;
		case 7: Action("DL", false); Action("DL", true); break;
		case 8: Action("FR", false); Action("FR", true); break;
		case 9: Action("FL", false); Action("FL", true); break;
		case 10: Action("BR", false); Action("BR", true); break;
		case 11: Action("BL", false); Action("BL", true); break;
		}
		for (int j = 0; j < cubeModel.size(); j++)
			cubeModel[j].clearChilds();
	}
	step = glm::pi<double>() / 100;
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

void Controller::RD(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[1][5]].rotate(glm::vec3(-step, 0, 0));
    }
    else
    {
        Addchilds(&cubeModel[indices[1][5]]);
		int temp = indices[0][2];
		indices[0][2] = indices[2][2]; 
		indices[2][2] = indices[2][8];
		indices[2][8] = indices[0][8];
		indices[0][8] = temp;
		temp = indices[0][5];
		indices[0][5] = indices[1][2];
		indices[1][2] = indices[2][5];
		indices[2][5] = indices[1][8];
		indices[1][8] = temp;
    }
}

void Controller::RU(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[1][5]].rotate(glm::vec3(step, 0, 0));
    }
    else
    {
        Addchilds(&cubeModel[indices[1][5]]);
		int temp = indices[0][2];
		indices[0][2] = indices[0][8];
		indices[0][8] = indices[2][8];
		indices[2][8] = indices[2][2];
		indices[2][2] = temp;
		temp = indices[0][5];
		indices[0][5] = indices[1][8];
		indices[1][8] = indices[2][5];
		indices[2][5] = indices[1][2];
		indices[1][2] = temp;
    }
}

void Controller::LD(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[1][3]].rotate(glm::vec3(-step, 0, 0));
    }
    else
    {
        Addchilds(&cubeModel[indices[1][3]]);
		int temp = indices[0][0];
		indices[0][0] = indices[2][0];
		indices[2][0] = indices[2][6];
		indices[2][6] = indices[0][6];
		indices[0][6] = temp;
		temp = indices[0][3];
		indices[0][3] = indices[1][0];
		indices[1][0] = indices[2][3];
		indices[2][3] = indices[1][6];
		indices[1][6] = temp;
    }
}

void Controller::LU(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[1][3]].rotate(glm::vec3(step, 0, 0));
    }
    else
    {
        Addchilds(&cubeModel[indices[1][3]]);
		int temp = indices[0][2];
		indices[0][0] = indices[0][6];
		indices[0][6] = indices[2][6];
		indices[2][6] = indices[2][0];
		indices[2][0] = temp;
		temp = indices[0][3];
		indices[0][3] = indices[1][6];
		indices[1][6] = indices[2][3];
		indices[2][3] = indices[1][0];
		indices[1][0] = temp;
    }
}

void Controller::UR(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[1][1]].rotate(glm::vec3(0, step, 0));
    }
    else
    {
        Addchilds(&cubeModel[indices[1][1]]);
		int temp = indices[0][0];
		indices[0][0] = indices[2][0];
		indices[2][0] = indices[2][2];
		indices[2][2] = indices[0][2];
		indices[0][2] = temp;
		temp = indices[0][1];
		indices[0][1] = indices[1][0];
		indices[1][0] = indices[2][1];
		indices[2][1] = indices[1][2];
		indices[1][2] = temp;
    }
}

void Controller::UL(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[1][1]].rotate(glm::vec3(0, -step, 0));
    }
    else
    {
        Addchilds(&cubeModel[indices[1][1]]);
		int temp = indices[0][0];
		indices[0][0] = indices[0][2];
		indices[0][2] = indices[2][2];
		indices[2][2] = indices[2][0];
		indices[2][0] = temp;
		temp = indices[0][1];
		indices[0][1] = indices[1][2];
		indices[1][2] = indices[2][1];
		indices[2][1] = indices[1][0];
		indices[1][0] = temp;
    }
}

void Controller::DR(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[1][7]].rotate(glm::vec3(0, step, 0));
    }
    else
    {
        Addchilds(&cubeModel[indices[1][7]]);
		int temp = indices[0][6];
		indices[0][6] = indices[2][6];
		indices[2][6] = indices[2][8];
		indices[2][8] = indices[0][8];
		indices[0][8] = temp;
		temp = indices[0][7];
		indices[0][7] = indices[1][6];
		indices[1][6] = indices[2][7];
		indices[2][7] = indices[1][8];
		indices[1][8] = temp;
    }
}

void Controller::DL(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[1][7]].rotate(glm::vec3(0, -step, 0));
    }
    else
    {
        Addchilds(&cubeModel[indices[1][7]]);
		int temp = indices[0][6];
		indices[0][6] = indices[0][8];
		indices[0][8] = indices[2][8];
		indices[2][8] = indices[2][6];
		indices[2][6] = temp;
		temp = indices[0][7];
		indices[0][7] = indices[1][8];
		indices[1][8] = indices[2][7];
		indices[2][7] = indices[1][6];
		indices[1][6] = temp;
    }
}

void Controller::FR(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[0][4]].rotate(glm::vec3(0, 0, step));
    }
    else
    {
        Addchilds(&cubeModel[indices[0][4]]);
		int temp = indices[0][0];
		indices[0][0] = indices[0][6];
		indices[0][6] = indices[0][8];
		indices[0][8] = indices[0][2];
		indices[0][2] = temp;
		temp = indices[0][1];
		indices[0][1] = indices[0][3];
		indices[0][3] = indices[0][7];
		indices[0][7] = indices[0][5];
		indices[0][5] = temp;
    }
}

void Controller::FL(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[0][4]].rotate(glm::vec3(0, 0, -step));
    }
    else
    {
        Addchilds(&cubeModel[indices[0][4]]);
		int temp = indices[0][0];
		indices[0][0] = indices[0][2];
		indices[0][2] = indices[0][8];
		indices[0][8] = indices[0][6];
		indices[0][6] = temp;
		temp = indices[0][1];
		indices[0][1] = indices[0][5];
		indices[0][5] = indices[0][7];
		indices[0][7] = indices[0][3];
		indices[0][3] = temp;
    }
}

void Controller::BR(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[2][4]].rotate(glm::vec3(0, 0, step));
    }
    else
    {
        Addchilds(&cubeModel[indices[2][4]]);
		int temp = indices[2][0];
		indices[2][0] = indices[2][6];
		indices[2][6] = indices[2][8];
		indices[2][8] = indices[2][2];
		indices[2][2] = temp;
		temp = indices[2][1];
		indices[2][1] = indices[2][3];
		indices[2][3] = indices[2][7];
		indices[2][7] = indices[2][5];
		indices[2][5] = temp;
    }
}

void Controller::BL(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[2][4]].rotate(glm::vec3(0, 0, -step));
    }
	else
	{
		Addchilds(&cubeModel[indices[2][4]]);
		int temp = indices[2][0];
		indices[2][0] = indices[2][2];
		indices[2][2] = indices[2][8];
		indices[2][8] = indices[2][6];
		indices[2][6] = temp;
		temp = indices[2][1];
		indices[2][1] = indices[2][3];
		indices[2][3] = indices[2][7];
		indices[2][7] = indices[2][5];
		indices[2][5] = temp;
	}
}
