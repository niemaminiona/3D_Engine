#include "src/graphics/Model.h"

FloatModel::FloatModel(const std::vector<GLfloat>&vertices, const std::vector<GLuint> indices, Shader& shader) : shader(shader) {
	
	vertexCount = (GLsizei)vertices.size() / 3;
	indicesCount = (GLsizei)indices.size();

	objectMatrix = glm::mat4(1.0f);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	ClearBuffers();
}

FloatModel::~FloatModel() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}

void FloatModel::Render() {
	shader.setUniformMatrix4("model", objectMatrix);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}

void FloatModel::ClearBuffers() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void FloatModel::Translate(glm::vec3 vector) {
	objectMatrix = glm::translate(objectMatrix, vector);
}

void FloatModel::Rotate(float degrees, glm::vec3 vector) {
	objectMatrix = glm::rotate(objectMatrix, degrees * (glm::pi<float>() / 180.0f), vector);
}

void FloatModel::Scale(glm::vec3 vector) {
	objectMatrix = glm::scale(objectMatrix, vector);
}


