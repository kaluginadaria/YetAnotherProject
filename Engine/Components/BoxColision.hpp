#pragma once


#include "../Core/ActorComponent.hpp"

class BoxColision : public ActorComponent
{
	GENERATED_BODY(BoxColision, ActorComponent);
public:

	BoxColision();

public:

	Vector3f GetExtends() const	{ return extends; }
	void SetExtends(Vector3f newExtends);

protected:

	/// >> 
	Vector3f extends;
	///
};