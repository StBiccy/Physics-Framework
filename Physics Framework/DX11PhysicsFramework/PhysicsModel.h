#pragma once
#include "Transform.h"
#include "SphereCollider.h"

class PhysicsModel
{
protected:

	Transform* _transfrom;

	Collider* _collider = nullptr;

	Vector3 _velocity = Vector3::Zero();
	Vector3 _Acceleration = Vector3::Zero();

	Vector3 _netForce = Vector3::Zero();
	float _mass = 1.0f;
	float _gravity = 9.81f;

	bool _simGravity = false;
	bool _simFriction = true;
	bool _simDrag = true;
	//drag
	float _density = 1.225f;
	float _dragCoefficient = 1.05f;
	float _refrenceArea = 1.0f;
	//friction
	float _staticCoeff = 0.5f;
	float _keneticCoeff = 0.5f;

public:
	PhysicsModel(Transform* transform);
	~PhysicsModel();
	virtual void Update(float deltaTime);

	float GetMass() { return _mass; }
	float GetInverserMass(){ if (_mass == 0) return 0; return 1.0f / _mass; }

	Vector3 GetVelocity() const		{ return _velocity; }
	void SetVelocity(Vector3 velocity) { _velocity = velocity; }

	void SetAcceleration(Vector3 acceleration) { _Acceleration = acceleration; }
	Vector3 GetAcceleration() { return _Acceleration; }

	void AddForce(Vector3 force) { _netForce += force; }
	void ApplyImpulse(Vector3 impulse) { _velocity += impulse; }

	virtual void AddRelativeForce(Vector3 Force, Vector3 point, float deltaTime) = 0;;

	Vector3 GravityForce() { return -Vector3(0, _gravity * _mass, 0); }
	Vector3 FrictionForce();
	Vector3 DragForce();

	bool IsCollidable() const { return _collider != nullptr; }
	Collider* GetCollider() const { return _collider; }
	void SetCollider(Collider* collider) { _collider = collider; OnSetCollider(); }

	virtual void OnSetCollider() = 0;

};

