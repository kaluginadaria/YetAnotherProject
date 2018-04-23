#include "BTRigidBody.hpp"
#include "BTPhysicsScene.hpp"
#include "ActorComponent.hpp"

RigidBody::RigidBody(FShape shape, ActorComponent* owner, float mass, FVector inertia)
	: FRigidBody(owner)
{
	assert(owner);

	// colision
	btCollisionShape* newShape = nullptr;
	btVector3 newExtents = btVector3() << shape.extends;
	switch (shape.type) {
	case EShapeType::eBox: newShape = new btBoxShape(newExtents);
	}
	collision.reset(newShape);
	
	// moution
	FTransform  transform = owner->GetComponentTransform();
	btTransform newTransform = btTransform() << transform;
	motionState.reset(
		new btDefaultMotionState(newTransform)
		);

	// rigid body
	rigidBody.reset(
		new btRigidBody( mass ,
			motionState.get(),
			collision  .get(),
			CalculateIniertia(mass, inertia)
			)
		);

	if (auto* scene = GetPhysicsScene<PhysicsScene>())
	{
		scene->RegisterBody(this);
	}
}

RigidBody::~RigidBody()
{
	if (auto* scene = GetPhysicsScene<PhysicsScene>())
	{
		scene->UnregisterBody(this);
	}
}

void RigidBody::Update()
{
	if (owner && rigidBody)
	{
		FTransform  transform = owner->GetComponentTransform();
		btTransform newTransform = btTransform() << transform;
		rigidBody->setWorldTransform(newTransform);
		
		SyncWithScene();
	}
}

void RigidBody::Sync()
{
	if (owner && motionState && bDynamic)
	{
		btTransform transform; 
		FTransform newTransform;
		motionState->getWorldTransform(transform);
		newTransform << transform;
		owner->SetComponentTransform(newTransform, true, false);
	}
}

bool RigidBody::IsValid() const
{
	return collision 
		&& motionState 
		&& rigidBody;
}

btTransform RigidBody::GetTransform() const
{
	if (owner)
	{
		FTransform transform = owner->GetComponentTransform();
		btTransform newTransform = btTransform() << transform;
		return newTransform;
	}
	return btTransform();
}

void RigidBody::AddForce(const FVector& force)
{
	if (rigidBody && motionState)
	{
		btTransform center;
		motionState->getWorldTransform(center);
		btVector3 impact = btVector3() << force;
		rigidBody->applyForce(impact, center.getOrigin());
	}
}

void RigidBody::AddTorque(const FVector& torque)
{
	if (rigidBody && motionState)
	{
		btVector3 impact = btVector3() << torque;
		rigidBody->applyTorque(impact);
	}
}

void RigidBody::AddImpulce(const FVector& impulce)
{
	if (rigidBody && motionState)
	{
		btTransform center;
		motionState->getWorldTransform(center);
		btVector3 impact = btVector3() << impulce;
		rigidBody->applyImpulse(impact, center.getOrigin());
	}
}

void RigidBody::AddKineticMomement(const FVector& moment)
{
	if (rigidBody && motionState)
	{
		btVector3 impact = btVector3() << moment;
		rigidBody->applyTorqueImpulse(impact);
	}
}

void RigidBody::SetMass(float newMass)
{
	if (rigidBody && collision)
	{
		if (newMass)
		{
			bDynamic = true;
			btVector3 inertia;
			collision->calculateLocalInertia(newMass, inertia);
			rigidBody->setMassProps(newMass, inertia);
		}
		else
		{
			bDynamic = false;
			btVector3 inertia;
			inertia.setZero();
			rigidBody->setMassProps(0, inertia);
		}
		SyncWithScene();
	}
}

void RigidBody::SetInertia(FVector newInertia)
{
	if (rigidBody)
	{
		btVector3 inertia = btVector3() << newInertia;
		btScalar  mass    = rigidBody->getInvMass();
		rigidBody->setMassProps(mass, inertia);

		bDynamic = newInertia != FVector::ZeroVector && mass;
		
		SyncWithScene();
	}
}

float RigidBody::GetMass() const
{
	if (rigidBody)
	{
		return rigidBody->getInvMass();
	}
	return 0;
}

FVector RigidBody::GetInertia() const
{
	if (rigidBody)
	{
		btVector3 inertia = rigidBody->getLocalInertia();
		return FVector() << inertia;
	}
	return FVector::ZeroVector;
}

void RigidBody::SetExtents(FVector newExtents)
{
	if (auto* shape = (btPolyhedralConvexShape*)(collision.get())) // TODO:: fix a dynamic_cast error
	{
		btVector3 extents = btVector3() << newExtents;
		shape->setImplicitShapeDimensions(extents);
		SyncWithScene();
	}
}

btVector3 RigidBody::CalculateIniertia(float mass, FVector inertia)
{
	if (!mass) 
	{
		bDynamic = false;
		return btVector3(0,0,0);
	}
	if (inertia != FVector::ZeroVector)
	{
		return btVector3() << inertia;
	}
	if (collision)
	{
		btVector3 newInertia;
		collision->calculateLocalInertia(mass, newInertia);
		return newInertia;
	}
	return btVector3(0,0,0);
}

void RigidBody::SyncWithScene()
{
	if (auto* scene = GetPhysicsScene<PhysicsScene>())
	{
		scene->SyncBody(this);
	}
}
