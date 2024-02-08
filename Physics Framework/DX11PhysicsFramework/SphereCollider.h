#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
private:
	float _radius = 1.0f;

public:
	SphereCollider(Transform* tf, float r) : Collider(tf) { _radius = r; }

	virtual bool CollidesWith(Collider& other) override { return other.CollidesWith(*this); }
	virtual bool CollidesWith(SphereCollider& other) override { return _radius + other._radius > Vmath::Magnitude(_transfrom->GetPosition() - other.GetPosition()); };

	virtual float GetRaidus() override { return _radius; }
};
