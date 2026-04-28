#include "app.h"
#include "Camera.h"


// classic full_HD 16:9 resolution
int windowWidth = 1600;
int windowHeight = 900;

// main program
int main() {
	if (!glfwInit()) {
		std::cout << "Failed to intialize GLFW" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL Render", NULL, NULL);

	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(GLFW_TRUE); // enables v-Sync

	if (!gladLoadGL()) {
		std::cout << "Failed to load GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, windowWidth, windowHeight);

	ShowWindow(GetConsoleWindow(), SW_HIDE); // hides terminal from background

	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (vidMode != nullptr) {
		glfwSetWindowPos(window, (vidMode->width - windowWidth) / 2, (vidMode->height - windowHeight) / 2);
	}

	glfwSetKeyCallback(window, keyCallback);



	Shader shader = Shader("testShader1");

	float squareSize = 1.0f;
	std::vector<GLfloat> vertices = {
		-squareSize, -squareSize, squareSize,
		squareSize, -squareSize, squareSize,
		-squareSize, -squareSize, -squareSize,
		squareSize, -squareSize, -squareSize,
		-squareSize, squareSize, squareSize,
		squareSize, squareSize, squareSize,
		-squareSize, squareSize, -squareSize,
		squareSize, squareSize, -squareSize,
	};

	std::vector<GLuint> indices = {
		// bottom
		0, 1, 2,
		1, 3, 2,

		// top
		4, 6, 5,
		5, 6, 7,

		//front
		0, 1, 4,
		4, 5, 1,

		//back
		2, 3, 6,
		6, 3, 7,

		//left
		0, 2, 4,
		2, 4, 6,

		//right
		1, 5, 3,
		5, 3, 7
	};

	FloatModel model(vertices, indices, shader);
	model.Translate(glm::vec3(0.0f,0.0f,-2.0f));
	model.Scale(glm::vec3(0.5f));

	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f,0.0f,0.0f), shader);

	// main update loop
	while (!glfwWindowShouldClose(window)) {
		update(window);
		shader.Bind();
		camera.HandleInputs(window);
		camera.Update();

		model.Rotate(0.5f, glm::vec3(1.0f, 0.1f, 1.0f));

		model.Render();

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


// this code runs every frame
int framesCount = 0;
void update(GLFWwindow* window) {
	glfwPollEvents();

	framesCount++;
	string title = "OpenGL " + std::to_string(framesCount);
	glfwSetWindowTitle(window, title.c_str());

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//this function checks every pressed key
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}