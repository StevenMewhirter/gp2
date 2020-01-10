#include "TextureHolder.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

TextureHolder::TextureHolder(const std::string& fileName)
{
	int widthOfTexture, heightOfTexture, numberOfComponents; //width, height, and number of components for the image
	unsigned char* imageData = stbi_load((fileName).c_str(), &widthOfTexture, &heightOfTexture, &numberOfComponents, 4); //load the image and store the data

	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << fileName << std::endl; //prompt an error if the texture does not load
	}

	glGenTextures(1, &textureManagement); // number of and address of textures
	glBindTexture(GL_TEXTURE_2D, textureManagement); //bind texture - define type 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap texture outside height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // linear filtering for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear filtering for magnifcation (texture is larger)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthOfTexture, heightOfTexture, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Image Data

	stbi_image_free(imageData);
}

TextureHolder::~TextureHolder()
{
	glDeleteTextures(1, &textureManagement); // number of and address of textures
}

void TextureHolder::BindTextures(unsigned int unitBind)
{
	assert(unitBind >= 0 && unitBind <= 31); /// check we are working with one of the 32 textures

	glActiveTexture(GL_TEXTURE0 + unitBind); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, textureManagement); //type of and texture to bind to unit
}
