#include "interface.h"
#include "controller.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT

#include "nuklear_glfw_gl3.h"
#include <string>
#include "logger.h"


bool keys[1024];

GLfloat deltaTime = 0;
GLfloat lastFrame = 0;
const GLfloat defaultCameraSpeed = 5;

GLfloat lastX, lastY;
GLfloat xoffset, yoffset;
const GLfloat sensitivity = 0.01f;
bool moved = false;
bool firstMouse = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose (window, GL_TRUE);
	}
	if (action == GLFW_PRESS)
	{
		keys[key] = 1;
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = 0;
	}
}


void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	GLfloat xpos = (GLfloat)xPos;
	GLfloat ypos = (GLfloat)yPos;
    if(firstMouse)
	{
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    xoffset = (xpos - lastX) * sensitivity;
    yoffset = (lastY - ypos) * sensitivity; // Reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;
    moved = false;
}

void doMovement(CViewPoint* camera){
    GLfloat currentFrame = (GLfloat)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    GLfloat cameraSpeed = defaultCameraSpeed*deltaTime;
    if(!moved)
    {
		camera->rotate(glm::vec3(xoffset,yoffset,0));
		moved = true;
	}

    glm::vec3 eulers = camera->getEulers();

    glm::vec3 cameraTarget(-glm::sin(eulers.x)*glm::cos(eulers.y),
                           0,
                           glm::cos(eulers.x)*glm::cos(eulers.y));
    glm::vec3 cameraUp(0,1,0);

	if (keys[GLFW_KEY_W])
	{
		camera->move (cameraTarget*cameraSpeed);
	}
	if (keys[GLFW_KEY_S])
	{
		camera->move (cameraTarget*(-cameraSpeed));
	}
	if (keys[GLFW_KEY_A])
	{
		camera->move (-glm::normalize (glm::cross (cameraTarget, cameraUp))*cameraSpeed);
	}
	if (keys[GLFW_KEY_D])
	{
		camera->move (glm::normalize (glm::cross (cameraTarget, cameraUp))*cameraSpeed);
	}
	if (keys[GLFW_KEY_SPACE])
	{
		camera->move (cameraUp*cameraSpeed);
	}
	if (keys[GLFW_KEY_LEFT_CONTROL])
	{
		camera->move (cameraUp*(-cameraSpeed));
	}
}



GLFWwindow* initializeInterface(GLuint width, GLuint height){
    GLFWwindow* wind;
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    wind = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(wind);

    //glfwSetInputMode(wind, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSetCursorPosCallback(wind, mouse_callback);

    // Set the required callback functions
    glfwSetKeyCallback(wind, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, width, height);

    //models[0]=model("path/to/model","");
    //mainCam = &viewPoint(&Shader("",""),WIDTH,HEIGHT);
    glEnable(GL_DEPTH_TEST);

    return wind;
}

struct nk_context* initializeUI(GLFWwindow* window)
{
    struct nk_context *ctx;
    ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&atlas);
    struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "DroidSans.ttf", 14, 0);
    nk_glfw3_font_stash_end();
    nk_style_set_font(ctx, &droid->handle);
    return ctx;
}

int prevstate = 0;

void wayoverride(spin s) {
	if (Controller::getInstance().way.size())
		Controller::getInstance().way = std::vector<spin>(1, Controller::getInstance().way[0]);
	Controller::getInstance().way.push_back(s);
	logger::ButtonPress(4);
	if (Controller::getInstance().state == idle)
		Controller::getInstance().state = contactive;
}

void drawUI(nk_context* ctx, nk_colorf& bg)
{
    nk_glfw3_new_frame();

    /* GUI */
	if (nk_begin(ctx, "Show", nk_rect(1093, 0, 273, 600),
		NK_WINDOW_BORDER)) {

		nk_layout_row_static(ctx, 30, 80, 1);
		nk_label(ctx, "Actions", NK_TEXT_LEFT);

		nk_layout_row_static(ctx, 30, 100, 2);
		if (nk_button_label(ctx, "Pause")) {
			logger::ButtonPress(3);
			if (Controller::getInstance().state != paused) {
				prevstate = Controller::getInstance().state;
				Controller::getInstance().state = paused;
			}
		}
		if (nk_button_label(ctx, "Continue")) {
			logger::ButtonPress(1);
			if (Controller::getInstance().state > 1)
				Controller::getInstance().state = prevstate;
		}
		if (nk_button_label(ctx, "Generate")) {
			logger::ButtonPress(2);
			Controller::getInstance().way = Controller::getInstance().solver.Solve();

			if (Controller::getInstance().state == idle)
				Controller::getInstance().state = contactive;
		}
		if (nk_button_label(ctx, "Stop")) {
			logger::ButtonPress(0);
			if (Controller::getInstance().way[0])
				Controller::getInstance().way = std::vector<spin>(1, Controller::getInstance().way[0]);
		}

		nk_layout_row_static(ctx, 30, 80, 1);
		nk_label(ctx, "Manual inputs", NK_TEXT_LEFT);

		nk_layout_row_begin(ctx, NK_STATIC, 30, 3); {

			nk_layout_row_push(ctx, 60);
			if (nk_button_label(ctx, "Left")) {
				wayoverride(WL);
			}
			nk_label(ctx, "White", NK_TEXT_CENTERED);
			if (nk_button_label(ctx, "Right")) {
				wayoverride(WR);
			}

			nk_layout_row_push(ctx, 60);
			if (nk_button_label(ctx, "Left")) {
				wayoverride(YL);
			}
			nk_label(ctx, "Yellow", NK_TEXT_CENTERED);
			if (nk_button_label(ctx, "Right")) {
				wayoverride(YR);
			}

			nk_layout_row_push(ctx, 60);
			if (nk_button_label(ctx, "Left")) {
				wayoverride(RL);
			}
			nk_label(ctx, "Red", NK_TEXT_CENTERED);
			if (nk_button_label(ctx, "Right")) {
				wayoverride(RR);
			}

			nk_layout_row_push(ctx, 60);
			if (nk_button_label(ctx, "Left")) {
				wayoverride(BL);
			}
			nk_label(ctx, "Blue", NK_TEXT_CENTERED);
			if (nk_button_label(ctx, "Right")) {
				wayoverride(BR);
			}

			nk_layout_row_push(ctx, 60);
			if (nk_button_label(ctx, "Left")) {
				wayoverride(OL);
			}
			nk_label(ctx, "Orange", NK_TEXT_CENTERED);
			if (nk_button_label(ctx, "Right")) {
				wayoverride(OR);
			}

			nk_layout_row_push(ctx, 60);
			if (nk_button_label(ctx, "Left")) {
				wayoverride(GL);
			}
			nk_label(ctx, "Green", NK_TEXT_CENTERED);
			if (nk_button_label(ctx, "Right")) {
				wayoverride(GR);
			}
		}
		nk_layout_row_end(ctx);
		nk_layout_row_static(ctx, 30, 100, 1);
		nk_label(ctx, std::to_string(Controller::getInstance().way.size()).c_str(), NK_TEXT_LEFT);
	}

    nk_end(ctx);
}
