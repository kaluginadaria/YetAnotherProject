#ifndef COLOR_HPP
#define COLOR_HPP

#include <assert.h>
#include <string>


struct FColor
{
public:

	float R;
	float G;
	float B;
	float A;

public:

	FColor(float R = 0, float G = 0, float B = 0, float A = 0)
		: R(R), G(G), B(B), A(A)
	{}

	FColor(const FColor& r)
		: R(r.R), G(r.G), B(r.B), A(r.A)
	{}
	
	bool operator=(const FColor& r)
	{
		R = r.R;
		G = r.G;
		B = r.B;
		A = r.A;
	}

	float& operator[](int i)
	{
		assert(i >= 0 && i < 4);
		switch (i)
		{
		case 0: return R;
		case 1: return G;
		case 2: return B;
		case 3: return A;
		}
	}

	float operator[](int i) const
	{
		assert(i >= 0 && i < 4);
		switch (i)
		{
		case 0: return R;
		case 1: return G;
		case 2: return B;
		case 3: return A;
		}
	}

public: //~~~~~~~~~~~~~~| color - color

	FColor operator+(const FColor& r) const
	{
		return FColor(
			R + r.R,
			G + r.G,
			B + r.B,
			A + r.A);
	}

	FColor operator-(const FColor& r) const
	{
		return FColor(
			R - r.R,
			G - r.G,
			B - r.B,
			A - r.A);
	}

	FColor& operator-=(FColor r)
	{
		R -= r.R;
		G -= r.G;
		B -= r.B;
		A -= r.A;
		return *this;
	}

	FColor& operator+=(FColor r)
	{
		R += r.A;
		G += r.G;
		B += r.B;
		A += r.A;
		return *this;
	}

public: //~~~~~~~~~~~~~~| color - scalar

	FColor operator+(float r)
	{
		return FColor(
			R + r,
			G + r,
			B + r,
			A + r);
	}

	FColor operator-(float r)
	{
		return FColor(
			R - r,
			G - r,
			B - r,
			A - r);
	}

	FColor operator*(float r)
	{
		return FColor(
			R * r,
			G * r,
			B * r,
			A * r);
	}

	FColor operator/(float r)
	{
		return FColor(
			R / r,
			G / r,
			B / r,
			A / r);
	}

	// ?=

	FColor& operator+=(float r)
	{
		R += r;
		G += r;
		B += r;
		A += r;
		return *this;
	}

	FColor& operator-=(float r)
	{
		R -= r;
		G -= r;
		B -= r;
		A -= r;
		return *this;
	}

	FColor& operator*=(float r)
	{
		R *= r;
		G *= r;
		B *= r;
		A *= r;
		return *this;
	}

	FColor& operator/=(float r)
	{
		R /= r;
		G /= r;
		B /= r;
		A /= r;
		return *this;
	}

public: //~~~~~~~~~~~~~~| equation

	bool operator==(const FColor& r) const
	{
		return R == r.R
			&& G == r.G
			&& B == r.B
			&& A == r.A;
	}

	bool operator!=(const FColor& r) const
	{
		return !(*this == r);
	}

public: //~~~~~~~~~~~~~~| misc

	FColor Lerp(const FColor& r, float factor)
	{
		return (*this) - (r - (*this)) * factor;
	}

	std::string ToString() const
	{
		return "R: " + std::to_string(R) + " "
			+  "G: " + std::to_string(G) + " "
			+  "B: " + std::to_string(B) + " "
			+  "A: " + std::to_string(A);
	}

public: //~~~~~~~~~~~~~~| constants

	static const FColor Red;
	static const FColor Green;
	static const FColor Blue;
};




// constants
const FColor FColor::Red   = FColor(1, 0, 0);
const FColor FColor::Green = FColor(0, 1, 0);
const FColor FColor::Blue  = FColor(0, 0, 1);



#endif //!COLOR_HPP