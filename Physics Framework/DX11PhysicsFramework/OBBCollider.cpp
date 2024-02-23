#include "OBBCollider.h"

OBBCollider::OBBCollider(Transform* tf, Vector3 halfExtents, Quaternion orientation) : Collider(tf)
{
	_Center = transform->GetPosition();
	_HalfExtents = halfExtents;
	_Extents = halfExtents * 2;
	_orientation = orientation;
	XMStoreFloat3x3(&_rotation, XMMatrixIdentity());

}

bool OBBCollider::CollidesWith(Collider& other, CollisionManifold& out)
{
	return other.CollidesWith(*this, out);
}

bool OBBCollider::CollidesWith(AABBCollider& other, CollisionManifold& out)
{
	return false;
}

bool OBBCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
	return false;
}

bool OBBCollider::CollidesWith(OBBCollider& other, CollisionManifold& out)
{
	//cal rotation / orientation
	_Center = GetPosition();
	Quaternion orientation = transform->GetOrientation();
	Quaternion OtherOrientation = other.transform->GetOrientation();

	XMMATRIX rotation = CalculateRotationMatirx(orientation, _orientation, &_rotation);
	XMMATRIX otherRotation = CalculateRotationMatirx(OtherOrientation, other._orientation, &other._rotation);


	//cal axis
	Vector3 axes[3]; 
	Vector3 otherAxes[3];

	CalculateAxes(rotation, axes);
	CalculateAxes(otherRotation, otherAxes);

	//cal vertices
	float HalfExtents[3] = { _HalfExtents.x,_HalfExtents.y,_HalfExtents.z };
	Vector3 vertices[8];


	other._Center = other.GetPosition();
	float otherHalfExtents[3] = { other._HalfExtents.x,other._HalfExtents.y,other._HalfExtents.z };
	Vector3 otherVertices[8];

	CalculateVertices(_Center, axes, HalfExtents, vertices);
	CalculateVertices(other._Center, otherAxes, otherHalfExtents, otherVertices);

	//sperating axis
	for (int i = 0; i < 3; ++i) {

		if (!CheckSeparatingAxis(*this, other, axes[i], vertices, otherVertices))
			continue;
			//return false;
	}
	for (int i = 0; i < 3; ++i) {
		if (!CheckSeparatingAxis(*this, other, otherAxes[i], vertices, otherVertices))
			return false;
	}

	return true;
}

bool OBBCollider::CheckSeparatingAxis(OBBCollider& obb1, OBBCollider& obb2, Vector3& axis, Vector3 obb1Verts[], Vector3 obb2Verts[])
{
	float min1 = FLT_MAX;
	float max1 = -FLT_MAX;
	for (int i = 0; i < 8; ++i) {
		float projection = Vmath::Dot(obb1Verts[i], axis);
		min1 = fmin(min1, projection);
		max1 = fmax(max1, projection);
	}

	float min2 = FLT_MAX;
	float max2 = -FLT_MAX;
	for (int i = 0; i < 8; ++i) {
		float projection = Vmath::Dot(obb2Verts[i], axis);
		min2 = fmin(min2, projection);
		max2 = fmax(max2, projection);
	}


	if (max1 < min2 || max2 < min1) {
		return false;
	}


	return true;
}

XMMATRIX OBBCollider::CalculateRotationMatirx(Quaternion& newOrientation, Quaternion& storedOrientation, XMFLOAT3X3* rotation)
{
	XMMATRIX rotationMatrix;
	if (storedOrientation != newOrientation) {
		storedOrientation = newOrientation;
		rotationMatrix = XMMatrixRotationQuaternion(XMVectorSet(newOrientation.v.x, newOrientation.v.y, newOrientation.v.z, newOrientation.n));
		XMStoreFloat3x3(rotation, rotationMatrix);
	}
	else {
		rotationMatrix = XMLoadFloat3x3(rotation);
	}
	return rotationMatrix;
}

void OBBCollider::CalculateAxes(XMMATRIX& rotation, Vector3 axes[3])
{
	XMFLOAT3X3 rot3x3;
	XMStoreFloat3x3(&rot3x3, rotation);
	axes[0] = Vmath::Normalise(Vector3(rot3x3._11, rot3x3._12, rot3x3._13));
	axes[1] = Vmath::Normalise(Vector3(rot3x3._21, rot3x3._22, rot3x3._23));
	axes[2] = Vmath::Normalise(Vector3(rot3x3._31, rot3x3._32, rot3x3._33));
}

void OBBCollider::CalculateVertices(Vector3& center, Vector3 axes[3], float halfExtents[3], Vector3 vertices[8])
{
	for (int i = 0; i < 8; ++i) {
		Vector3 vertex = center;
		for (int j = 0; j < 3; ++j) {
			// Add or subtract extents along each axis
			vertex += axes[j] * (halfExtents[j] * ((i >> j) & 1 ? 1 : -1));
		}
		vertices[i] = vertex;
	}
}


