#pragma once
#include "PhysicsModel.h"
class RigidBody : public PhysicsModel
{
public:
	RigidBody(Transform* tf) : PhysicsModel(tf) {};

	void Update(float deltaTime);
};

