#include "RigidBody.h"

RigidBody::RigidBody(Transform* tf) : PhysicsModel(tf)
{
	XMStoreFloat3x3(&_InertiaTensor, XMMatrixIdentity());

	_InertiaTensor._11 = 2 / 5 * _mass * pow(GetCollider()->GetRaidus(), 2);
	_InertiaTensor._22 = 2 / 5 * _mass * pow(GetCollider()->GetRaidus(), 2);
	_InertiaTensor._33 = 2 / 5 * _mass * pow(GetCollider()->GetRaidus(), 2);


}

void RigidBody::AddRelativeForce(Vector3 force, Vector3 point)
{
	AddForce(force);
	_torque = Vmath::Cross(point, force);
}

void RigidBody::CalculateAngularVelocity()
{
	Vector3 AngularAcceleration;

}

void RigidBody::Update(float deltaTime)
{
	PhysicsModel::Update(deltaTime);

}
