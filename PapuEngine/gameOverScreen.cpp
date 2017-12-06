#include "gameOverScreen.h"
#include "ScreenIndices.h"
#include "Game.h"
#include <iostream>



gameOverScreen::gameOverScreen(Window* window) :
	_window(window), btnGameClicked(false)
{
	_screenIndex = SCREEN_INDEX_MENU;
}

void gameOverScreen::initGUI() {

}

void gameOverScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}


gameOverScreen::~gameOverScreen()
{
}


void gameOverScreen::build()
{
}

void gameOverScreen::destroy() {
	delete _background;
	delete _button;
}

void gameOverScreen::onExit() {

}

void gameOverScreen::onEntry() {
	initSystem();
	_camera2D.init(_window->getScreenWidth(), _window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(_window->getScreenWidth() / 2.0f, _window->getScreenHeight() / 2.0f));
	_spriteBacth.init();
	_background = new Background("Textures/naves/gam-over.png");
	_button = new Button("Textures/naves/menu_button.png");
	_spriteFont = new SpriteFont("Fonts/arial.ttf", 64);
}

void gameOverScreen::update() {
	_camera2D.update();
	if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		if (_button->clicked(_game->_inputManager.getMouseCoords()) && !btnGameClicked) {
			btnGameClicked = true;
			std::cout << "Button clicked" << std::endl;
			_currentState = ScreenState::CHANGE_NEXT;

		}
	}
	checkInput();
}

void gameOverScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	char buffer[256];
	_spriteBacth.begin();
	_background->draw(_spriteBacth,0);
	_button->draw(_spriteBacth);
	sprintf_s(buffer, " Puntaje Total : %d ",puntajeSuperTotal);
	_spriteFont->draw(_spriteBacth, buffer, glm::vec2(0, 0),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	sprintf_s(buffer, " ");
	_spriteFont->draw(_spriteBacth, buffer, glm::vec2(0, 36),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	_spriteBacth.renderBatch();
	_spriteBacth.end();
	_spriteBacth.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

int gameOverScreen::getNextScreen()const {
	return SCREEN_INDEX_MENU;
}

int gameOverScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

void gameOverScreen::setPuntaje(int puntaje) {
	puntajeTotal = puntaje;
}

void gameOverScreen::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		_game->onSDLEvent(evnt);
	}
}






