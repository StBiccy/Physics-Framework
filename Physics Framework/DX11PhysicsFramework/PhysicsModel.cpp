#include "PhysicsModel.h"

PhysicsModel::PhysicsModel(Transform* transform)
{
	_transfrom = transform;
}

PhysicsModel::~PhysicsModel()
{
	if (_collider != nullptr)
	{
		delete _collider;
	}
}

void PhysicsModel::Update(float deltaTime)
{
	Vector3 position = _transfrom->GetPosition();

	if (_simGravity)
		_netForce += GravityForce();
	if (_simDrag)
		_netForce += DragForce();
	if (_simFriction)
		_netForce += FrictionForce();


	_Acceleration += _netForce / _mass;
	_velocity += _Acceleration * deltaTime;

	position += _velocity * deltaTime;
	

	_Acceleration = Vector3::Zero();
	_netForce = Vector3::Zero();

	_transfrom->SetPosition(position);
}
