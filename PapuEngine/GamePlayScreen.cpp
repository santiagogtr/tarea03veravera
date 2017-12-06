#include "GamePlayScreen.h"
#include "Game.h"
#include "ScreenIndices.h"
#include <iostream>
#include "ResourceManager.h"
#include <random>
#include <ctime>


bool GamePlayScreen::onExitClicked()
{
	_currentState = ScreenState::EXIT_APPLICATION;
	return true;
}

GamePlayScreen::GamePlayScreen(Window* window):
	_window(window),_bullet(0),_score(0)
{
	_screenIndex = SCREEN_INDEX_GAMEPLAY;
}

GamePlayScreen::~GamePlayScreen()
{
}

void GamePlayScreen::build() {

}

void GamePlayScreen::destroy() {

}

void GamePlayScreen::onExit() {
}

void GamePlayScreen::onEntry() {
	initWorld();
	initSystem();
	_spriteBatch.init();
	_hudBatch.init();
	initGUI();
	tiempo = 0;
	puntaje = 0;
	puntajeTotal = 0;
	vida = 10;
	_camera2d.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_camera2d.setPosition(
		glm::vec2(_window->getScreenWidth() / 2.0f,
			_window->getScreenHeight() / 2.0f));
	
	_background = new Background("Textures/naves/game.png");
	_ship = new Ship(53, 80
		, glm::vec2(_window->getScreenWidth() / 2.0f, 300), "Textures/naves/X.png",&_game->_inputManager);

	_hudCamera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_hudCamera.setPosition(
		glm::vec2(_window->getScreenWidth() / 2.0f,
				_window->getScreenHeight() / 2.0f));

	_spriteFont = new SpriteFont("Fonts/arial.ttf",64);

	/*_enemies.push_back(new EnemyShip(-120, 120, glm::vec2(
		0, 220),
		"Textures/naves/amarillo.png", 1));
	_enemies.push_back(new EnemyShip(140, 90, glm::vec2(
		600, 400),
		"Textures/naves/rojo.png", 2));*/
}

void GamePlayScreen::initWorld() {
	
}

void GamePlayScreen::initGUI()
{

}

void GamePlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera2d.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_spriteBatch.begin();

	_ship->draw(_spriteBatch);
	_background->draw(_spriteBatch,_ship->getPosition().x/800);

	for (size_t i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->draw(_spriteBatch);
	}

	for (size_t i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->draw(_spriteBatch);
	}
	for (size_t i = 0; i < _enemyBullets.size(); i++)
	{
		_enemyBullets[i]->draw(_spriteBatch);
	}
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	drawHUD();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void GamePlayScreen::update() {
	const float MS_PER_SECOND = 1000;
	const float DESIRED_FRAMETIME = MS_PER_SECOND / _game->getFps();
	float previuosTime = SDL_GetTicks();
	float newTime = SDL_GetTicks();
	float frameTime = newTime - previuosTime;
	previuosTime = newTime;
	float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

	_camera2d.update();
	_hudCamera.update();
	_ship->update(0.01);
	checkInput();
	_elapsed += 0.1f;
	if (_elapsed >= 6.0f) {
		tiempo++;
		_elapsed = 0;
		if (tiempo % 1 == 0) {
			std::mt19937 randomEngine;
			randomEngine.seed(time(nullptr));
			std::uniform_real_distribution<float>
				randX(-50000,50000);
			int randomColor = randX(randomEngine);
			if (randomColor > _ship->getPosition().x - 50 || randomColor <= _ship->getPosition().x)
				randomColor - 50;
			if(randomColor < _ship->getPosition().x + 50 || randomColor > _ship->getPosition().x)
				randomColor + 50;
			_enemies.push_back(new EnemyShip(120, 120, glm::vec2(
				randomColor, 220),
				"Textures/naves/amarillo.png", 1));
			 randomColor = randX(randomEngine);
			if (randomColor > _ship->getPosition().x - 50 || randomColor <= _ship->getPosition().x)
				randomColor - 50;
			if (randomColor < _ship->getPosition().x + 50 || randomColor > _ship->getPosition().x)
				randomColor + 50;
			_enemies.push_back(new EnemyShip(140, 90, glm::vec2(
				randomColor, 450),
				"Textures/naves/rojo.png", 2));
			randomColor = randX(randomEngine);
			if (randomColor > _ship->getPosition().x - 50 || randomColor <= _ship->getPosition().x)
				randomColor - 50;
			if (randomColor < _ship->getPosition().x + 50 || randomColor > _ship->getPosition().x)
				randomColor + 50;
			_enemies.push_back(new EnemyShip(120, 120, glm::vec2(
				randomColor, 220),
				"Textures/naves/amarillo.png", 1));


			/*
			if (randomColor % 3) {
				_enemies.push_back(new EnemyShip(55, 37, glm::vec2(
					randX(randomEngine), 800),
					"Textures/naves/amarillo.png", 1));
			}
			else {
				if (randomColor % 2) {
					_enemies.push_back(new EnemyShip(55, 37, glm::vec2(
						randX(randomEngine), 800),
						"Textures/naves/rojo.png", 2));
				}
				else {
					_enemies.push_back(new EnemyShip(55, 37, glm::vec2(
						randX(randomEngine), 800),
						"Textures/naves/verde.png", 3));
				}
			}*/
		}
	}
	_ship->gravity();
	for (size_t i = 0; i < _enemies.size(); i++)
	{
		/*
		//_enemies[i]->gravity();
		//_enemies[i]->update(0.1f);
		if (_enemies[i]->outside()) {
			_enemies.erase(_enemies.begin() + i);
			break;
			*/

		if (_ship->getPosition().x - _window->getScreenWidth() / 2 < _enemies[i]->getPosition().x && _window->getScreenWidth() / 2 + _ship->getPosition().x >_enemies[i]->getPosition().x) {
			//_enemies[i]->gravity();
			if (_enemies[i]->update(0.1f, _ship)) {
				_enemyBullets.push_back(new Vullet("Textures/naves/spaceMissiles_001.png", _enemies[i]->getPosition(), _enemies[i]->getFacing()));
			}
			/*if (_enemies[i]->outside()) {
				_enemies.erase(_enemies.begin() + i);
				break;
			}*/
			if (_enemies[i]->collideWithAgent(_ship)) {
				_enemies.erase(_enemies.begin() + i);
				vida--;
				break;
			}
		}
	}

	for (size_t i = 0; i < _enemyBullets.size(); i++)
	{

		if (_enemyBullets[i]->update(0.1f, _window->getScreenWidth()/2 + _ship->getPosition().x, _ship->getPosition().x - _window->getScreenWidth() / 2)) {
			_enemyBullets.erase(_enemyBullets.begin() + i);
		}
		else {
			EnemyShip* prov = new EnemyShip(55, 37, glm::vec2(
				_enemyBullets[i]->_position.x, _enemyBullets[i]->_position.y),
				"Textures/naves/amarillo.png", 1);
			if (_ship->collideWithAgent(prov)) {
				vida--;
				_enemyBullets.erase(_enemyBullets.begin() + i);
				break;
			}
		}

	}
	for (size_t i = 0; i < _bullets.size(); i++)
	{

		if (_bullets[i]->update(0.1f, _window->getScreenWidth() / 2 + _ship->getPosition().x,  _ship->getPosition().x - _window->getScreenWidth() / 2 )) {
			_bullets.erase(_bullets.begin() + i);
		}
		else {

			for (int e = 0; e < _enemies.size(); e++) {
				EnemyShip* prov = new EnemyShip(55, 37, glm::vec2(
					_bullets[i]->_position.x, _bullets[i]->_position.y),
					"Textures/naves/amarillo.png", 1);
				if (_enemies[e]->collideWithAgent(prov)) {
					_bullets.erase(_bullets.begin() + i);
					_enemies.erase(_enemies.begin() + e);
					puntaje += 10;
					puntajeTotal += 10;
					break;
				}
			}
		}

	}

	/*for (size_t e = 0; e < _enemies.size(); e++)
	{

		


			if (_enemies[e]->collideWithAgent(_ship)) {
				int color = _enemies[e]->getColor();
				if (_game->_inputManager.isKeyDown(SDLK_q)) {
					if (color == 1) {
						puntaje += 10;
						puntajeTotal += 10;
					}
					if (color == 2)
						puntaje -= 10;
					if (color == 3)
						puntaje -= 20;
				}
				if (_game->_inputManager.isKeyDown(SDLK_w)) {
					if (color == 1)
						puntaje -= 15;
					if (color == 2) {
						puntaje += 20;
						puntajeTotal += 20;
					}
					if (color == 3)
						puntaje -= 15;
				}
				if (_game->_inputManager.isKeyDown(SDLK_e)) {
					if (color == 1)
						puntaje = puntaje/2;
					if (color == 2)
						puntaje -= 5;
					if (color == 3) {
						puntajeTotal += puntaje;
						puntaje = puntaje * 2;
					}
				}
				_enemies.erase(_enemies.begin() + e);
				if (puntaje<0) {
					puntajeSuperTotal = puntajeTotal;
					_currentState = ScreenState::CHANGE_NEXT;

					
				}
			}
		
	}*/

	if (_game->_inputManager.isKeyDown(SDLK_f) && frecuenciaBala <= 0) {
		_bullets.push_back(new Vullet("Textures/naves/bullet.png", _ship->getPosition(),_ship->getFacing()));
		frecuenciaBala = 10;
	}
	else {
		frecuenciaBala--;
	}
	
	if (_game->_inputManager.isKeyDown(SDLK_d)) {
		_camera2d.setPosition(glm::vec2(
			_camera2d.getPosition().x + 5, _camera2d.getPosition().y));
		
	}
	if (_game->_inputManager.isKeyDown(SDLK_a)) {
		_camera2d.setPosition(glm::vec2(
			_camera2d.getPosition().x - 5, _camera2d.getPosition().y));
		
	}
	if (vida == 0) {
		puntajeSuperTotal = puntajeTotal;
		_currentState = ScreenState::CHANGE_NEXT;
	}

}

void  GamePlayScreen::drawHUD() {
	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _hudCamera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];

	_hudBatch.begin();
	sprintf_s(buffer, " VIDA %d", vida);
	_spriteFont->draw(_hudBatch, buffer, glm::vec2(0, 450),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	sprintf_s(buffer, " PUNTAJE %d", puntaje);
	_spriteFont->draw(_hudBatch, buffer, glm::vec2(520, 450),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	_hudBatch.end();
	_hudBatch.renderBatch();

}

void GamePlayScreen::initSystem()
{
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}


void GamePlayScreen::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		_game->onSDLEvent(evnt);
	}
}

int GamePlayScreen::getNextScreen() const {
	return SCREEN_INDEX_GAMEOVER;
};

int GamePlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}
