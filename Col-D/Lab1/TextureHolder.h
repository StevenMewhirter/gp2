#pragma once
#include <string>
#include <GL\glew.h>

class TextureHolder
{
public:
	TextureHolder(const std::string& fileName);//holds the information about the texture

	void BindTextures(unsigned int unitBind); // bind upto 32 textures

	~TextureHolder();

protected:
private:

	GLuint textureManagement; // manages the texture ensuring correct one is chosen
};