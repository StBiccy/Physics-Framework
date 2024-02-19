#pragma once
#include "Transform.h"
#include "Structures.h"

class SphereCollider;
class AABBCollider;

class Collider abstract
{
protected:
	Transform* _transfrom;
public:
	Collider(Transform* tf) { _transfrom = tf; }

	virtual bool CollidesWith(Collider& other , CollisionManifold& out) = 0;
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) = 0;
	virtual bool CollidesWith(AABBCollider& other, CollisionManifold& out) = 0;
	virtual float GetRaidus() = 0;

	Vector3 GetPosition() const { return _transfrom->GetPosition(); }
};

