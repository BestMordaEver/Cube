#include "controller.h"
#include <iostream>
#include <time.h>
#include <map>

std::vector<std::vector<GLfloat>> squares = {
	// Corners
	{	// 0
		//blue 9
		0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,

		//yellow 3
		0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.2f,
		0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,

		//orange 7
		0.0f, 0.0f, 0.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 0.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 0.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 1.0f,  0.8f, 0.5f, 0.0f
	},
	{	// 1
		//blue 3
		0.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 3.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		0.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		0.0f, 3.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 3.0f, 0.0f,  0.0f, 0.0f, 1.0f,

		//white 9
		0.0f, 3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		0.0f, 3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		0.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,

		//orange 1
		0.0f, 2.0f, 0.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 3.0f, 0.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 3.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 0.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 3.0f, 1.0f,  0.8f, 0.5f, 0.0f
	},
	{	// 2
		//blue 1
		2.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 3.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		3.0f, 3.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		3.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		3.0f, 3.0f, 0.0f,  0.0f, 0.0f, 1.0f,

		//white 7
		2.0f, 3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		3.0f, 3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		3.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		3.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,

		//red 3
		3.0f, 2.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 3.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 3.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 3.0f, 1.0f,  1.0f, 0.0f, 0.0f
	},
	{	// 3
		//blue 7
		2.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		3.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		3.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		3.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,

		//yellow 1
		2.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.2f,
		3.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.2f,
		3.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		3.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,

		//red 9
		3.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f
	},
	{	// 4
		//Green 9
		0.0f, 0.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,

		//yellow 9
		0.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 3.0f,  1.0f, 1.0f, 0.2f,
		0.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		0.0f, 0.0f, 3.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 3.0f,  1.0f, 1.0f, 0.2f,

		//orange 9
		0.0f, 0.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 3.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 0.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 0.0f, 3.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 3.0f,  0.8f, 0.5f, 0.0f
	},
	{	// 5
		//green 3
		0.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 3.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		0.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		0.0f, 3.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 3.0f, 3.0f,  0.0f, 1.0f, 0.0f,

		//white 3
		0.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 3.0f,  1.0f, 1.0f, 1.0f,
		0.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		0.0f, 3.0f, 3.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 3.0f,  1.0f, 1.0f, 1.0f,

		//orange 3
		0.0f, 2.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 3.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 3.0f, 3.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 3.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 3.0f, 3.0f,  0.8f, 0.5f, 0.0f
	},
	{	// 6
		//green 1
		2.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 3.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		3.0f, 3.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		3.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		3.0f, 3.0f, 3.0f,  0.0f, 1.0f, 0.0f,

		//white 1
		2.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		3.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		3.0f, 3.0f, 3.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 3.0f,  1.0f, 1.0f, 1.0f,
		3.0f, 3.0f, 3.0f,  1.0f, 1.0f, 1.0f,

		//red 1
		3.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 3.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 3.0f, 3.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 3.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 3.0f, 3.0f,  1.0f, 0.0f, 0.0f
	},
	{	// 7
		//green 7
		2.0f, 0.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		3.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 0.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		3.0f, 0.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		3.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,

		//yellow 7
		2.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		3.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		3.0f, 0.0f, 3.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 3.0f,  1.0f, 1.0f, 0.2f,
		3.0f, 0.0f, 3.0f,  1.0f, 1.0f, 0.2f,

		//red 7
		3.0f, 0.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 3.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 0.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 0.0f, 3.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 3.0f,  1.0f, 0.0f, 0.0f
	},
	// Sides
	{	// 8
		//blue 6
		0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		0.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,

		//orange 4
		0.0f, 1.0f, 0.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 0.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 0.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 1.0f,  0.8f, 0.5f, 0.0f
	},
	{	// 9
		//blue 2
		1.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 3.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 3.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 3.0f, 0.0f,  0.0f, 0.0f, 1.0f,

		//white 8
		1.0f, 3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f
	},
	{	// 10
		//blue 4
		2.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		3.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		3.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		3.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,

		//red 6
		3.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 1.0f,  1.0f, 0.0f, 0.0f
	},
	{	// 11
		//blue 8
		1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,

		//yellow 2
		1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f
	},
	{	// 12
		//green 6
		0.0f, 1.0f, 3.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 3.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 3.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 2.0f, 3.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 0.0f,

		//orange 6
		0.0f, 1.0f, 2.0f, 0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 2.0f, 0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 3.0f, 0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 2.0f, 0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 3.0f, 0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 3.0f, 0.8f, 0.5f, 0.0f
	},
	{	// 13
		//green 2
		1.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 3.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 3.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 3.0f, 3.0f,  0.0f, 1.0f, 0.0f,

		//white 2
		1.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 3.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 3.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 3.0f,  1.0f, 1.0f, 1.0f
	},
	{	// 14
		//green 4
		2.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		3.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		3.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		3.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,

		//red 4
		3.0f, 1.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 3.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 3.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 3.0f,  1.0f, 0.0f, 0.0f
	},
	{	// 15
		//green 8
		1.0f, 0.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 0.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,

		//yellow 8
		1.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 3.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 3.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 3.0f,  1.0f, 1.0f, 0.2f
	},
	{	// 16
		//yellow 6
		0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		0.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,

		//orange 8
		0.0f, 0.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 0.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 0.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 2.0f,  0.8f, 0.5f, 0.0f
	},
	{	// 17
		//yellow 4
		2.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		3.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		3.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		3.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,

		//red 8
		3.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 0.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 2.0f,  1.0f, 0.0f, 0.0f
	},
	{	// 18
		//white 6
		0.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		0.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		0.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,

		//orange 2
		0.0f, 2.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 3.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 3.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 3.0f, 2.0f,  0.8f, 0.5f, 0.0f
	},
	{	// 19
		//white 4
		2.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		3.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		3.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		3.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,

		//red 2
		3.0f, 2.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 3.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 3.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 3.0f, 2.0f,  1.0f, 0.0f, 0.0f
	},
	// Centers
	{	// 20
		//blue 5
		1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f
	},
	{
		// 21
		//orange 5
		0.0f, 1.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 2.0f,  0.8f, 0.5f, 0.0f
	},
	{	// 22
		//green 5
		1.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f
	},
	{
		// 23
		//red 5
		3.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f
	},
	{
		// 24
		//white 5
		1.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f
	},
	{
		// 25
		//yellow 5
		1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f
	}, 
	{
		// 26
		// middle
		// no need to draw him
	}
};

