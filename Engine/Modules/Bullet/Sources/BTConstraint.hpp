#pragma once
#ifndef BTCONSTRAINT_HPP
#define BTCONSTRAINT_HPP

#include "Interfaces/Default/Constraint.hpp"
#include "ActorComponent.hpp"


class Constraint : public FConstraint
{
public: 
	Constraint(ActorComponent* owner);



};



#endif // !BTCONSTRAINT_HPP
