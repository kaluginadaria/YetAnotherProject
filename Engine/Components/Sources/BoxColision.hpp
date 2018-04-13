#pragma once


#include "ActorComponent.hpp"

class BoxColision : public ActorComponent
{
	GENERATED_BODY(BoxColision, ActorComponent);
public:

	BoxColision();

public:

	FVector GetExtends() const	
	{ 
		return extends; 
	}

	void SetExtends(FVector newExtends);

protected:

	/// >> 
	FVector extends;
	///
};