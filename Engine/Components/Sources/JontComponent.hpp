#pragma once
#ifndef JOINT_COMPONENT_HPP
#define JOINT_COMPONENT_HPP

#include "ActorComponent.hpp"
#include "Interfaces/IConstraint.hpp"


class JointComponent : public ActorComponent
{
	GENERATED_BODY(JointComponent, ActorComponent);

public:
	JointComponent();

public:
	FConstraintType GetConstraint();
	void SetConstraint(FConstraintType type);

protected:
	virtual void OnSubcomponentAttached(ActorComponent* child ) override;
	virtual void OnSubcomponentDetached(ActorComponent* child ) override;
	virtual void OnComponentAttached   (ActorComponent* parent) override;
	virtual void OnComponentDetached   (ActorComponent* parent) override;
	virtual void onSubcomponentMoved   (ActorComponent* child, bool bUpdateBody) override;
	virtual void onComponentMoved      (bool bUpdateBody) override;

protected:
	UNIQUE(IConstraint) constraint;
	FConstraintType constraintType;	
};


#endif // !JOINT_COMPONENT_HPP