std::vector<int> way;
std::vector<std::vector<int>> indices = {
	{2, 9, 1, 10, 20, 8, 3, 11, 0},
	{19, 24, 18, 23, 26, 21, 17, 25, 16},
	{6, 13, 5, 14, 22, 12, 7, 15, 4}
};
static int state = 0;
static double timer = 0;

Controller::Controller() {
	for (unsigned int i = 0; i < squares.size(); i++)
		cubeModel.emplace_back(squares[i]);
	//way = { 1};
	way = { 1, 5, 1, 5, 1, 5, 1, 0, 0, 0, 0, 0};
	//way = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
};

void Controller::Action(std::string s, bool rotate) {
	if (s == "RU") { RU(rotate); return; }
	if (s == "RD") { RD(rotate); return; }
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
	if (s == "MR") { MR(rotate); return; }
	if (s == "ML") { ML(rotate); return; }
	if (s == "CU") { CU(rotate); return; }
	if (s == "CR") { CR(rotate); return; }
	if (s == "CD") { CD(rotate); return; }
	if (s == "CL") { CL(rotate); return; }
}
static double count = 0;
void Controller::Update(double dt) {
	timer += dt;
	switch (state)
	{
	case 0:
		Assemble(false);
		state = 1;
		timer -= dt;
		return;
	case 1:
		if (timer > count) {
			Assemble(true);
			count += glm::pi<double>() / 20;
		}
		else if (count == glm::pi<double>() / 2)
		{
			//Assemble(true);
			state = 0;
			timer = 0;
			count = 0;
			for (int i = 0; i < cubeModel.size(); i++)
				cubeModel[i].clearChilds();
			way.pop_back();
		}
		return;
	}/*
	std::string act;
	std::cin >> act; std::cout << std::endl;
	Action(act, false); Action(act, true);
	for (int j = 0; j < cubeModel.size(); j++)
		cubeModel[j].clearChilds();*/
}

void Controller::Draw(CViewPoint mainCam) {
	//for (auto i = 0u; i < cubeModel.size(); i++)
		//mainCam.drawModel(cubeModel[i]);
	mainCam.drawModel(cubeModel[indices[1][1]]);
	mainCam.drawModel(cubeModel[indices[1][5]]);
}

