#pragma once
#include "Collider.h"
#include "SphereCollider.h"
#include "OBBCollider.h"

class SphereCollider;

class AABBCollider : public Collider
{
private:
	Vector3 _min;
	Vector3 _max;

	Vector3 _Extents;
	Vector3 _HalfExtents;
	Vector3 _Center;

public:
	AABBCollider(Transform* tf, Vector3 min, Vector3 max);


	virtual bool CollidesWith(Collider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(AABBCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(OBBCollider& other, CollisionManifold& out) override;

	Vector3 GetMin() { return _min; }
	Vector3 GetMax() { return _min; }
	Vector3 GetExtense() { return _Extents; }

	bool IsValid();

	void Fix();

};

