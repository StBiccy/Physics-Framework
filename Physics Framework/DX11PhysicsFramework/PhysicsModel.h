#pragma once
#include "Transform.h"

class PhysicsModel
{
protected:

	Transform* _transfrom;
	XMFLOAT3 _velocity = XMFLOAT3(0, 0, 0);
	XMFLOAT3 _Acceleration = XMFLOAT3(0,0,0);
public:
	PhysicsModel(Transform* transform);
	void Update(float deltaTime);
	XMFLOAT3 GetVelocity() { return _velocity; }
	void SetVelocity(XMFLOAT3 velocity) { _velocity = velocity; }

	void SetAcceleration(XMFLOAT3 acceleration) { _Acceleration = acceleration; }
	XMFLOAT3 GetAcceleration() { return _Acceleration; }

};

