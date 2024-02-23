#include "SphereCollider.h"

bool SphereCollider::CollidesWith(Collider& other, CollisionManifold& out)
{
	return other.CollidesWith(*this, out); 
;
}

bool SphereCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
	Vector3 diff = other.GetPosition() - GetPosition();
	float radiiSum = other.GetRaidus() + GetRaidus();

	if (Vmath::Magnitude(diff) < radiiSum)
	{
		out.collisionNormal = diff;
		out.collisionNormal = Vmath::Normalise(out.collisionNormal);
		out.contactPointCount = 1;
		out.points[0].Position = GetPosition() + out.collisionNormal * GetRaidus();
		out.points[0].penetartionDepth = fabs(Vmath::Magnitude(diff) - radiiSum);

		return true;
	}

	return false;
}

bool SphereCollider::CollidesWith(AABBCollider& other, CollisionManifold& out)
{
	Vector3 clamp;

	Vector3 min = other.GetMin();
	Vector3 max = other.GetMax();

	clamp.x = fmax(other.GetPosition().x + min.x, fmin(GetPosition().x, other.GetPosition().x + max.x));
	clamp.y = fmax(other.GetPosition().y + min.y, fmin(GetPosition().y, other.GetPosition().y + max.y));
	clamp.z = fmax(other.GetPosition().z + min.z, fmin(GetPosition().z, other.GetPosition().z + max.z));

	Vector3 diff = GetPosition() - clamp;

	float diffSQ = pow(Vmath::Magnitude(diff), 2);

	if (diffSQ <= (GetRaidus() * GetRaidus()))
	{
		out.contactPointCount = 1;
		out.collisionNormal = Vmath::Normalise(clamp - GetPosition());
		out.points[0].Position = clamp + (out.collisionNormal * GetRaidus());
		out.points[0].penetartionDepth = fabs(GetRaidus() - Vmath::Magnitude(diff));
		return true;
	}

	return false;
}

bool SphereCollider::CollidesWith(OBBCollider& other, CollisionManifold& out)
{
	return false;
}
