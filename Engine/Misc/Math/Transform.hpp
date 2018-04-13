#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Quat.hpp"
#include "Vector.hpp"



class FTransform
{
public:

	FVector Location; // positions of a center
	FQuat   Rotation; // ratation around the center

public:

	FTransform() = default;

	FTransform(const FQuat& q, const FVector& v)
		: Location (v)
		, Rotation (q)
	{}

	FTransform(const FQuat& q)
		: Location (FVector::ZeroVector)
		, Rotation (q)
	{}

	FTransform(const FVector& v)
		: Location (v)
		, Rotation (FQuat::Identity)
	{}

	FTransform(const FTransform& r)
		: Location (r.Location)
		, Rotation (r.Rotation)
	{}

	FTransform& operator=(const FTransform& r)
	{
		Location = r.Location;
		Rotation = r.Rotation;
		return *this;
	}

public: //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| Rotatins and Translations

	/** Apply the transform to the vector 
	* @param v - vector in a transform's parent coorditates
	* @return	- rotated and translated vector					*/
	FVector operator()(const FVector& v) const
	{
		return Rotation * v + Location;
	}

	FVector operator*(const FVector& v) const
	{
		return (*this)(v);
	}

	/** Apply the transform to the quaternion
	* @param q - quaternion in a transform's parent coorditates
	* @return	- rotated quaternion							*/
	FQuat operator()(const FQuat& q) const
	{
		return Rotation * q;
	}

	FQuat operator*(const FQuat& q) const
	{
		return (*this)(q);
	}

public: //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| 

	FTransform operator*(const FTransform& r) const
	{
		FTransform tmp = *this;
		return (tmp *= r);
	}

	// ?=

	FTransform& operator*=(const FTransform& r)
	{
		Location = (*this) * r.Location;
		Rotation *= r.Rotation;
		return *this;
	}

	FTransform& operator+=(const FTransform& r)
	{
		Rotation = r.Rotation * Rotation;
		Location = r.Location + Location;
		return *this;
	}

	FTransform& operator+=(const FQuat& r)
	{
		Rotation = r * Rotation;
		return *this;
	}

	FTransform& operator+=(const FVector& r)
	{
		Location += r;
		return *this;
	}

public: //~~~~~~~~~~~~~~| unary

	FTransform operator~() const
	{
		FQuat inv = ~Rotation;
		return FTransform(inv, inv * -Location);
	}

public: //~~~~~~~~~~~~~~| misc

	std::string ToString() const
	{
		return "R:{" + Rotation.ToString() + "}"
			+  "LL{" + Location.ToString() + "}";
	}

public: //~~~~~~~~~~~~~~| constants

	static const FTransform Identity;
};


inline FTransform operator*(const FQuat& q, const FTransform& t)
{
	return FTransform(q * t.Rotation, q * t.Location);
}



// constants
const FTransform FTransform::Identity = FTransform();

#endif // TRANSFORM_HPP
