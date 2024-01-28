#pragma once
#include <directxmath.h>

using namespace DirectX;

struct Vector3
{
	float x, y, z;

	Vector3(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	};
	
	Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
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
	Vector3 operator /= (const t val) const
	{	return Vector3(x /= static_cast<float>(val), y /= static_cast<float>(val), z /= static_cast<float>(val));	}
#pragma endregion

#pragma region *
		template <typename t> const
		Vector3 operator *(const t val) const
		{	return Vector3(x * static_cast<float>(val), y * static_cast<float>(val), z * static_cast<float>(val));	}

		template <typename t> const
		Vector3 operator *= (const t val) const
		{	return Vector3(x *= static_cast<float>(val), y *= static_cast<float>(val), z *= static_cast<float>(val));		}
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
#pragma endregion


};