#include "PhysicsScene.h"
#include <list>
#include "Rigidbody.h"
PhysicsScene::PhysicsScene()
{
	m_timestep = 0.01f;
	m_gravity = { 0,0 };
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
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

	static std::list<PhysicsObject*> dirty;
	//update physics at a fixed time step

	static float accumulatedTime = 0.0f;

	accumulatedTime += dt;

	while (accumulatedTime >= m_timestep) {


		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timestep);
		}
		accumulatedTime -= m_timestep;


		// check for collisions (ideally you'd want to have some sort of
		// scene management in place)

		for (auto pActor : m_actors)
		{
			for (auto p0ther : m_actors) {
				if (pActor == p0ther)
					continue;
				if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), p0ther) != dirty.end())
					continue;


				Rigidbody* pRigid = dynamic_cast<Rigidbody*>(pActor);

				if (pRigid->checkCollision(p0ther) == true) {
					pRigid->applyForceToActor(dynamic_cast<Rigidbody*>(p0ther),
						pRigid->getVelocity() * pRigid->getMass());
					dirty.push_back(pRigid);
					dirty.push_back(p0ther);
				}
			}

			dirty.clear();
		}


	}

}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{

}
