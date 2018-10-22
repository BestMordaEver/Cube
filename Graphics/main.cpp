#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>


// Other includes
#include "shader.h"
#include "viewpoint.h"
#include "model.h"
#include "interface.h"
#include "cube.h"
#include "controller.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLuint WIDTH = 800, HEIGHT = 600;

GLFWwindow* window;

int main() {
	window = initializeInterface(WIDTH, HEIGHT);
	CShader mainShader("vertex-shader.vs",
		"fragment-shader.frag");
	CViewPoint mainCam(std::move(mainShader), WIDTH, HEIGHT);
	mainCam.SetCamera(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0));
	//CModel testChild;
	
	Controller controller;
	
	//testChild.setPosition (glm::vec3 (2, 0, 0), glm::vec3 (0, 0, 0));
	//CModel& child = cube.getChild(cube.AddChild (std::move (testChild)));
	double dt = 0;
	//main loop
	double prevTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		doMovement(&mainCam);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		double currTime = glfwGetTime();
		//game logic
		controller.Update(-prevTime + currTime); // for now...
		mainCam.UseCamera();
		dt = glfwGetTime();
		//drawing
		controller.Draw(mainCam);
		glfwSwapBuffers(window);
		prevTime = currTime;
	}
	glfwTerminate();
	return 0;
}