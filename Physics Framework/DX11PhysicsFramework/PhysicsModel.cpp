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

	if (_mass == 0)
	{
		return;
	}

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


Vector3 PhysicsModel::FrictionForce()
{
	{
		if (Vmath::Magnitude(_netForce) < Vmath::Magnitude(Vmath::Normalise(_netForce) * _staticCoeff))
		{
			_netForce = Vector3::Zero();
		}

		return -Vmath::Normalise(_velocity) * _keneticCoeff;
	}
}

Vector3 PhysicsModel::DragForce()
{
	float scalerDrag = 0.5f * _density * _dragCoefficient * _refrenceArea;
	return -Vmath::Normalise(_velocity) * scalerDrag;
}
