#include "Vector.hpp"

#include <assert.h>
#include <cmath>

// constants
const FVector FVector::ZeroVector = FVector( 0, 0, 0);
const FVector FVector::Forward    = FVector( 1, 0, 0);
const FVector FVector::Backward   = FVector(-1, 0, 0);
const FVector FVector::Upward     = FVector( 0, 0, 1);
const FVector FVector::Downward   = FVector( 0, 0,-1);
const FVector FVector::Leftward   = FVector( 0, 1, 0);
const FVector FVector::Rightward  = FVector( 0,-1, 0);




FVector::FVector(float X, float Y, float Z)
	: X(X), Y(Y), Z(Z)
{}

FVector::FVector(const FVector& r)
	: X(r.X), Y(r.Y), Z(r.Z)
{}

FVector& FVector::operator=(const FVector& r)
{
	X = r.X;
	Y = r.Y;
	Z = r.Z;
	return *this;

}

float& FVector::operator[](int i)
{
	assert(i >= 0 && i < 3);
	switch (i) {
	case 0: return X;
	case 1: return Y;
	case 2: return Z;
	}
}

float FVector::operator[](int i) const
{
	assert(i >= 0 && i < 3);
	switch (i) {
	case 0: return X;
	case 1: return Y;
	case 2: return Z;
	}
}

FVector FVector::operator+(const FVector& r) const
{
	return FVector(
		X + r.X,
		Y + r.Y,
		Z + r.Z);
}

FVector FVector::operator-(const FVector& r) const
{
	return FVector(
		X - r.X,
		Y - r.Y,
		Z - r.Z);
}

FVector FVector::operator*(const FVector& r) const
{
	return FVector(
		X * r.X,
		Y * r.Y,
		Z * r.Z);
}

FVector FVector::operator/(const FVector& r) const
{
	return FVector(
		X / r.X,
		Y / r.Y,
		Z / r.Z);
}

FVector FVector::operator^(const FVector& r) const
{
	return FVector(
		Y * r.Z - r.Y * Z,
		Z * r.X - r.Z * X,
		X * r.Y - r.X * Y);
}

FVector& FVector::operator-=(const FVector& r)
{
	X -= r.X;
	Y -= r.Y;
	Z -= r.Z;
	return *this;
}

FVector& FVector::operator+=(const FVector& r)
{
	X += r.X;
	Y += r.Y;
	Z += r.Z;
	return *this;
}

FVector& FVector::operator*=(const FVector& r)
{
	X *= r.X;
	Y *= r.Y;
	Z *= r.Z;
	return *this;
}

FVector& FVector::operator/=(const FVector& r)
{
	X /= r.X;
	Y /= r.Y;
	Z /= r.Z;
	return *this;
}

FVector& FVector::operator^=(const FVector& r)
{
	X = Y * r.Z - r.Y * Z;
	Y = Z * r.X - r.Z * X;
	Z = X * r.Y - r.X * Y;
	return *this;
}

FVector FVector::operator+(float r)
{
	return FVector(
		X + r,
		Y + r,
		Z + r);
}

FVector FVector::operator-(float r)
{
	return FVector(
		X - r,
		Y - r,
		Z - r);
}

FVector FVector::operator*(float r)
{
	return FVector(
		X * r,
		Y * r,
		Z * r);
}

FVector FVector::operator/(float r)
{
	return FVector(
		X / r,
		Y / r,
		Z / r);
}

FVector& FVector::operator+=(float r)
{
	X += r;
	Y += r;
	Z += r;
	return *this;
}

FVector& FVector::operator-=(float r)
{
	X -= r;
	Y -= r;
	Z -= r;
	return *this;
}

FVector& FVector::operator*=(float r)
{
	X *= r;
	Y *= r;
	Z *= r;
	return *this;
}

FVector& FVector::operator/=(float r)
{
	X /= r;
	Y /= r;
	Z /= r;
	return *this;
}

FVector FVector::operator-() const
{
	return FVector(-X, -Y, -Z);
}

bool FVector::operator==(const FVector& r) const
{
	return X == r.X
		&& Y == r.Y
		&& Z == r.Z;
}

bool FVector::operator!=(const FVector& r) const
{
	return !(*this == r);
}

float FVector::Size() const
{
	return std::sqrtf(X*X + Y*Y + Z*Z);
}

float FVector::SizeSq() const
{
	return X*X + Y*Y + Z*Z;
}

FVector FVector::GetNormal() const
{
	float size = Size();
	return FVector(
		X / size,
		Y / size,
		Z / size);
}

FVector& FVector::Normalise()
{
	float size = Size();
	X /= size;
	Y /= size;
	Z /= size;
	return *this;
}

FVector FVector::Lerp(const FVector& r, float factor)
{
	return (*this) - (r - (*this)) * factor;
}

std::string FVector::ToString() const
{
	return "X: " + std::to_string(X) + " "
		+  "Y: " + std::to_string(Y) + " "
		+  "Z: " + std::to_string(Z);
}