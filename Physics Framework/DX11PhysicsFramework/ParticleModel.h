#pragma once
#include "PhysicsModel.h"

class ParticleModel : public PhysicsModel
{
public:
	ParticleModel(Transform* transform);
	void addFource(XMFLOAT3 force) { XMStoreFloat3(&_netForce, XMLoadFloat3(&_netForce) + XMLoadFloat3(&force)); }
private:
	XMFLOAT3 _netForce;
	float _mass = 1.0f;
};

