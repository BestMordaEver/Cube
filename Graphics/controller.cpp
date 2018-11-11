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

std::vector<spin> way;

//std::vector<int> indices = {
//	8, 7, 6, 5, 4, 3, 2, 1, 0,
//	17, 16, 15, 14, 13, 12, 11, 10, 9,
//    26, 25, 24, 23, 22, 21, 20, 19, 18
//};

std::vector<int> indices = {
	0, 1, 2, 3, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25, 26
};

static int state = 0, animstate = 0;
static double timer = 0, counter = 0;
double step = glm::pi<double>() / 100;

float getDistance(CModel const* lhs, CModel const* rhs)
{
    return glm::distance(lhs->getPosition(), rhs->getPosition());
}

CModel Xaxis, Yaxis, Zaxis;

Controller::Controller()
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
    std::vector<CModel*> copy;
    std::transform(cubeModel.begin(), cubeModel.end(), std::back_inserter(copy), [](CModel& model) { return &model; });
    std::sort(copy.begin(), copy.end(), [model = &cubeModel[indices[13]]](CModel const* lhs, CModel const* rhs) {return getDistance(lhs, model) < getDistance(rhs, model); });
    childs.resize(20);

	Xaxis = CModel(vector<GLfloat>{ 
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f
	});
	Yaxis = CModel(vector<GLfloat>{
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
		0.5f, 1.0f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
	});
	Zaxis = CModel(vector<GLfloat>{
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	});

    std::copy(copy.begin() + 7, copy.end(), childs.begin());

	way = {UR, UL, DR, DL};
	//Way hell = Way(true);

    //Disassemble(5);
};

void Controller::Update(double dt)
{
    timer += dt;
    if (way.size() == 0)
        state = 2; // Assembled
    switch (state)
    {
        case 0:
			Action(way.back(), false);
            state = 1;
            timer -= dt;
			return;
        case 1:
            if (timer > counter)
            {
				Action(way.back(), true);
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
    for (int i = 0; i < cubeModel.size(); i++)
        mainCam.drawModel(cubeModel[i]);
	//mainCam.drawModel(cubeModel[1]);
	//mainCam.drawModel(cubeModel[0]);
	//mainCam.drawModel(cubeModel[4]);
	//mainCam.drawModel(Xaxis);
	//mainCam.drawModel(Yaxis);
	//mainCam.drawModel(Zaxis);
}

void Controller::Action(spin s, bool rotate)     // Rotate false is for preparation, assigns children to centers
{   
	if (s == RU) { RightUp(rotate); return; }              // True makes actual rotation
	if (s == RD) { RightDown(rotate); return; }              // rn rotation is fixed in int step, change on your own risk
	if (s == LU) { LeftUp(rotate); return; }
	if (s == LD) { LeftDown(rotate); return; }
	if (s == UR) { UpRight(rotate); return; }
	if (s == UL) { UpLeft(rotate); return; }
	if (s == DR) { DownRight(rotate); return; }
	if (s == DL) { DownLeft(rotate); return; }
	if (s == FR) { FrontRight(rotate); return; }
	if (s == FL) { FrontLeft(rotate); return; }
	if (s == BR) { BackRight(rotate); return; }
	if (s == BL) { BackLeft(rotate); return; }
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

void Controller::RightDown(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[14]].rotate(glm::vec3(0, 0, step));
    }
    else
    {
        Addchilds(&cubeModel[indices[14]]);
		int temp = indices[2];
		indices[2] = indices[20]; 
		indices[20] = indices[26];
		indices[26] = indices[8];
		indices[8] = temp;
		temp = indices[5];
		indices[5] = indices[11];
		indices[11] = indices[23];
		indices[23] = indices[17];
		indices[17] = temp;
    }
}

void Controller::RightUp(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[14]].rotate(glm::vec3(0, 0, -step));
    }
    else
    {
        Addchilds(&cubeModel[indices[14]]);
		int temp = indices[2];
		indices[2] = indices[8];
		indices[8] = indices[26];
		indices[26] = indices[20];
		indices[20] = temp;
		temp = indices[5];
		indices[5] = indices[17];
		indices[17] = indices[23];
		indices[23] = indices[11];
		indices[11] = temp;
    }
}

void Controller::LeftDown(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[12]].rotate(glm::vec3(0, 0, step));
    }
    else
    {
        Addchilds(&cubeModel[indices[12]]);
		int temp = indices[0];
		indices[0] = indices[18];
		indices[18] = indices[24];
		indices[24] = indices[6];
		indices[6] = temp;
		temp = indices[3];
		indices[3] = indices[9];
		indices[9] = indices[21];
		indices[21] = indices[15];
		indices[15] = temp;
    }
}

