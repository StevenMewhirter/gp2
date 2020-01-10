#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "ViewScreen.h" 
#include "GameShaders.h"
#include "MeshCreator.h"
#include "TextureHolder.h"
#include "transform.h"
#include "GameAudio.h"

enum class CurrentGameState { PLAY, EXIT };

class myGame
{
public:
	myGame();
	~myGame();

	void runSystems();

private:

	void initSystems();
	void processPlayerInput();
	void gamesCurrentLoop();
	void drawTheGame();
	float NetX = 0.0f;
	float NetY = 0.0f;
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m3Pos, float m3Rad);
	void playAudio(unsigned int Source, glm::vec3 pos);

	ViewScreen _currentGameDisplay;
	CurrentGameState _currentGameState;
	MeshCreator mesh1;
	MeshCreator mesh2;
	MeshCreator mesh3;
	MainCamera myCamera;
	GameAudio audioDevice;

	float counter;
	unsigned int Coin;
	unsigned int gameMusic;
};


