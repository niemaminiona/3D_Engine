#pragma once

#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



class Camera {
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	int width;
	int height;

	GLfloat FOV = 45.0f;
	float speed = 0.1f;
	float sensitivity = 100.0f;

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	Camera(int width, int height, glm::vec3 position, Shader& shader);

	void Update();

	void HandleInputs(GLFWwindow* window);

private:
	Shader& shader;
};
