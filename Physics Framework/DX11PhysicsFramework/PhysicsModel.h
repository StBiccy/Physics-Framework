#pragma once
#include "Transform.h"

class PhysicsModel
{
protected:

	Transform* _transfrom;
	Vector3 _velocity = Vector3();
	Vector3 _Acceleration = Vector3();

	Vector3 _netForce;
	float _mass = 1.0f;
public:
	PhysicsModel(Transform* transform);
	virtual void Update(float deltaTime);
	Vector3 GetVelocity() { return _velocity; }
	void SetVelocity(Vector3 velocity) { _velocity = velocity; }

	void SetAcceleration(Vector3 acceleration) { _Acceleration = acceleration; }
	Vector3 GetAcceleration() { return _Acceleration; }

	void addFource(Vector3 force) { _netForce += force; }
};

