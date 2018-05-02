#include "Color.hpp"

// constants
const FColor FColor::Red   = FColor(1, 0, 0);
const FColor FColor::Green = FColor(0, 1, 0);
const FColor FColor::Blue  = FColor(0, 0, 1);




FColor::FColor(float R, float G, float B, float A)
	: R(R), G(G), B(B), A(A)
{}

FColor::FColor(const FColor & r)
	: R(r.R), G(r.G), B(r.B), A(r.A)
{}

FColor& FColor::operator=(const FColor& r)
{
	R = r.R;
	G = r.G;
	B = r.B;
	A = r.A;
	return *this;
}

float& FColor::operator[](int i)
{
	switch (i) {
	case 0: return R;
	case 1: return G;
	case 2: return B;
	case 3: return A;
	}
	throw std::out_of_range("");
}

float FColor::operator[](int i) const
{
	switch (i) {
	case 0: return R;
	case 1: return G;
	case 2: return B;
	case 3: return A;
	}
	throw std::out_of_range("");
}

FColor FColor::operator+(const FColor& r) const
{
	return FColor(
		R + r.R,
		G + r.G,
		B + r.B,
		A + r.A);
}

FColor FColor::operator-(const FColor& r) const
{
	return FColor(
		R - r.R,
		G - r.G,
		B - r.B,
		A - r.A);
}

FColor& FColor::operator-=(FColor r)
{
	R -= r.R;
	G -= r.G;
	B -= r.B;
	A -= r.A;
	return *this;
}

FColor& FColor::operator+=(FColor r)
{
	R += r.A;
	G += r.G;
	B += r.B;
	A += r.A;
	return *this;
}

FColor FColor::operator+(float r) const
{
	return FColor(
		R + r,
		G + r,
		B + r,
		A + r);
}

FColor FColor::operator-(float r) const
{
	return FColor(
		R - r,
		G - r,
		B - r,
		A - r);
}

FColor FColor::operator*(float r) const
{
	return FColor(
		R * r,
		G * r,
		B * r,
		A * r);
}

FColor FColor::operator/(float r) const
{
	assert(r); // TODO:: log
	return FColor(
		R / r,
		G / r,
		B / r,
		A / r);
}

FColor& FColor::operator+=(float r)
{
	R += r;
	G += r;
	B += r;
	A += r;
	return *this;
}

FColor& FColor::operator-=(float r)
{
	R -= r;
	G -= r;
	B -= r;
	A -= r;
	return *this;
}

FColor& FColor::operator*=(float r)
{
	R *= r;
	G *= r;
	B *= r;
	A *= r;
	return *this;
}

FColor& FColor::operator/=(float r)
{
	assert(r); // TODO:: log
	R /= r;
	G /= r;
	B /= r;
	A /= r;
	return *this;
}

bool FColor::operator==(const FColor& r) const
{
	return R == r.R
		&& G == r.G
		&& B == r.B
		&& A == r.A;
}

bool FColor::operator!=(const FColor& r) const
{
	return !(*this == r);
}

FColor FColor::Lerp(const FColor & r, float factor)
{
	return (*this) - (r - (*this)) * factor;
}

std::string FColor::ToString() const
{
	return "R: " + std::to_string(R) + " "
		+  "G: " + std::to_string(G) + " "
		+  "B: " + std::to_string(B) + " "
		+  "A: " + std::to_string(A);
}