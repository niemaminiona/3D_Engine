#include "app.h"



string windowTitle = "3D_Engine v0.2.1";

// main program
int main() {
	if (!glfwInit()) {
		std::cout << "Failed to intialize GLFW" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	if (vidMode != nullptr)
	{
		float maxW = (float)vidMode->width * 0.8f;
		float maxH = (float)vidMode->height * 0.8f;

		float windowW = maxW;
		float windowH = windowW / targetAspect;

		if (windowH > maxH)
		{
			windowH = maxH;
			windowW = windowH * targetAspect;
		}

		windowWidth = (int)windowW;
		windowHeight = (int)windowH;
	}

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);

	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (vSyncEnabled) {
		glfwSwapInterval(GLFW_TRUE); // enables v-Sync
	}
	else {
		glfwSwapInterval(GLFW_FALSE);
	}


	if (!gladLoadGL()) {
		std::cout << "Failed to load GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, windowWidth, windowHeight);

	ShowWindow(GetConsoleWindow(), SW_HIDE); // hides terminal from background

	
	if (vidMode != nullptr) {
		glfwSetWindowPos(window, (vidMode->width - windowWidth) / 2, (vidMode->height - windowHeight) / 2);
	}

	glfwSetKeyCallback(window, keyCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);


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

	//FloatModel model(vertices, indices, shader);
	//model.Scale(glm::vec3(0.5f));

	std::vector<FloatModel> listOfModels;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			listOfModels.emplace_back(vertices, indices, shader);
			listOfModels.back().Scale(glm::vec3(0.5f));
			listOfModels.back().Translate(glm::vec3(i * 3.0f, -2.0f, j * 3.0f));
		}
	}

	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 3.0f), shader);
	camera.FOV = 60.0f;
	camera.zFar = 250.0f;

	g_camera = &camera;

	// main update loop
	while (!glfwWindowShouldClose(window)) {
		auto start = std::chrono::high_resolution_clock::now();

		update(window);
		shader.Bind();

		camera.HandleAllInputs(window);
		camera.Update();

		//model.Rotate(0.5f, glm::vec3(1.0f, 0.1f, 1.0f));

		//model.Render();

		for (FloatModel& item : listOfModels) {
			item.Render();
		}

		glfwSwapBuffers(window);


		// FPS limiter
		if (!vSyncEnabled) {
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = end - start;// Calculate how much time passed since the frame started

			double sleepTime = frameTime - elapsed.count();// Calculate how much time we still need to wait
			if (sleepTime > 0.0) {
				std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
			}
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


// this code runs every frame
void update(GLFWwindow* window) {
	glfwPollEvents();


	double currentTime = glfwGetTime();
	frameCount++;

	if (currentTime - lastTime >= 0.5) {
		double elapsed = currentTime - lastTime;
		double fps = frameCount / elapsed;

		std::string title = windowTitle + "    (" + std::to_string((int)fps) + " FPS)";
		glfwSetWindowTitle(window, title.c_str());

		frameCount = 0;
		lastTime = currentTime;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//this function checks every pressed key
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	if (g_camera)
	{
		g_camera->width = width;
		g_camera->height = height;
	}
}