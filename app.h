#pragma once

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

#include "Shader.h"
#include "Model.h"
#include "Camera.h"

using string = std::string;

// global
Camera* g_camera;

// const variables
const float toRadians = glm::pi<float>() / 180.0f;

// methods
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void update(GLFWwindow* window);