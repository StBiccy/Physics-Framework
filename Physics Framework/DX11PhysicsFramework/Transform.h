#pragma once
#include <directxmath.h>


using namespace DirectX;

class Transform
{
private:
	XMFLOAT3 _position;
	XMFLOAT3 _scale;
	XMFLOAT3 _rotation;

	XMFLOAT4X4 _world;

public:
	Transform();
	~Transform();

	void Update(float dt);

	// Setters and Getters for position/rotation/scale
	void SetPosition(XMFLOAT3 position) { _position = position; }
	void SetPosition(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }

	XMFLOAT3 GetPosition() const { return _position; }

	void SetScale(XMFLOAT3 scale) { _scale = scale; }
	void SetScale(float x, float y, float z) { _scale.x = x; _scale.y = y; _scale.z = z; }

	XMFLOAT3 GetScale() const { return _scale; }

	void SetRotation(XMFLOAT3 rotation) { _rotation = rotation; }
	void SetRotation(float x, float y, float z) { _rotation.x = x; _rotation.y = y; _rotation.z = z; }

	XMFLOAT3 GetRotation() const { return _rotation; }

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }
	XMFLOAT4X4 GetWorld() const { return _world; }

	void Move(XMFLOAT3 direction);
};

