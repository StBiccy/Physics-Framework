#pragma once
#include "Quaternion.h"


class Transform
{
private:
	Vector3 _position = Vector3::Zero();
	Vector3 _scale = Vector3::Zero();
	Quaternion _orientation; 

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

	void SetRotation(Vector3 rotation) { _orientation = MakeQFromEulerAngles(rotation.x, rotation.y, rotation.z); }
	void SetRotation(float x, float y, float z) { _orientation = MakeQFromEulerAngles(x, y, z); }

	void SetOrientation(Quaternion orientation) { _orientation = orientation; }

	Vector3 GetRotation() const { return MakeEulerAnglesFromQ(_orientation); }
	Quaternion GetOrientation() const { return _orientation; }

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }
	XMFLOAT4X4 GetWorld() const { return _world; }

	void Move(Vector3 direction);
};

