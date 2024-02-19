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
    return false;
}

bool AABBCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
    return false;
}

bool AABBCollider::CollidesWith(AABBCollider& other, CollisionManifold& out)
{
    Vector3 OtherWorldCenter = other.GetPosition() + other._Center;
    Vector3 WorldCenter = GetPosition() + _Center;
    if (WorldCenter.x - _HalfExtense.x > OtherWorldCenter.x - other._HalfExtense.x)
    {
        if (WorldCenter.y - _HalfExtense.y > OtherWorldCenter.y - other._HalfExtense.y)
        {
            if (WorldCenter.z - _HalfExtense.z > OtherWorldCenter.z - other._HalfExtense.z)
            {
                //other stuff
                return true;
            }
        }
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
