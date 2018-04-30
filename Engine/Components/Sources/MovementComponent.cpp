#include "MovementComponent.hpp"


MovementComponent::MovementComponent()
	: updatedComponent(nullptr)
{
	prePhysicsTick.BindFunction(this, &MovementComponent::PrePhysicsTick);
	prePhysicsTick.tickType = ETickType::ePrePhysics;

	postPhysicsTick.BindFunction(this, &MovementComponent::PostPhysicsTick);
	postPhysicsTick.tickType = ETickType::ePostPhysics;
}

void MovementComponent::OnConstructed()
{
	Super::OnConstructed();
	RegisterTick(prePhysicsTick );
	RegisterTick(postPhysicsTick);
}

void MovementComponent::OnEndPlay()
{
	Super::OnEndPlay();
	UnregisterTick(prePhysicsTick );
	UnregisterTick(postPhysicsTick);
}

void MovementComponent::PrePhysicsTick(float DeltaTime, ETickType type)
{
	if (states.flags.bUseStabilisation) 
	{
		stabilisation.Stabilisate(DeltaTime);
	}

	if (updatedComponent)
	{
		switch (states.CurrentMode().ImpactType)
		{
		case EMovementImpactType::Force:
		case EMovementImpactType::Acceleration:
			updatedComponent->AddForce (GetResultForce() , ESpaceType::eLocal);
			updatedComponent->AddTorque(GetResultTorque(), ESpaceType::eLocal);
			break;
		case EMovementImpactType::Impulce:
			updatedComponent->AddImpulce        (GetResultImpulce()       , ESpaceType::eLocal);
			updatedComponent->AddKineticMomement(GetResultAngularImpulce(), ESpaceType::eLocal);
			break;
		default:
			throw std::out_of_range("ImpactType has unsupported value");
		}
	}
}

void MovementComponent::PostPhysicsTick(float DeltaTime, ETickType type)
{
	states.NextFrame(DeltaTime);    /// Here we start new frame
	AbsorbTelemetry();              /// Take a telemetry
	states.UpdateStates(DeltaTime); /// Update accelerations
}

void MovementComponent::SetTrackingComponent(ActorComponent* target)
{
	updatedComponent = target;
	stabilisation.SetTarget(target);
}

void MovementComponent::AddLenearInput   (FVector WorldVector, ESpaceType space) { AddState(WorldVector, states.LinearInput()     , space); }
void MovementComponent::AddAngularInput  (FVector WorldVector, ESpaceType space) { AddState(WorldVector, states.AngularInput()    , space); }
void MovementComponent::RegisterExternalForce (FVector Force , ESpaceType space) { AddState(Force,       states.RegisteredForce() , space); }
void MovementComponent::RegisterExternalTorque(FVector Torque, ESpaceType space) { AddState(Torque,      states.RegisteredTorque(), space); }

void MovementComponent::AddState(const FVector& Value, FVector& Target, ESpaceType space) const
{
	if(updatedComponent)
	{
		Target += updatedComponent->SpaceToLocal(Value, space);
	}
}

FVector MovementComponent::GetResultForce() const
{
	if (updatedComponent)
	{
		switch (states.CurrentMode().ImpactType)
		{
		case EMovementImpactType::Acceleration:        
			return states.LinearInput() 
				 * states.NormalAcceleration() 
				 * updatedComponent->GetMass();
		case EMovementImpactType::Force: 
			return states.LinearInput() 
				 * states.CurrentMode().Force;
		}
	}
	return FVector::ZeroVector;
}

FVector MovementComponent::GetResultTorque() const
{
	if (updatedComponent)
	{
		switch (states.CurrentMode().ImpactType)
		{
		case EMovementImpactType::Acceleration:        
			return states.AngularInput() 
				 * states.NormalEpsilon() 
				 * updatedComponent->GetInertia();
		case EMovementImpactType::Force: 
			return states.AngularInput() 
				 * states.CurrentMode().Torque;
		}
	}
	return FVector::ZeroVector;
}

FVector MovementComponent::GetResultImpulce() const
{
	return states.LinearInput()
		 * states.CurrentMode().Impulce;
}

FVector MovementComponent::GetResultAngularImpulce() const
{
	return states.AngularInput()
		 * states.CurrentMode().AngularImpulce;
}

void MovementComponent::AbsorbTelemetry()
{
	if (auto* t = updatedComponent)
	{
		states.Transform()	= t->GetComponentTransform();
		states.Velocity()	= t->SpaceToLocal(t->GetVelocity(), ESpaceType::eWorld);
		states.Omega()		= t->SpaceToLocal(t->GetOmega()   , ESpaceType::eWorld);
	}
}
