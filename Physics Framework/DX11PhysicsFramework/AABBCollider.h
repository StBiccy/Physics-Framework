#pragma once
#include "Collider.h"

class AABBCollider : public Collider
{
private:
	Vector3 _min;
	Vector3 _max;

	Vector3 _Extense;
	Vector3 _HalfExtense;
	Vector3 _Center;

public:
	AABBCollider(Transform* tf, Vector3 min, Vector3 max);


	virtual bool CollidesWith(Collider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(AABBCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;

	virtual float GetRaidus() override{ return 0.0f; }

	bool IsValid();

	void Fix();

};

