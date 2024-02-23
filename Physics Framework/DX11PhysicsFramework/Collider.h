#pragma once
#include "Transform.h"
#include "Structures.h"

class SphereCollider;
class AABBCollider;
class OBBCollider;


class Collider abstract
{
protected:
	Transform* transform;
public:
	Collider(Transform* tf) { transform = tf; }

	virtual bool CollidesWith(Collider& other , CollisionManifold& out) = 0;
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) = 0;
	virtual bool CollidesWith(AABBCollider& other, CollisionManifold& out) = 0;
	virtual bool CollidesWith(OBBCollider& other, CollisionManifold& out) = 0;

	Vector3 GetPosition() const { return transform->GetPosition(); }
};

