#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class FloatModel {
public:
	FloatModel(const std::vector<GLfloat>& vertices, const std::vector<GLuint> indices);
	~FloatModel();
	void Render();

private:
	GLuint VAO, VBO, IBO;
	GLsizei vertexCount, indicesCount;
	void ClearBuffers();
};