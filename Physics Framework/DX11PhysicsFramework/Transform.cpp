#include "Transform.h"

Transform::Transform()
{
	_position = Vector3::Zero();
	
	_scale = Vector3(1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{
}

void Transform::Update(float dt)
{
	Vector3 rot = GetRotation();

	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	XMMATRIX rotation = XMMatrixRotationQuaternion(XMVectorSet(_orientation.v.x, _orientation.v.y, _orientation.v.z, _orientation.n));
	XMMATRIX translation = XMMatrixTranslation(_position.x, _position.y, _position.z);

	XMStoreFloat4x4(&_world, scale * rotation * translation);
}

void Transform::Move(Vector3 direction)
{
	_position.x += direction.x;
	_position.y += direction.y;
	_position.z += direction.z;
}