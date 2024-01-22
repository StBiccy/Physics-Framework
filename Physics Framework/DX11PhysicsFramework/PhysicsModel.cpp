#include "PhysicsModel.h"

PhysicsModel::PhysicsModel(Transform* transform)
{
	_transfrom = transform;
}

void PhysicsModel::Update(float deltaTime)
{
	XMFLOAT3 position = _transfrom->GetPosition();
	XMStoreFloat3(&_velocity, XMLoadFloat3(&_velocity) + XMLoadFloat3(&_Acceleration) * deltaTime);
	XMStoreFloat3(&position, XMLoadFloat3(&position) + (XMLoadFloat3(&_velocity) * deltaTime));

	_transfrom->SetPosition(position);
}
