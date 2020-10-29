#pragma once
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

struct Shader
{
	GLuint shaderID;
	std::string name;

	void Use()
	{
		glUseProgram(shaderID);
	}

	void SetUniform1i(const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(shaderID, name), value);
	}

	void SetUniform1ui(const char* name, int value)
	{
		glUniform1ui(glGetUniformLocation(shaderID, name), value);
	}

	void SetFloat(const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(shaderID, name), value);
	}

};





static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* message = (char*)malloc(lenght * sizeof(char));
		glGetShaderInfoLog(id, lenght, &lenght, message);
		std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const char* vertexShader, const char* fragShader)
{
	std::string vertexCode;
	std::string fragCode;
	std::ifstream vertexFile;
	std::ifstream fragFile;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//Open Files
		vertexFile.open(vertexShader);
		fragFile.open(fragShader);
		//Read files into buffer
		std::stringstream vertexStream, fragStream;
		vertexStream << vertexFile.rdbuf();
		fragStream << fragFile.rdbuf();
		//Close files
		vertexFile.close();
		fragFile.close();
		//Convert stream into string
		vertexCode = vertexStream.str();
		fragCode = fragStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR: FAILED TO READ SHADER FILES." << std::endl;
	}

	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexCode);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragCode);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}