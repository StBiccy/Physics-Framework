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
	return false;
}
