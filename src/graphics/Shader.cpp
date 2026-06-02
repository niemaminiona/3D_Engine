#include "src/graphics/Shader.h"

Shader::Shader(const std::string& shaderName) {
	std::string vertexShaderCode = readFromFile("shaders/" + shaderName + "/vertex_shader.glsl");
	std::string fragmentShaderCode = readFromFile("shaders/" + shaderName + "/fragment_shader.glsl");

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

Shader::~Shader() {
	glDeleteProgram(program);
}

void Shader::Bind() {
	glUseProgram(program);
}

void Shader::setUniformMatrix4(std::string name, const glm::mat4& value) {
	const char* parsedName = name.c_str();
	GLint location = glGetUniformLocation(program, parsedName);
	if (location != -1) {
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}


std::string Shader::readFromFile(const std::string filepath){
	std::ifstream file(filepath);

	if (!file.is_open()) {
		std::cout << "Failed to open file: " << filepath << std::endl;
		return "";
	}

	std::string line, content;
	while (std::getline(file, line)) {
		content += line + "\n";
	}

	file.close();
	return content;
}
