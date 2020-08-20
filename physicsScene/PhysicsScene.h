#pragma once
#include "glm\ext.hpp"
#include "physicsObject.h"
#include <vector>
class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float dt);
	void updateGizmos();

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; };
	glm::vec2 getGr4avity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timestep = timeStep; }
	float getTimeStep() const { return m_timestep; }
protected:
	glm::vec2 m_gravity;
	float m_timestep;
	std::vector<PhysicsObject*> m_actors;
};

