#define GLFW_INCLUDE_NONE
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using string = std::string;

// classic full_HD 16:9 resolution
int windowWidth = 1920;
int windowHeight = 1080;

// method that checks if window should close
void checkClose(GLFWwindow* window) {
	// if pressed escape key, close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

// function that reads data from files and return it in string
string static readFromFile(const string filepath) {
	std::ifstream file(filepath);

	if (!file.is_open()) {
		std::cout << "Failed to open file: " << filepath << std::endl;
		return "";
	}
	string line, content;
	while (std::getline(file, line)) {
		content += line + "\n";
	}

	return content;
}

const char* readShader(const string filepath) {
	static string source;
	source = readFromFile(filepath);
	if (source.empty()) {
		std::cout << "File is empty: " + filepath << std::endl;
	}
	return source.c_str();
}


// Vertex Shader source code
const char* vertexShaderSource = readShader("Shaders/exampleShader1/vertex_shader.glsl");
//Fragment Shader source code
const char* fragmentShaderSource = readShader("Shaders/exampleShader1/fragment_shader.glsl");


// main program
int main() {
	std::cout << readFromFile("Shaders/exampleShader1/vertex_shader.glsl") << std::endl;

	if (!glfwInit()) {
		std::cout << "Failed to intialize GLFW" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSwapInterval(GLFW_TRUE); // enables v-Sync

	if (!gladLoadGL()) {
		std::cout << "Failed to load GLAD" << std::endl;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	int framesCount = 0;
	//ShowWindow(GetConsoleWindow(), SW_HIDE); // hides terminal from background
	// main update loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		checkClose(window);


		framesCount++;
		string title = "OpenGL " + std::to_string(framesCount);
		glfwSetWindowTitle(window, title.c_str());

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

