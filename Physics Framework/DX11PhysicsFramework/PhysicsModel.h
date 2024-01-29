#pragma once
#include "Transform.h"

class PhysicsModel
{
protected:

	Transform* _transfrom;
	Vector3 _velocity = Vector3::Zero();
	Vector3 _Acceleration = Vector3::Zero();

	Vector3 _netForce = Vector3::Zero();
	float _mass = 1.0f;
	float _gravity = 9.81f;

	bool _simGravity = false;
	bool _simFriction = false;
	bool _simDrag = false;
	//drag
	float _density = 1.225f;
	float _dragCoefficient = 0.5f;
	float _refrenceArea = 1.0f;

public:
	PhysicsModel(Transform* transform);
	virtual void Update(float deltaTime);
	Vector3 GetVelocity() { return _velocity; }
	void SetVelocity(Vector3 velocity) { _velocity = velocity; }

	void SetAcceleration(Vector3 acceleration) { _Acceleration = acceleration; }
	Vector3 GetAcceleration() { return _Acceleration; }

	void addForce(Vector3 force) { _netForce += force; }
	Vector3 GravityForce() { return -Vector3(0, _gravity * _mass, 0); }

	Vector3 DragForce() { 
		float scalerDrag = 0.5 * _density * _dragCoefficient * _refrenceArea;
		return Vmath::pow3(_velocity,2) * -scalerDrag;
	}
};

