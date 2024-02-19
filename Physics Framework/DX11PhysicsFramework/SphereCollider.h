#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
private:
	float _radius = 1.0f;

public:
	SphereCollider(Transform* tf, float r) : Collider(tf) { _radius = r; }

	virtual bool CollidesWith(Collider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(AABBCollider& other, CollisionManifold& out) override;
	virtual float GetRaidus() override { return _radius; }
};
