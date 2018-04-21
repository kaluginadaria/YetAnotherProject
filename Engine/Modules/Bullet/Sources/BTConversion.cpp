#include "BTConvertion.hpp"

btVector3& operator<<(btVector3& l, const FVector& r)
{
	l.setX(r.X);
	l.setY(r.Y);
	l.setZ(r.Z);
	return l;
}

btQuaternion& operator<<(btQuaternion& l, const FQuat& r)
{
	l.setX(r.X);
	l.setY(r.Y);
	l.setZ(r.Z);
	l.setW(r.W);
	return l;
}

btTransform& operator<<(btTransform& l, const FTransform& r)
{
	l.setRotation(btQuaternion() << r.Rotation);
	l.setOrigin  (btVector3()    << r.Location);
	return l;
}

FVector& operator<<(FVector& l, const btVector3& r)
{
	l.X = r.x();
	l.Y = r.y();
	l.Z = r.z();
	return l;
}

FQuat& operator<<(FQuat& l, const btQuaternion& r)
{
	l.X = r.x();
	l.Y = r.y();
	l.Z = r.z();
	l.W = r.w();
	return l;
}

FTransform& operator<<(FTransform& l, const btTransform& r)
{
	l.Rotation = FQuat()   << r.getRotation();
	l.Location = FVector() << r.getOrigin();
	return l;
}