void Controller::Assemble(bool rotate) {
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
	case 13: Action("MR", rotate); return;
	case 12: Action("ML", rotate); return;
	case 16: Action("CU", rotate); return;
	case 17: Action("CR", rotate); return;
	case 14: Action("CD", rotate); return;
	case 15: Action("CL", rotate); return;
	}
}

void Controller::Disassemble(int i) {
	way.clear();
	srand(time(NULL));
	for (; i > 0; i--) {
		way.push_back(rand() % 18);
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
		case 12: Action("MR", false); Action("MR", true); break;
		case 13: Action("ML", false); Action("ML", true); break;
		case 14: Action("CU", false); Action("CU", true); break;
		case 15: Action("CR", false); Action("CR", true); break;
		case 16: Action("CD", false); Action("CD", true); break;
		case 17: Action("CL", false); Action("CL", true); break;
		}
		for (int j = 0; j < cubeModel.size(); j++)
			cubeModel[j].clearChilds();
	}
}

void Controller::RD(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][5]].rotate(glm::vec3(-glm::pi<double>() / 20, 0, 0));
	}
	else {
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[0][2]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[0][5]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[0][8]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[1][2]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[1][8]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[2][2]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[2][5]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[2][8]]);
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

void Controller::RU(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][5]].rotate(glm::vec3(glm::pi<double>() / 20, 0, 0));
	}
	else {
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[0][2]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[0][5]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[0][8]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[1][2]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[1][8]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[2][2]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[2][5]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[2][8]]);
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

void Controller::LD(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][3]].rotate(glm::vec3(-glm::pi<double>() / 20, 0, 0));
	}
	else {
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[0][0]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[0][3]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[0][6]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[1][0]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[1][6]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[2][0]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[2][3]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[2][6]]);
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

void Controller::LU(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][3]].rotate(glm::vec3(glm::pi<double>() / 20, 0, 0));
	}
	else {
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[0][0]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[0][3]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[0][6]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[1][0]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[1][6]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[2][0]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[2][3]]);
		cubeModel[indices[1][3]].AddChild(&cubeModel[indices[2][6]]);
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

void Controller::UR(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][1]].rotate(glm::vec3(0, glm::pi<double>() / 20, 0));
	}
	else {
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[0][0]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[0][1]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[0][2]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[1][2]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[2][2]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[2][1]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[2][0]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[1][0]]);
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

void Controller::UL(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][1]].rotate(glm::vec3(0, -glm::pi<double>() / 20, 0));
	}
	else {
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[0][0]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[0][1]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[0][2]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[1][2]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[2][2]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[2][1]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[2][0]]);
		cubeModel[indices[1][1]].AddChild(&cubeModel[indices[1][0]]);
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

void Controller::DR(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][7]].rotate(glm::vec3(0, glm::pi<double>() / 20, 0));
	}
	else {
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[0][6]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[0][7]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[0][8]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[1][8]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[2][8]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[2][7]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[2][6]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[1][6]]);
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

void Controller::DL(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][7]].rotate(glm::vec3(0, -glm::pi<double>() / 20, 0));
	}
	else {
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[0][6]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[0][7]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[0][8]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[1][8]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[2][8]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[2][7]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[2][6]]);
		cubeModel[indices[1][7]].AddChild(&cubeModel[indices[1][6]]);
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

void Controller::FR(bool rotate) {
	if (rotate) {
		cubeModel[indices[0][4]].rotate(glm::vec3(0, 0, glm::pi<double>() / 20));
	}
	else {
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][1]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][2]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][3]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][5]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][6]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][7]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][8]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][0]]);
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

void Controller::FL(bool rotate) {
	if (rotate) {
		cubeModel[indices[0][4]].rotate(glm::vec3(0, 0, -glm::pi<double>() / 20));
	}
	else {
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][1]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][2]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][3]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][5]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][6]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][7]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][8]]);
		cubeModel[indices[0][4]].AddChild(&cubeModel[indices[0][0]]);
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

void Controller::BR(bool rotate) {
	if (rotate) {
		cubeModel[indices[2][4]].rotate(glm::vec3(0, 0, glm::pi<double>() / 20));
	}
	else {
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][1]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][2]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][3]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][5]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][6]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][7]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][8]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][0]]);
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

