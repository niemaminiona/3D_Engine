#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using string = std::string;

class Shader {
public:
	GLuint program;

	Shader(const string shaderName) {
		string vertexShaderCode = readFromFile("shaders/" + shaderName + "/vertex_shader.glsl");
		string fragmentShaderCode = readFromFile("shaders/" + shaderName + "/fragment_shader.glsl");

		const char* vertexShaderSource = vertexShaderCode.c_str();
		const char* fragmentShaderSource = fragmentShaderCode.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Bind() {
		glUseProgram(program);
	}

	void setUniformMatrix4(string name, glm::mat4 value) {
		const char* parsedName = name.c_str();
		GLint location = glGetUniformLocation(program, parsedName);
		if (location != -1) {
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		}
	}

	~Shader() {
		glDeleteProgram(program);
	}

	void Delete() {
		glDeleteProgram(program);
	}

private:
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

		file.close();
		return content;
	}
};