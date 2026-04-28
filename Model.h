#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

class FloatModel {
public:
	glm::mat4 objectMatrix;

	FloatModel(const std::vector<GLfloat>& vertices, 
		const std::vector<GLuint> indices, 
		Shader& passedShader);
	~FloatModel();
	void Render();
	void Translate(glm::vec3 vector);
	void Rotate(float degrees, glm::vec3 vector);
	void Scale(glm::vec3 vector);

private:
	Shader& shader;
	GLuint VAO, VBO, IBO;
	GLsizei vertexCount, indicesCount;
	void ClearBuffers();
};