#include "AABBCollider.h"


AABBCollider::AABBCollider(Transform* tf, Vector3 min, Vector3 max) : Collider(tf) 
{
        _min = min; 
        _max = max;
        if (!IsValid())
            Fix();

        _Extense.x = abs(_max.x - _min.x);
        _Extense.y = abs(_max.y - _min.y);
        _Extense.z = abs(_max.z - _min.z);

        _HalfExtense = _Extense / 2;
        
        _Center = _min + _HalfExtense;
}

bool AABBCollider::CollidesWith(Collider& other, CollisionManifold& out)
{
    return other.CollidesWith(*this, out);
}

bool AABBCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
    Vector3 WorldCenter = GetPosition() + _Center;
    //Vector3 SPhrePos = Vector3(std,,)
    



    return false;
}

bool AABBCollider::CollidesWith(AABBCollider& other, CollisionManifold& out)
{
    Vector3 OtherWorldCenter = other.GetPosition() + other._Center;
    Vector3 WorldCenter = GetPosition() + _Center;

    Vector3 halfExtenseSum = other._HalfExtense + _HalfExtense;

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
                out.points[0].Position = WorldCenter + out.collisionNormal * _HalfExtense.x;
                out.points[0].penetartionDepth = fabs(diff.x - halfExtenseSum.x);
                return true;
            }
            else
            {
                out.collisionNormal.z = (WorldCenter.z < OtherWorldCenter.z) ? -1 : 1;
                out.points[0].Position = WorldCenter + out.collisionNormal * _HalfExtense.z;
                out.points[0].penetartionDepth = fabs(diff.z - halfExtenseSum.z);
                return true;
            }
        }
        else if (diff.y - halfExtenseSum.y > diff.z - halfExtenseSum.z)
        {
            out.collisionNormal.y = (WorldCenter.y < OtherWorldCenter.y) ? -1 : 1;
            out.points[0].Position = WorldCenter + out.collisionNormal * _HalfExtense.y;
            out.points[0].penetartionDepth = fabs(diff.y - halfExtenseSum.y);
            return true;
        }
        else
        {
            out.collisionNormal.z = (WorldCenter.z < OtherWorldCenter.z) ? -1 : 1;
            out.points[0].Position = WorldCenter + out.collisionNormal * _HalfExtense.z;
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
