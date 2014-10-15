#pragma once

#include <math.h>
#include <random>

class SospVector3
{
private:
	float x;
	float y;
	float z;

public:
	SospVector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	SospVector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float GetX() { return x; }
	float GetY() { return y; }
	float GetZ() { return z; }

	void RandomVector3(int minimumVal, int maximumVal)
	{
		x = rand() % maximumVal + (minimumVal);
		y = rand() % maximumVal + (minimumVal);
		z = rand() % maximumVal + (minimumVal);
	}

	void Add(SospVector3 b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
	}

	void Subtract(SospVector3 b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
	}

	float Dot(SospVector3 b)
	{
		return acos((x * b.x + y * b.y + z * b.z) / (Magnitude() * b.Magnitude()));
	}

	SospVector3 Cross(SospVector3 b)
	{
		SospVector3 vec;

		vec.x = (y * b.z) - (z * b.y);
		vec.y = (z * b.x) - (x * b.z);
		vec.z = (x * b.y) - (y * b.x);

		return vec;
	}
	
	// Multiply the vector by a scalar value
	void Multiply(float value)
	{
		x *= value;
		y *= value;
		z *= value;
	}

	// Divide the vector by a scalar value
	void Divide(float value)
	{
		x /= value;
		y /= value;
		z /= value;
	}

	void Divide(SospVector3 b)
	{
		x /= b.x;
		y /= b.y;
		z /= b.z;
	}

	float Magnitude()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float MagnitudeSquared()
	{
		return (x*x) + (y*y) + (z*z);
	}

	SospVector3 Normalize()
	{
		float vectorMagnitude = Magnitude();
		x = x / vectorMagnitude;
		y = y / vectorMagnitude;
		z = z / vectorMagnitude;
	}
};