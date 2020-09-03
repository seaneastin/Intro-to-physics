#include "physicsSceneApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "PhysicsScene.h"
#include <Gizmos.h>
#include "Sphere.h"
#include "Plane.h"



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

	glm::vec2 gravity = glm::vec2(0, -10);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimeStep(0.01f);

	glm::vec2 initialvelocity = glm::vec2(0.0f, 0.0f);
	glm::vec2 initialposition = glm::vec2(-70.0f, 60.0f);


	Sphere* ball = new Sphere(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), 1.0f, 1.0f, glm::vec4(128, 0, 128, 1));
	Sphere* ball2 = new Sphere(initialposition, initialvelocity, 1.0f, 1.0f, glm::vec4(1, 1, 1, 1));
	
	//setupContinuousDemo(initialposition, initialvelocity, gravity.y);
	m_physicsScene->addActor(ball);
	m_physicsScene->addActor(ball2);

	
	Plane* floor = new Plane(glm::vec2(-1.0f, 2.0f), -6.0f);
	Plane* floor2 = new Plane(glm::vec2(1.0f, 2.0f), -6.0f);
	m_physicsScene->addActor(floor);
	m_physicsScene->addActor(floor2);



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

void physicsSceneApp::setupContinuousDemo(glm::vec2 startPos, glm::vec2 velocity, float gravity)
{
	float time = 0.0f;
	float timeStep = 0.5f;
	float radius = 1.0f;
	int segments = 12;
	glm::vec4 color = glm::vec4(1, 1, 0, 1);
	glm::vec2 endPos;
	while (time <= 5)
	{
		//calculate the x, y position of the projectile at time

		float x = startPos.x + velocity.x * time;
		float y = (startPos.y + velocity.y * time) + (.5f * gravity * (time * time));




		endPos = glm::vec2(x, y);

		aie::Gizmos::add2DCircle(endPos, radius, segments, color);
		time += timeStep;
	}
}
