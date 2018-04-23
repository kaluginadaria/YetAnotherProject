#pragma once
#ifndef BTCONSTRAINT_HPP
#define BTCONSTRAINT_HPP

#include <unordered_map>
#include <btBulletDynamicsCommon.h>
#include "Interfaces/Default/Constraint.hpp"

#include "BTRigidBody.hpp"
#include "BTConvertion.hpp"

class Constraint : public FConstraint
{
public: 
	Constraint(ActorComponent* owner);

	btTransform GetTransform() const;

public:
	virtual void AddChild    (IRigidBody* ibody) override;
	virtual void SetParent   (IRigidBody* ibody) override;

	virtual void RemoveChild (IRigidBody* ibody) override;
	virtual void RemoveParent(IRigidBody* ibody) override;

	virtual void UpdateConstraint() override;            
	virtual void UpdateChild(IRigidBody* ibody) override;

public:
	virtual void SetContraints(FConstraintType& newConstraints);

private:
	void UpdateConstraint(btPoint2PointConstraint& target);
	btPoint2PointConstraint* GetConstraint(RigidBody* child);

	//UNIQUE(btGeneric6DofConstraint) MakeConstraint(RigidBody* parent, RigidBody* child);
	UNIQUE(btPoint2PointConstraint) MakeConstraint(RigidBody* parent, RigidBody* child);

private:
	RigidBody* parent;
	std::unordered_map<RigidBody*, UNIQUE(btPoint2PointConstraint)> childConstraints;
};



#endif // !BTCONSTRAINT_HPP
