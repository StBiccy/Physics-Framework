#include "PhysicsModel.h"

PhysicsModel::PhysicsModel(Transform* transform)
{
	_transfrom = transform;
}

void PhysicsModel::Update(float deltaTime)
{
	Vector3 position = _transfrom->GetPosition();

	_Acceleration += _netForce / _mass;
	_velocity += _Acceleration * deltaTime;

	position = _velocity * deltaTime;
	

	_Acceleration = Vector3();
	_netForce = Vector3();

	_transfrom->SetPosition(position);
}
