#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
private:
	float _radius = 1.0f;

public:
	SphereCollider(Transform* tf, float r) : Collider(tf) { _radius = r; }

	virtual bool CollidesWith(Collider& other) override { return other.CollidesWith(*this); }
	virtual bool CollidesWith(SphereCollider& other) override;

	float GetRaidus() const { return _radius; }
};
