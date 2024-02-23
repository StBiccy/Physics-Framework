#pragma once
#include "Collider.h"
#include "SphereCollider.h"
#include "AABBCollider.h"


class OBBCollider : public Collider
{
private:

	XMFLOAT3X3 _rotation;
	Quaternion _orientation;

	Vector3 _Extents;
	Vector3 _HalfExtents;
	Vector3 _Center;

public:
	OBBCollider(Transform* tf, Vector3 halfExtents, Quaternion orientation);


	virtual bool CollidesWith(Collider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(AABBCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(OBBCollider& other, CollisionManifold& out) override;


	bool CheckSeparatingAxis(OBBCollider& obb1, OBBCollider& obb2, Vector3& axes, Vector3 obb1Verts[], Vector3 obb2Verts[]);
	XMMATRIX CalculateRotationMatirx(Quaternion& orientaiton, Quaternion& storedOrientation, XMFLOAT3X3* rotation);
	void CalculateAxes(XMMATRIX& rotation, Vector3 axes[3]);
	void CalculateVertices(Vector3& center, Vector3 axes[3], float halfExtents[3], Vector3 vertices[8]);

	Vector3 GetExtents() { return _Extents; }
	XMFLOAT3X3 GetOrientation() { return _rotation; }
};
