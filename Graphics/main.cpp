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
	mainCam.SetCamera(glm::vec3(-5, 5, -5), glm::vec3(-0.7, -0.7, 0));
	
	Controller controller;
	
	double dt = 0;
	//main loop
	double prevTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		doMovement(&mainCam);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		double currTime = glfwGetTime();
		//game logic
		controller.Update(-prevTime + currTime);
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