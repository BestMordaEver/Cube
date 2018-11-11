<<<<<<< HEAD
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
=======
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

#include "nuklear_glfw_gl3.h"

const GLuint WIDTH = 800, HEIGHT = 600;
#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

GLFWwindow* window;

int main() {
    window = initializeInterface(WIDTH, HEIGHT);

    struct nk_colorf bg;
    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
    nk_context* ctx = initializeUI(window);
	CShader mainShader("vertex-shader.vs",
		"fragment-shader.frag");
	CViewPoint mainCam(std::move(mainShader), WIDTH, HEIGHT);
	mainCam.SetCamera(glm::vec3(5, 5, -5), glm::vec3(0.7, -0.7, 0));
	
	Controller controller;
	
	double dt = 0;
	//main loop
	double prevTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        drawUI(ctx, bg);
		doMovement(&mainCam);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		double currTime = glfwGetTime();
		//game logic
		controller.Update(-prevTime + currTime);
		mainCam.UseCamera();
		dt = glfwGetTime();
		//drawing
        controller.Draw(mainCam);
        nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
        glEnable(GL_DEPTH_TEST);
		glfwSwapBuffers(window);
		prevTime = currTime;
	}
	glfwTerminate();
	return 0;
>>>>>>> ca09a13327253fbb0c834e4b7cd05ded74bc1818
}