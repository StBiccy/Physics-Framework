#include "ParticleModel.h"

ParticleModel::ParticleModel(Transform* transform, float resetTime, Vector3 pertubation, bool invertGravity) : PhysicsModel(transform)
{
	_resetTime = resetTime;
	_invertGravity = invertGravity;
}

void ParticleModel::Update(float deltaTime)
{
	_timeAlive += deltaTime;
	if (_timeAlive > _resetTime)
	{
		Reset();
	}
	PhysicsModel::Update(deltaTime);
}

void ParticleModel::Reset()
{
	_timeAlive = 0.0f;
}
