#pragma once
#include "PhysicsModel.h"
class RigidBody : public PhysicsModel
{
public:
	RigidBody(Transform* tf);

	void AddRelativeForce(Vector3 force, Vector3 point, float deltaTime) override;
	void CalculateAngularVelocity(float deltaTime);

	void OnSetCollider() override;

	void Update(float deltaTime);
private:
	float _angularDampening = 0.5f;

	Vector3 _torque;
	Vector3 _angularVelocity;

	XMFLOAT3X3 _InertiaTensor;
};

