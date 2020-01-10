#include "GameShaders.h"
#include <iostream>
#include <fstream>

GameShaders::GameShaders(const std::string& filename)
{
	shaderProgram = glCreateProgram(); // create shader program (openGL saves as ref number)
	numShaders[0] = CreateGameShader(LoadGameShader("..\\res\\shader.vert"), GL_VERTEX_SHADER); // create vertex shader
	numShaders[1] = CreateGameShader(LoadGameShader("..\\res\\shader.frag"), GL_FRAGMENT_SHADER); // create fragment shader

	for (unsigned int i = 0; i < NUMBER_SHADERS; i++)
	{
		glAttachShader(shaderProgram, numShaders[i]); //add all our shaders to the shader program  
	}

	glBindAttribLocation(shaderProgram, 0, "position"); // associate attribute variable with our shader program attribute 
	glBindAttribLocation(shaderProgram, 1, "texCoord");// associate attribute variable with our shader program attribute 
	glBindAttribLocation(shaderProgram, 2, "normals");// associate attribute variable with our shader program attribute 

	glLinkProgram(shaderProgram); //create executables that will run on the GPU shaders
	CheckGameShaderError(shaderProgram, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // cheack for error

	glValidateProgram(shaderProgram); //check the entire program is valid
	CheckGameShaderError(shaderProgram, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	numUniforms[TRANSFORM_U] = glGetUniformLocation(shaderProgram, "transform"); // associate with the location of uniform variable within a program
}


GameShaders::~GameShaders()
{
	for (unsigned int i = 0; i < NUMBER_SHADERS; i++)
	{
		glDetachShader(shaderProgram, numShaders[i]); //detach shader from program
		glDeleteShader(numShaders[i]); //delete the sahders
	}
	glDeleteProgram(shaderProgram); // delete the program
}

void GameShaders::BindShader()
{
	glUseProgram(shaderProgram); //installs the program object specified by program as part of rendering state
}

void GameShaders::UpdateShader(const Transform& transform, const MainCamera& camera)
{
	glm::mat4 mvp = camera.GetCameraViewProjection() * transform.GetModelDimensions(); // updates the transform of models and viewpoint of camera 
	glUniformMatrix4fv(numUniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}


GLuint GameShaders::CreateGameShader(const std::string& text, unsigned int type)
{
	GLuint numShader = glCreateShader(type); //create shader based on specified type

	if (numShader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(numShader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(numShader); //get open gl to compile shader code

	CheckGameShaderError(numShader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return numShader;
}

std::string GameShaders::LoadGameShader(const std::string& fileName)// checks the file, sees if it can open then returns the output 
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void GameShaders::CheckGameShaderError(GLuint gameShader, GLuint flag, bool isProgram, const std::string& errorShader) // checks the shader and shader program for any errors 
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(gameShader, flag, &success);
	else
		glGetShaderiv(gameShader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(gameShader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(gameShader, sizeof(error), NULL, error);

		std::cerr << errorShader << ": '" << error << "'" << std::endl;
	}
}

