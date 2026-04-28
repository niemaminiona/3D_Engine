#pragma once

#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



class Camera {
public:

	// projection values
	GLint width;
	GLint height;
	GLfloat FOV = 45.0f;
	GLfloat zNear = 0.1f;
	GLfloat zFar = 100.0f;

	// used matrices
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	Camera(int width, int height, glm::vec3 position, Shader& shader);

	void Update();

	void HandleKeyInputs(GLFWwindow* window);

private:
	Shader& shader;

	glm::vec3 position;
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up;
	glm::vec3 right;
	//glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	GLfloat yaw = -90.0f;
	GLfloat pitch = 0.0f;

	GLfloat moveSpeed = 0.05f;
	GLfloat turnSpeed = 0.75f;
};
