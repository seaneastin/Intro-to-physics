#include "physicsSceneApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "PhysicsScene.h"
#include <Gizmos.h>
#include "Sphere.h"



physicsSceneApp::physicsSceneApp() {

}

physicsSceneApp::~physicsSceneApp() {

}

bool physicsSceneApp::startup() {
	
	// increase the 2D line countr to mazimize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);



	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimeStep(0.01f);

	
	Sphere* ball = new Sphere(glm::vec2(-40, 0), glm::vec2(0, 40), 3.0f, 5, glm::vec4(1, 0, 0, 1));
	m_physicsScene->addActor(ball);
	return true;
}

void physicsSceneApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void physicsSceneApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void physicsSceneApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));


	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}