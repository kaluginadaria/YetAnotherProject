#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <string>


struct FVector
{
public:
	float X;
	float Y;
	float Z;

public:

	FVector(float X = 0, float Y = 0, float Z = 0);
	FVector(const FVector& r);

	FVector& operator=(const FVector& r);

	float& operator[](int i);
	float  operator[](int i) const;

public: //~~~~~~~~~~~~~~| vector - vector

	FVector operator+(const FVector& r) const;
	FVector operator-(const FVector& r) const;
	FVector operator*(const FVector& r) const;
	FVector operator/(const FVector& r) const;
	FVector operator^(const FVector& r) const;

	// ?=

	FVector& operator-=(const FVector& r);
	FVector& operator+=(const FVector& r);
	FVector& operator*=(const FVector& r);
	FVector& operator/=(const FVector& r);
	FVector& operator^=(const FVector& r);

public: //~~~~~~~~~~~~~~| vector - scalar

	FVector operator+(float r);
	FVector operator-(float r);
	FVector operator*(float r);
	FVector operator/(float r);

	// ?=

	FVector& operator+=(float r);
	FVector& operator-=(float r);
	FVector& operator*=(float r);
	FVector& operator/=(float r);

public: //~~~~~~~~~~~~~~| unary

	FVector operator-() const;

public: //~~~~~~~~~~~~~~| equation

	bool operator==(const FVector& r) const;
	bool operator!=(const FVector& r) const;

public: //~~~~~~~~~~~~~~| size

	float Size  () const;
	float SizeSq() const;

	FVector  GetNormal() const;
	FVector& Normalise();

public: //~~~~~~~~~~~~~~| misc

	FVector Lerp(const FVector& r, float factor);

	std::string ToString() const;

public: //~~~~~~~~~~~~~~| constants

	static const FVector ZeroVector;

	static const FVector Forward;
	static const FVector Backward;
	
	static const FVector Upward;
	static const FVector Downward;
	
	static const FVector Leftward;
	static const FVector Rightward;
};

#endif //!VECTOR_HPP