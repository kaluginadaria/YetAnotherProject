#pragma once
#ifndef COIN_HPP
#define COIN_HPP

#include "Actor.hpp"
#include "BoxColision.hpp"


class Coin : public Actor
{
	GENERATED_BODY(Coin, Actor);

public:
	Coin()
	{
		body = CreateSubcomponent<BoxColision>("Body");
		body->SetExtends(FVector(0.5f, 0.5f, 0.6f));
		body->GetRigidBody()->SetMass(1);
	}

protected:
	BoxColision* body;
};


#endif // !COIN_HPP
