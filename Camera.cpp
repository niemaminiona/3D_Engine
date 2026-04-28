#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, Shader& shader)
    : width(width), height(height), Position(position), shader(shader) { }

void Camera::Update() {
    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOV), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

    shader.setUniformMatrix4("view", view);
    shader.setUniformMatrix4("projection", projection);
}

void Camera::HandleInputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
}