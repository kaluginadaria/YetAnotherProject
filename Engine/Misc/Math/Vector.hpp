#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <assert.h>
#include <string>
#include <cmath>


struct FVector
{
public:
	float X;
	float Y;
	float Z;

public:

	FVector(float X = 0, float Y = 0, float Z = 0)
		: X(X), Y(Y), Z(Z)
	{}

	FVector(const FVector& r)
		: X(r.X), Y(r.Y), Z(r.Z)
	{}

	FVector& operator=(const FVector& r)
	{
		X = r.X;
		Y = r.Y;
		Z = r.Z;
		return *this;

	}

	float& operator[](int i)
	{
		assert(i >= 0 && i < 3);
		switch (i)
		{
		case 0: return X;
		case 1: return Y;
		case 2: return Z;
		}
	}

	float operator[](int i) const
	{
		assert(i >= 0 && i < 3);
		switch (i)
		{
		case 0: return X;
		case 1: return Y;
		case 2: return Z;
		}
	}

public: //~~~~~~~~~~~~~~| vector - vector

	FVector operator+(const FVector& r) const
	{
		return FVector(
			X + r.X,
			Y + r.Y,
			Z + r.Z);
	}

	FVector operator-(const FVector& r) const
	{
		return FVector(
			X - r.X,
			Y - r.Y,
			Z - r.Z);
	}

	FVector operator*(const FVector& r) const
	{
		return FVector(
			X * r.X,
			Y * r.Y,
			Z * r.Z);
	}

	FVector operator/(const FVector& r) const
	{
		return FVector(
			X / r.X,
			Y / r.Y,
			Z / r.Z);
	}

	FVector operator^(const FVector& r) const
	{
		return FVector(
			Y * r.Z - r.Y * Z,
			Z * r.X - r.Z * X,
			X * r.Y - r.X * Y);
	}

	// ?=

	FVector& operator-=(const FVector& r)
	{
		X -= r.X;
		Y -= r.Y;
		Z -= r.Z;
		return *this;
	}

	FVector& operator+=(const FVector& r)
	{
		X += r.X;
		Y += r.Y;
		Z += r.Z;
		return *this;
	}

	FVector& operator*=(const FVector& r)
	{
		X *= r.X;
		Y *= r.Y;
		Z *= r.Z;
		return *this;
	}

	FVector& operator/=(const FVector& r)
	{
		X /= r.X;
		Y /= r.Y;
		Z /= r.Z;
		return *this;
	}

	FVector& operator^=(const FVector& r)
	{
		X = Y * r.Z - r.Y * Z;
		Y = Z * r.X - r.Z * X;
		Z = X * r.Y - r.X * Y;
		return *this;
	}

public: //~~~~~~~~~~~~~~| vector - scalar

	FVector operator+(float r)
	{
		return FVector(
			X + r,
			Y + r,
			Z + r);
	}

	FVector operator-(float r)
	{
		return FVector(
			X - r,
			Y - r,
			Z - r);
	}

	FVector operator*(float r)
	{
		return FVector(
			X * r,
			Y * r,
			Z * r);
	}

	FVector operator/(float r)
	{
		return FVector(
			X / r,
			Y / r,
			Z / r);
	}

	// ?=

	FVector& operator+=(float r)
	{
		X += r;
		Y += r;
		Z += r;
		return *this;
	}

	FVector& operator-=(float r)
	{
		X -= r;
		Y -= r;
		Z -= r;
		return *this;
	}

	FVector& operator*=(float r)
	{
		X *= r;
		Y *= r;
		Z *= r;
		return *this;
	}

	FVector& operator/=(float r)
	{
		X /= r;
		Y /= r;
		Z /= r;
		return *this;
	}

public: //~~~~~~~~~~~~~~| unary

	FVector operator-() const
	{
		return FVector(-X, -Y, -Z);
	}

public: //~~~~~~~~~~~~~~| equation

	bool operator==(const FVector& r) const
	{
		return X == r.X
			&& Y == r.Y
			&& Z == r.Z;
	}

	bool operator!=(const FVector& r) const
	{
		return !(*this == r);
	}

public: //~~~~~~~~~~~~~~| size

	float Size() const
	{
		return std::sqrtf(X*X + Y*Y + Z*Z);
	}

	float SizeSq() const
	{
		return X*X + Y*Y + Z*Z;
	}

	FVector GetNormal() const
	{
		float size = Size();
		return FVector(
			X / size,
			Y / size,
			Z / size);
	}

	FVector& Normalise()
	{
		float size = Size();
		X /= size;
		Y /= size;
		Z /= size;
		return *this;
	}

public: //~~~~~~~~~~~~~~| misc

	FVector Lerp(const FVector& r, float factor)
	{
		return (*this) - (r - (*this)) * factor;
	}

	std::string ToString() const
	{
		return "X: " + std::to_string(X) + " "
			+  "Y: " + std::to_string(Y) + " "
			+  "Z: " + std::to_string(Z);
	}

public: //~~~~~~~~~~~~~~| constants

	static const FVector ZeroVector;

	static const FVector Forward;
	static const FVector Backward;
	
	static const FVector Upward;
	static const FVector Downward;
	
	static const FVector Leftward;
	static const FVector Rightward;
};





// constants
const FVector FVector::ZeroVector = FVector( 0, 0, 0);
const FVector FVector::Forward    = FVector( 1, 0, 0);
const FVector FVector::Backward   = FVector(-1, 0, 0);
const FVector FVector::Upward     = FVector( 0, 0, 1);
const FVector FVector::Downward   = FVector( 0, 0,-1);
const FVector FVector::Leftward   = FVector( 0, 1, 0);
const FVector FVector::Rightward  = FVector( 0,-1, 0);

#endif //!VECTOR_HPP