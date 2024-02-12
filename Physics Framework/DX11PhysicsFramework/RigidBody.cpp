#include "RigidBody.h"

RigidBody::RigidBody(Transform* tf) : PhysicsModel(tf)
{
	XMStoreFloat3x3(&_InertiaTensor, XMMatrixIdentity());
}

void RigidBody::AddRelativeForce(Vector3 force, Vector3 point, float deltaTime)
{
	AddForce(force);
	_torque = Vmath::Cross(point, force);
	CalculateAngularVelocity(deltaTime);
}

void RigidBody::CalculateAngularVelocity(float deltaTime)
{
	Vector3 AngularAcceleration = _torque;
	XMVector3Transform(AngularAcceleration, XMMatrixInverse(nullptr, XMLoadFloat3x3(&_InertiaTensor)));
	_angularVelocity += AngularAcceleration * deltaTime;
	
}

void RigidBody::Update(float deltaTime)
{
	if (GetCollider())
	{
		_InertiaTensor._11 = 2 / 5 * _mass * pow(GetCollider()->GetRaidus(), 2);
		_InertiaTensor._22 = 2 / 5 * _mass * pow(GetCollider()->GetRaidus(), 2);
		_InertiaTensor._33 = 2 / 5 * _mass * pow(GetCollider()->GetRaidus(), 2);
	}

	Quaternion orientation = _transfrom->GetOrientation();
	orientation += orientation * _angularVelocity * 0.5 * deltaTime;
	
	if (orientation.Magnitude() != 0)
		orientation / orientation.Magnitude();

	_transfrom->SetOrientation(orientation);

	_angularVelocity *= pow(_angularDampening, deltaTime);

	PhysicsModel::Update(deltaTime);
}
