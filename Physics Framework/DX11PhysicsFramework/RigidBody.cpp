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

void RigidBody::OnSetCollider()
{
	Collider* collider = GetCollider();

	if (SphereCollider* sphere = dynamic_cast<SphereCollider*>(collider))
	{
		float factor = 2 / 5 * _mass;

		_InertiaTensor._11 = factor * pow(sphere->GetRaidus(), 2);
		_InertiaTensor._22 = factor * _mass * pow(sphere->GetRaidus(), 2);
		_InertiaTensor._33 = factor * _mass * pow(sphere->GetRaidus(), 2);
	}
	else if (AABBCollider* aabb = dynamic_cast<AABBCollider*>(collider))
	{
		Vector3 extenseSQ = aabb->GetExtense();

		extenseSQ.x = extenseSQ.x * extenseSQ.x;
		extenseSQ.y = extenseSQ.y * extenseSQ.y;
		extenseSQ.z = extenseSQ.z * extenseSQ.z;

		float factor = 12 / _mass;

		_InertiaTensor._11 = factor * (extenseSQ.y + extenseSQ.z);
		_InertiaTensor._22 = factor * (extenseSQ.x + extenseSQ.z);
		_InertiaTensor._33 = factor * (extenseSQ.x + extenseSQ.y);
	}
	
}

void RigidBody::Update(float deltaTime)
{
	if (_mass == 0)
	{
		return;
	}

	Quaternion orientation = _transfrom->GetOrientation();
	orientation += orientation * _angularVelocity * 0.5 * deltaTime;
	
	if (orientation.Magnitude() != 0)
		orientation / orientation.Magnitude();

	_transfrom->SetOrientation(orientation);

	_angularVelocity *= pow(_angularDampening, deltaTime);

	PhysicsModel::Update(deltaTime);
}
