#include "AABBCollider.h"


AABBCollider::AABBCollider(Transform* tf, Vector3 min, Vector3 max) : Collider(tf) 
{
        _min = min; 
        _max = max;
        if (!IsValid())
            Fix();

        _Extents.x = abs(_max.x - _min.x);
        _Extents.y = abs(_max.y - _min.y);
        _Extents.z = abs(_max.z - _min.z);

        _HalfExtents = _Extents / 2;
        
        _Center = _min + _HalfExtents;
}

bool AABBCollider::CollidesWith(Collider& other, CollisionManifold& out)
{
    return other.CollidesWith(*this, out);
}

bool AABBCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
    Vector3 clamp;

    clamp.x = fmax(GetPosition().x + _min.x, fmin(other.GetPosition().x, GetPosition().x + _max.x));
    clamp.y = fmax(GetPosition().y + _min.y, fmin(other.GetPosition().y, GetPosition().y + _max.y));
    clamp.z = fmax(GetPosition().z + _min.z, fmin(other.GetPosition().z, GetPosition().z + _max.z));

    Vector3 diff = other.GetPosition() - clamp;

    float diffSQ = pow(Vmath::Magnitude(diff), 2);

    if (diffSQ <= (other.GetRaidus() * other.GetRaidus()))
    {
        out.contactPointCount = 1;
        out.collisionNormal = Vmath::Normalise(clamp - other.GetPosition());
        out.points[0].Position = clamp + (out.collisionNormal * other.GetRaidus());
        out.points[0].penetartionDepth = fabs(other.GetRaidus() - Vmath::Magnitude(diff));
        return true;
    }


    return false;
}

bool AABBCollider::CollidesWith(OBBCollider& other, CollisionManifold& out)
{
    return false;
}

bool AABBCollider::CollidesWith(AABBCollider& other, CollisionManifold& out)
{
    Vector3 OtherWorldCenter = other.GetPosition() + other._Center;
    Vector3 WorldCenter = GetPosition() + _Center;

    Vector3 halfExtenseSum = other._HalfExtents + _HalfExtents;

    Vector3 diff = WorldCenter - OtherWorldCenter;
    diff = Vector3(abs(diff.x), abs(diff.y), abs(diff.z));

    if (diff.x <= halfExtenseSum.x && diff.y <= halfExtenseSum.y && diff.z <= halfExtenseSum.z)
    {
        out.collisionNormal = Vector3();
        out.contactPointCount = 1;

        if (diff.x - halfExtenseSum.x > diff.y - halfExtenseSum.y)
        {
            if (diff.x - halfExtenseSum.x > diff.z - halfExtenseSum.z)
            {
                out.collisionNormal.x = (WorldCenter.x < OtherWorldCenter.x) ? -1 : 1;
                out.points[0].Position = WorldCenter + out.collisionNormal * _HalfExtents.x;
                out.points[0].penetartionDepth = fabs(diff.x - halfExtenseSum.x);
                return true;
            }
            else
            {
                out.collisionNormal.z = (WorldCenter.z < OtherWorldCenter.z) ? -1 : 1;
                out.points[0].Position = WorldCenter + out.collisionNormal * _HalfExtents.z;
                out.points[0].penetartionDepth = fabs(diff.z - halfExtenseSum.z);
                return true;
            }
        }
        else if (diff.y - halfExtenseSum.y > diff.z - halfExtenseSum.z)
        {
            out.collisionNormal.y = (WorldCenter.y < OtherWorldCenter.y) ? -1 : 1;
            out.points[0].Position = WorldCenter + out.collisionNormal * _HalfExtents.y;
            out.points[0].penetartionDepth = fabs(diff.y - halfExtenseSum.y);
            return true;
        }
        else
        {
            out.collisionNormal.z = (WorldCenter.z < OtherWorldCenter.z) ? -1 : 1;
            out.points[0].Position = WorldCenter + out.collisionNormal * _HalfExtents.z;
            out.points[0].penetartionDepth = fabs(diff.z - halfExtenseSum.z);
            return true;
        }
        return true;
    }

    return false;
}

bool AABBCollider::IsValid()
{
    return _min.x < _max.x && _min.y < _max.y && _min.z < _max.z;
}

void AABBCollider::Fix()
{
    if (_min.x > _max.x)
    {
        float temp = _min.x;
        _min.x = _max.x;
        _max.x = temp;
    }

    if (_min.y > _max.y)
    {
        float temp = _min.y;
        _min.y = _max.y;
        _max.y = temp;
    }

    if (_min.z > _max.z)
    {
        float temp = _min.z;
        _min.z = _max.z;
        _max.z = temp;
    }
}
