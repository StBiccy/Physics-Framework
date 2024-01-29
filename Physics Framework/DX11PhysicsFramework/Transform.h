#pragma once
#include "Vector3.h"



class Transform
{
private:
	Vector3 _position = Vector3::Zero();
	Vector3 _scale = Vector3::Zero();
	Vector3 _rotation = Vector3::Zero();

	XMFLOAT4X4 _world;
public:
	Transform();
	~Transform();

	void Update(float dt);

	// Setters and Getters for position/rotation/scale
	void SetPosition(Vector3 position) { _position = position; }
	void SetPosition(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }

	Vector3 GetPosition() const { return _position; }

	void SetScale(Vector3 scale) { _scale = scale; }
	void SetScale(float x, float y, float z) { _scale.x = x; _scale.y = y; _scale.z = z; }

	Vector3 GetScale() const { return _scale; }

	void SetRotation(Vector3 rotation) { _rotation = rotation; }
	void SetRotation(float x, float y, float z) { _rotation.x = x; _rotation.y = y; _rotation.z = z; }

	Vector3 GetRotation() const { return _rotation; }

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }
	XMFLOAT4X4 GetWorld() const { return _world; }

	void Move(Vector3 direction);
};

