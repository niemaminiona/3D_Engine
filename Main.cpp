#define GLFW_INCLUDE_NONE
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "Shader.cpp"
#include "Model.cpp"

using string = std::string;

// classic full_HD 16:9 resolution
int windowWidth = 1600;
int windowHeight = 900;

const float toRadians = glm::pi<float>() / 180.0f;

void checkClose(GLFWwindow* window);
void update(GLFWwindow* window);

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

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL", NULL, NULL);

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

	glViewport(0, 0, windowWidth, windowHeight);

	ShowWindow(GetConsoleWindow(), SW_HIDE); // hides terminal from background

	Shader shader = Shader("shaders/testShader1");

	std::vector<GLfloat> vertices = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 -0.5f, 0.5f, 0.0f
	};

	std::vector<GLuint> indices = {
		0, 1, 2,
		1, 2, 3
	};

	FloatModel model(vertices, indices);

	glm::mat4 objectMatrix(1.0f);
	glm::vec3 moveVec(0.005f, 0.0f, 0.0f);

	// main update loop
	while (!glfwWindowShouldClose(window)) {
		update(window);
		


		objectMatrix = glm::translate(objectMatrix, moveVec);
		objectMatrix = glm::rotate(objectMatrix, 1 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		shader.setUniformMatrix4("model", objectMatrix);


		shader.Bind();
		model.Render();

		glfwSwapBuffers(window);
	}

	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

// method that checks if window should close
void checkClose(GLFWwindow* window) {
	// if pressed escape key, close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

// this code runs every frame
int framesCount = 0;
void update(GLFWwindow* window) {
	glfwPollEvents();

	checkClose(window);

	framesCount++;
	string title = "OpenGL " + std::to_string(framesCount);
	glfwSetWindowTitle(window, title.c_str());

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

