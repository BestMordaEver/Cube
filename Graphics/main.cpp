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

const GLuint WIDTH = 1366, HEIGHT = 768;
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
	mainCam.SetCamera(glm::vec3(-5, 5, -5), glm::vec3(-0.7, -0.7, 0));
	
	bool good = true;
	do {
		try {
			Controller::getInstance().Start();
			good = true;
		}
		catch (const std::exception& e) {
			Controller::getInstance().~Controller();
			good = false;
		}
	} while (!good);
	
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
		Controller::getInstance().Update(-prevTime + currTime);
		mainCam.UseCamera();
		dt = glfwGetTime();

		//drawing
		Controller::getInstance().Draw(mainCam);
        nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
        glEnable(GL_DEPTH_TEST);
		glfwSwapBuffers(window);
		prevTime = currTime;
	}
	glfwTerminate();
	return 0;
}