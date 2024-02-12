#pragma once
#include "PhysicsModel.h"

class ParticleModel : public PhysicsModel
{
public:
	ParticleModel(Transform* transform) : PhysicsModel(transform) {};

	ParticleModel(Transform* transform, float resetTime, Vector3 pertubation, bool invertGravity);

	void AddRelativeForce(Vector3 force, Vector3 point) override { AddForce(force); }

	void Update(float deltaTime) override;

private:
	float _timeAlive = 0.0f;
	float _resetTime = 1.0f;

	bool _invertGravity;

	Vector3 _pertubation = Vector3::Zero();

	void Reset();
};

