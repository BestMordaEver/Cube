#include "controller.h"
#include <iostream>
#include <time.h>
#include <map>

std::vector<std::vector<GLfloat>> squares = {
	// Corners
	{	// 1
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
	{	// 2
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
	{	// 3
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
	{	// 4
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
	{	// 5
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
	{	// 6
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
	{	// 7
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
	{	// 8
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
	{	// 9
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
	{	// 10
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
	{	// 11
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
	{	// 12
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
	{	// 13
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
	{	// 14
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
	{	// 15
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
	{	// 16
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
	{	// 17
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
	{	// 18
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
	{	// 19
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
	{	// 20
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
	{	// 21
		//blue 5
		1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		2.0f, 2.0f, 0.0f,  0.0f, 0.0f, 1.0f
	},
	{
		// 22
		//orange 5
		0.0f, 1.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 1.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 1.0f, 2.0f,  0.8f, 0.5f, 0.0f,
		0.0f, 2.0f, 2.0f,  0.8f, 0.5f, 0.0f
	},
	{	// 23
		//green 5
		1.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 1.0f, 3.0f,  0.0f, 1.0f, 0.0f,
		2.0f, 2.0f, 3.0f,  0.0f, 1.0f, 0.0f
	},
	{
		// 24
		//red 5
		3.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 1.0f, 2.0f,  1.0f, 0.0f, 0.0f,
		3.0f, 2.0f, 2.0f,  1.0f, 0.0f, 0.0f
	},
	{
		// 25
		//white 5
		1.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 1.0f,  1.0f, 1.0f, 1.0f,
		1.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f,
		2.0f, 3.0f, 2.0f,  1.0f, 1.0f, 1.0f
	},
	{
		// 26
		//yellow 5
		1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.2f,
		1.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f,
		2.0f, 0.0f, 2.0f,  1.0f, 1.0f, 0.2f
	}, 
	{
		// 27
		// middle
		// no need to draw him
	}
};

std::vector<int> way;
std::vector<std::vector<int>> indices = {
	{2, 9, 1, 10, 20, 8, 3, 11, 0},
	{18, 24, 19, 23, 26, 21, 17, 25, 16},
	{6, 13, 5, 14, 22, 12, 7, 15, 4}
};
int state = 0;
double dT = 0, timer = 0;;

Controller::Controller() {
	for (unsigned int i = 0; i < squares.size(); i++)
		cubeModel.emplace_back(squares[i]);
	cubeModel.emplace_back(squares[20]);
	way = { 1};
};

void Controller::Action(std::string s, bool rotate) {
	if (s == "RU") RU(rotate);
	if (s == "RD") RD(rotate);
	if (s == "LU") LU(rotate);
	if (s == "LD") LD(rotate);
	if (s == "UR") UR(rotate);
	if (s == "UL") UL(rotate);
	if (s == "DR") DR(rotate);
	if (s == "DL") DL(rotate);
	if (s == "FR") FR(rotate);
	if (s == "FL") FL(rotate);
	if (s == "BR") BR(rotate);
	if (s == "BL") BL(rotate);
	if (s == "MR") MR(rotate);
	if (s == "ML") ML(rotate);
	if (s == "CU") CU(rotate);
	if (s == "CR") CR(rotate);
	if (s == "CD") CD(rotate);
	if (s == "CL") CL(rotate);
}

void Controller::Update(double dt) {
	timer += dt;
	switch (state)
	{
	case 0:
		Assemble(false);
		state = 1;
		return;
	case 1:
		dT = dt;
		Assemble(true);
		if (timer > glm::pi<double>()/2)
		{
			state = 2;
			for (int i = 0; i < cubeModel.size(); i++)
				cubeModel[i].clearChilds();
			//way.pop_back();
		}
		return;
	case 2:
		if (timer > glm::pi<double>())
		{
			state = 0;
			timer = 0;
		}
		return;
	}
}

void Controller::Draw(CViewPoint mainCam) {
	for (auto i = 0u; i < cubeModel.size(); i++)
		mainCam.drawModel(cubeModel[i]);
}

void Controller::Assemble(bool rotate) {
	switch (way.back())
	{
	case 1: Action("RD", rotate); break;
	case 0: Action("RU", rotate); break;
	case 3: Action("LU", rotate); break;
	case 2: Action("LD", rotate); break;
	case 5: Action("UR", rotate); break;
	case 4: Action("UL", rotate); break;
	case 7: Action("DR", rotate); break;
	case 6: Action("DL", rotate); break;
	case 9: Action("FR", rotate); break;
	case 8: Action("FL", rotate); break;
	case 11: Action("BR", rotate); break;
	case 10: Action("BL", rotate); break;
	case 13: Action("MR", rotate); break;
	case 12: Action("ML", rotate); break;
	case 16: Action("CU", rotate); break;
	case 17: Action("CR", rotate); break;
	case 14: Action("CD", rotate); break;
	case 15: Action("CL", rotate); break;
	}
}

void Controller::Disassemble(int i) {
	way.clear();
	cubeMatrix.cubeReset();
	srand(time(NULL));
	for (; i > 0; i--) {
		way.push_back(rand() % 18);
		//std::cout << way.back() << " ";
		switch (way.back())
		{
		case 0: Action("RD", false); break;
		case 1: Action("RU", false); break;
		case 2: Action("LU", false); break;
		case 3: Action("LD", false); break;
		case 4: Action("UR", false); break;
		case 5: Action("UL", false); break;
		case 6: Action("DR", false); break;
		case 7: Action("DL", false); break;
		case 8: Action("FR", false); break;
		case 9: Action("FL", false); break;
		case 10: Action("BR", false); break;
		case 11: Action("BL", false); break;
		case 12: Action("MR", false); break;
		case 13: Action("ML", false); break;
		case 14: Action("CU", false); break;
		case 15: Action("CR", false); break;
		case 16: Action("CD", false); break;
		case 17: Action("CL", false); break;
		}
	}
	std::cout << std::endl;
}

void Controller::RD(bool rotate) {
	if (rotate) {
		cubeModel[indices[1][5]].rotate(glm::vec3(0, 0, (float)dT));
	}
	else {
		cubeMatrix.RD();
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[0][2]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[0][5]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[0][8]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[1][2]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[1][8]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[2][2]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[2][5]]);
		cubeModel[indices[1][5]].AddChild(&cubeModel[indices[2][8]]);
	}
}

void Controller::RU(bool rotate) {
	cubeMatrix.RU();
}

void Controller::LD(bool rotate) {
	cubeMatrix.LD();
}

void Controller::LU(bool rotate) {
	cubeMatrix.LU();
}

void Controller::UR(bool rotate) {
	cubeMatrix.UR();
}

void Controller::UL(bool rotate) {
	cubeMatrix.UL();
}

void Controller::DR(bool rotate) {
	cubeMatrix.DR();
}

void Controller::DL(bool rotate) {
	cubeMatrix.DL();
}

void Controller::FR(bool rotate) {
	cubeMatrix.FR();
}

void Controller::FL(bool rotate) {
	cubeMatrix.FL();
}

void Controller::BR(bool rotate) {
	cubeMatrix.BR();
}

void Controller::BL(bool rotate) {
	cubeMatrix.BL();
}

void Controller::CR(bool rotate) {
	cubeMatrix.CR();
}

void Controller::CL(bool rotate) {
	cubeMatrix.CL();
}

void Controller::CU(bool rotate) {
	cubeMatrix.CU();
}

void Controller::CD(bool rotate) {
	cubeMatrix.CD();
}

void Controller::ML(bool rotate) {
	cubeMatrix.ML();
}

void Controller::MR(bool rotate) {
	cubeMatrix.MR();
}