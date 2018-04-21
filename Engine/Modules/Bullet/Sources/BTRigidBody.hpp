#ifndef BTRIGID_BODY_HPP
#define BTRIGID_BODY_HPP

#include "Interfaces/Default/RigidBody.hpp"

#include "BTConvertion.hpp"
#include "btBulletDynamicsCommon.h"


struct RigidBody : public FRigidBody
{
public:
	RigidBody(FShape shape, ActorComponent* owner, float mass, FVector inertia);
	~RigidBody();

	virtual void Update() override;
	virtual void Sync()   override;

public:
	virtual void AddForce          (const FVector& force  ) override;
	virtual void AddTorque         (const FVector& torque ) override;
	virtual void AddImpulce        (const FVector& impulce) override;
	virtual void AddKineticMomement(const FVector& moment ) override;

public:
	virtual void    SetMass    (float newMass     )       override;
	virtual void    SetInertia (FVector newInertia)       override;
	virtual float   GetMass    ()                   const override;
	virtual FVector GetInertia ()                   const override;
	
	virtual void SetExtents(FVector newExtents) override;

private:
	btVector3 CalculateIniertia(float mass, FVector inertia);

	void SyncWithScene();

public:
	UNIQUE(btCollisionShape)     collision;
	UNIQUE(btDefaultMotionState) motionState;
	UNIQUE(btRigidBody)	         rigidBody;
};



#endif // !BTRIGID_BODY_HPP
