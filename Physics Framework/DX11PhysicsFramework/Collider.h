#pragma once
#include "Transform.h"

class SphereCollider;

class Collider abstract
{
protected:
	Transform* _transfrom;
public:
	Collider(Transform* tf) { _transfrom = tf; }

	virtual bool CollidesWith(Collider& other) = 0;
	virtual bool CollidesWith(SphereCollider& other) = 0;
	virtual float GetRaidus() = 0;

	Vector3 GetPosition() const { return _transfrom->GetPosition(); }
};

