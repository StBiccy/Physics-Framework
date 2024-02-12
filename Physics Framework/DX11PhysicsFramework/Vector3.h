#pragma once
#include <directxmath.h>
#include <math.h>
using namespace DirectX;

float const tol = 0.0001f;

struct Vector3
{
	float x, y, z;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	};
	
	static Vector3 Zero()
	{
		return Vector3(0, 0, 0);
	}
#pragma region +

	Vector3 operator + (const Vector3& other) const
	{	return Vector3(x + other.x, y + other.y, z + other.z);	}

	Vector3 operator += (const Vector3& other) 
	{	return Vector3(x += other.x, y += other.y, z += other.z);	}

#pragma endregion

#pragma region -

	Vector3 operator - (const Vector3& other) const
	{	return Vector3(x - other.x, y - other.y, z - other.z);	}

	Vector3 operator -= (const Vector3& other) 
	{	return Vector3(x -= other.x, y -= other.y, z -= other.z);	}

#pragma endregion
	
#pragma region /
	template <typename t>
	Vector3 operator /(const t val)const
	{	return Vector3(x / static_cast<float>(val), y / static_cast<float>(val), z / static_cast<float>(val));	}

	template <typename t>
	Vector3 operator /= (const t val) 
	{	return Vector3(x /= static_cast<float>(val), y /= static_cast<float>(val), z /= static_cast<float>(val));	}
#pragma endregion

#pragma region *
		template <typename t> 
		Vector3 operator *(const t val) const
		{	return Vector3(x * static_cast<float>(val), y * static_cast<float>(val), z * static_cast<float>(val));	}
		
		template <typename t> const
		Vector3 operator *= (const t val) 
		{	return Vector3(x *= static_cast<float>(val), y *= static_cast<float>(val), z *= static_cast<float>(val));	}
#pragma endregion

#pragma region bool
		
		bool operator ==(const Vector3& other) const
		{	return x == other.x && y == other.y && z == other.z;	}

		bool operator != (Vector3& other) const
		{	return x != other.x && y != other.y && z != other.z;	}
#pragma endregion

#pragma region negative
		Vector3 operator -() const
		{	return { -x, -y, -z };	};
#pragma endregion

#pragma region XMFLOAT
		operator XMFLOAT3 () const
	{	return XMFLOAT3(x, y, z);	}

		Vector3 operator = (const XMFLOAT3& val) const
		{	return Vector3(val.x, val.y, val.z);	}
#pragma endregion
		

			operator XMVECTOR () const
		{
			return XMLoadFloat3(&XMFLOAT3(x,y,z));
		}

		Vector3 operator = (const XMVECTOR& val) const
		{
			XMFLOAT3 float3;
			XMStoreFloat3(&float3, val);

			return Vector3(float3.x, float3.y, float3.z);
		}
};

namespace Vmath
{

	static float Magnitude(Vector3 val)
	{
		if (val == Vector3::Zero())
		{
			return 0;
		}
		return sqrt(pow(val.x, 2) + pow(val.y, 2) + pow(val.z, 2));
	}

	static Vector3 Normalise(Vector3 val)
	{
		if (val == Vector3::Zero())
		{
			return Vector3::Zero();
		}

		return val / Magnitude(val);
	}

	static float Dot(Vector3 left, Vector3 right)
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	static Vector3 Cross(Vector3 u, Vector3 v)
	{
		return Vector3(u.y * v.z - u.z * v.y,
			-u.x * v.z + u.z * v.x,
			u.x * v.y - u.y * v.x);
	}
}