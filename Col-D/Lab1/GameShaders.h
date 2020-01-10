#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "Camera.h"

class GameShaders
{
public:
	GameShaders(const std::string& filename);

	void BindShader(); //Set gpu to use our shaders
	void UpdateShader(const Transform& transform, const Camera& camera);//updates the transform and camera

	std::string GameShaders::LoadGameShader(const std::string& fileName);//method for loading the shader 
	void GameShaders::CheckGameShaderError(GLuint gameShader, GLuint flag, bool isProgram, const std::string& errorShader);//checking for errors 
	GLuint GameShaders::CreateGameShader(const std::string& text, unsigned int type);//creating the shader

	~GameShaders();


protected:
private:
	static const unsigned int NUMBER_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_U,

		NUMBER_UNIFORMS
	};

	GLuint shaderProgram; // Track the shader program
	GLuint numShaders[NUMBER_SHADERS]; //array of shaders
	GLuint numUniforms[NUMBER_UNIFORMS]; //no of uniform variables
};