void Controller::LeftUp(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[12]].rotate(glm::vec3(0, 0, -step));
    }
    else
    {
        Addchilds(&cubeModel[indices[12]]);
		int temp = indices[2];
		indices[0] = indices[6];
		indices[6] = indices[24];
		indices[24] = indices[18];
		indices[18] = temp;
		temp = indices[3];
		indices[3] = indices[15];
		indices[15] = indices[21];
		indices[21] = indices[9];
		indices[9] = temp;
    }
}

void Controller::UpRight(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[11]].rotate(glm::vec3(0, step, 0));
    }
    else
    {
        Addchilds(&cubeModel[indices[11]]);
		int temp = indices[0];
		indices[0] = indices[18];
		indices[18] = indices[20];
		indices[20] = indices[2];
		indices[2] = temp;
		temp = indices[1];
		indices[1] = indices[9];
		indices[9] = indices[20];
		indices[20] = indices[11];
		indices[11] = temp;
    }
}

void Controller::UpLeft(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[11]].rotate(glm::vec3(0, -step, 0));
    }
    else
    {
        Addchilds(&cubeModel[indices[11]]);
		int temp = indices[0];
		indices[0] = indices[2];
		indices[2] = indices[20];
		indices[20] = indices[18];
		indices[18] = temp;
		temp = indices[1];
		indices[1] = indices[11];
		indices[11] = indices[20];
		indices[20] = indices[9];
		indices[9] = temp;
    }
}

void Controller::DownRight(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[16]].rotate(glm::vec3(0, step, 0));
    }
    else
    {
        Addchilds(&cubeModel[indices[16]]);
		int temp = indices[6];
		indices[6] = indices[24];
		indices[24] = indices[26];
		indices[26] = indices[8];
		indices[8] = temp;
		temp = indices[7];
		indices[7] = indices[15];
		indices[15] = indices[25];
		indices[25] = indices[17];
		indices[17] = temp;
    }
}

void Controller::DownLeft(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[16]].rotate(glm::vec3(0, -step, 0));
    }
    else
    {
        Addchilds(&cubeModel[indices[16]]);
		int temp = indices[6];
		indices[6] = indices[8];
		indices[8] = indices[26];
		indices[26] = indices[24];
		indices[24] = temp;
		temp = indices[7];
		indices[7] = indices[17];
		indices[17] = indices[25];
		indices[25] = indices[15];
		indices[15] = temp;
    }
}

void Controller::FrontRight(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[4]].rotate(glm::vec3(0, 0, step));
    }
    else
    {
        Addchilds(&cubeModel[indices[4]]);
		int temp = indices[0];
		indices[0] = indices[6];
		indices[6] = indices[8];
		indices[8] = indices[2];
		indices[2] = temp;
		temp = indices[1];
		indices[1] = indices[3];
		indices[3] = indices[7];
		indices[7] = indices[5];
		indices[5] = temp;
    }
}

void Controller::FrontLeft(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[4]].rotate(glm::vec3(0, 0, -step));
    }
    else
    {
        Addchilds(&cubeModel[indices[4]]);
		int temp = indices[0];
		indices[0] = indices[2];
		indices[2] = indices[8];
		indices[8] = indices[6];
		indices[6] = temp;
		temp = indices[1];
		indices[1] = indices[5];
		indices[5] = indices[7];
		indices[7] = indices[3];
		indices[3] = temp;
    }
}

void Controller::BackRight(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[22]].rotate(glm::vec3(0, 0, step));
    }
    else
    {
        Addchilds(&cubeModel[indices[22]]);
		int temp = indices[18];
		indices[18] = indices[24];
		indices[24] = indices[26];
		indices[26] = indices[20];
		indices[20] = temp;
		temp = indices[20];
		indices[20] = indices[21];
		indices[21] = indices[25];
		indices[25] = indices[23];
		indices[23] = temp;
    }
}

void Controller::BackLeft(bool rotate)
{
    if (rotate)
    {
        cubeModel[indices[22]].rotate(glm::vec3(0, 0, -step));
    }
	else
	{
		Addchilds(&cubeModel[indices[22]]);
		int temp = indices[18];
		indices[18] = indices[20];
		indices[20] = indices[26];
		indices[26] = indices[24];
		indices[24] = temp;
		temp = indices[20];
		indices[20] = indices[21];
		indices[21] = indices[25];
		indices[25] = indices[23];
		indices[23] = temp;
	}
}