void Controller::BL(bool rotate) {
	if (rotate) {
		cubeModel[indices[2][4]].rotate(glm::vec3(0, 0, -glm::pi<double>() / 20));
	}
	else {
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][1]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][2]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][3]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][5]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][6]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][7]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][8]]);
		cubeModel[indices[2][4]].AddChild(&cubeModel[indices[2][0]]);
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

void Controller::CR(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][4]].rotate(glm::vec3(0, glm::pi<double>() / 20, 0));
	}
	else {
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[0][3]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[0][4]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[0][5]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][3]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][5]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[2][3]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[2][4]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[2][5]]);
		int temp = indices[0][3];
		indices[0][3] = indices[2][3];
		indices[2][3] = indices[2][5];
		indices[2][5] = indices[0][5];
		indices[0][5] = temp;
		temp = indices[0][4];
		indices[0][4] = indices[1][3];
		indices[1][3] = indices[2][4];
		indices[2][4] = indices[1][5];
		indices[1][5] = temp;
	}
}

void Controller::CL(bool rotate) {
		if (rotate) {
		cubeModel[indices[1][4]].rotate(glm::vec3(0, -glm::pi<double>() / 20, 0));
	}
	else {
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[0][3]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[0][4]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[0][5]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][3]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][5]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[2][3]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[2][4]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[2][5]]);
		int temp = indices[0][3];
		indices[0][3] = indices[0][5];
		indices[0][5] = indices[2][5];
		indices[2][5] = indices[2][3];
		indices[2][3] = temp;
		temp = indices[0][4];
		indices[0][4] = indices[1][5];
		indices[1][5] = indices[2][4];
		indices[2][4] = indices[1][3];
		indices[1][3] = temp;
	}
}

void Controller::CU(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][4]].rotate(glm::vec3(glm::pi<double>() / 20, 0, 0));
	}
	else {
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[0][1]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[0][4]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[0][7]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][1]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][7]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[2][1]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[2][4]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[2][7]]);
		int temp = indices[0][1];
		indices[0][1] = indices[0][7];
		indices[0][7] = indices[2][7];
		indices[2][7] = indices[2][1];
		indices[2][1] = temp;
		temp = indices[0][4];
		indices[0][4] = indices[1][7];
		indices[1][7] = indices[2][4];
		indices[2][4] = indices[1][1];
		indices[1][1] = temp;
	}
}

void Controller::CD(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][4]].rotate(glm::vec3(-glm::pi<double>() / 20, 0, 0));
	}
	else {
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[0][1]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[0][4]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[0][7]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][1]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][7]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[2][1]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[2][4]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[2][7]]);
		int temp = indices[0][1];
		indices[0][1] = indices[2][1];
		indices[2][1] = indices[2][7];
		indices[2][7] = indices[0][7];
		indices[0][7] = temp;
		temp = indices[0][4];
		indices[0][4] = indices[1][1];
		indices[1][1] = indices[2][4];
		indices[2][4] = indices[1][7];
		indices[1][7] = temp;
	}
}

void Controller::ML(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][4]].rotate(glm::vec3(0, 0, -glm::pi<double>() / 20));
	}
	else {
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][1]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][2]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][3]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][5]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][6]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][7]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][8]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][0]]);
		int temp = indices[1][0];
		indices[1][0] = indices[1][2];
		indices[1][2] = indices[1][8];
		indices[1][8] = indices[1][6];
		indices[1][6] = temp;
		temp = indices[1][1];
		indices[1][1] = indices[1][5];
		indices[1][5] = indices[1][7];
		indices[1][7] = indices[1][3];
		indices[1][3] = temp;
	}
}

void Controller::MR(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][4]].rotate(glm::vec3(0, 0, glm::pi<double>() / 20));
	}
	else {
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][1]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][2]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][3]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][5]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][6]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][7]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][8]]);
		cubeModel[indices[1][4]].AddChild(&cubeModel[indices[1][0]]);
		int temp = indices[1][0];
		indices[1][0] = indices[1][6];
		indices[1][6] = indices[1][8];
		indices[1][8] = indices[1][2];
		indices[1][2] = temp;
		temp = indices[1][1];
		indices[1][1] = indices[1][3];
		indices[1][3] = indices[1][7];
		indices[1][7] = indices[1][5];
		indices[1][5] = temp;
	}
}