#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	GLuint program;

	Shader(const std::string& shaderName);
	~Shader();

	void Bind();
	void setUniformMatrix4(std::string name, const glm::mat4& value);

private:
	static std::string readFromFile(const std::string filepath);
};