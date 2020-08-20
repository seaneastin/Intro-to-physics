#include "PhysicsScene.h"

PhysicsScene::PhysicsScene()
{
	m_timestep = 0.01f;
	m_gravity = { 0,0 };
}

PhysicsScene::~PhysicsScene()
{

}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	for (auto i = m_actors.begin(); i != m_actors.end(); i++)
	{
		if (*i == actor)
		{
			m_actors.erase(i);
		}
	}
}

void PhysicsScene::update(float dt)
{
	//update physics at a fixed time step

	static float accumulatedTime = 0.0f;

	while (accumulatedTime >= m_timestep)
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timestep);
		}
	accumulatedTime -= m_timestep;

}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}
