#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "ViewScreen.h" 
#include "GameShaders.h"
#include "MeshCreator.h"
#include "TextureHolder.h"
#include "transform.h"
#include "Audio.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void playAudio(unsigned int Source, glm::vec3 pos);

	ViewScreen _gameDisplay;
	GameState _gameState;
	MeshCreator mesh1;
	MeshCreator mesh2;
	Camera myCamera;
	Audio audioDevice;

	float counter;
	unsigned int whistle;
	unsigned int backGroundMusic;
};

