#pragma once

#include "Avatar.hpp"
#include "BoxColision.hpp"
#include "JontComponent.hpp"
#include "CameraComponent.hpp"
#include "Control/EventBinder.hpp"
#include "PID.hpp"

#include <iostream>


class Pendulum : public Avatar
{
	GENERATED_BODY(Pendulum, Avatar);
public:

	Pendulum()
		: pid(4, 0.1f, 20)
	{
		base = CreateSubComponent<BoxColision>("Base");
		base->SetExtends(FVector(0.6f, 0.6f, 0.6f));
		base->GetRigidBody()->SetMass(0);

		floor = CreateSubComponent<BoxColision>("floor");
		floor->AddComponentLocation(FVector(0,0,-7));
		floor->SetExtends(FVector(5,5,0.1f));
		floor->GetRigidBody()->SetMass(0);

		joint = CreateSubComponent<JointComponent>("joint");
		joint->SetConstraint(FConstraintType::MakeRotation(ePitch));
		joint->AttachTo(base);
		
		pendulum = CreateSubComponent<BoxColision>("Pendulum");
		pendulum->AddComponentLocation(FVector(3, 0, 0), eParent);
		pendulum->SetExtends(FVector(1.5f, 0.2f, 0.2f));
		pendulum->GetRigidBody()->SetMass(10);
		pendulum->AttachTo(joint);
		
		target = CreateSubComponent<BoxColision>("Target");
		target->AddComponentLocation(FVector(6, 0 , 0), eParent);
		target->AddComponentRotation(FQuat(0 ,90, 0), eParent);
		target->SetExtends(FVector(0.5f, 0.1f, 0.1f));
		target->GetRigidBody()->SetMass(0);
		target->AttachTo(joint);
		
		cam = CreateSubComponent<CameraComponent>("Camera");
		cam->AddComponentLocation(FVector(-40, 0, 0), eParent);
		cam->AddComponentRotation(FQuat( 0, 0 ,90), eParent);
		cam->SetAutoregister(true);
	}

	virtual void Tick(float DeltaTime, ETickType type)
	{
		Super::Tick(DeltaTime, type);

		dt = DeltaTime;
		// if (!DeltaTime) return;

		// auto tr = target  ->GetComponentRotation();
		// auto cr = pendulum->GetComponentRotation();
		// auto delta = ~cr * tr;
		// 
		// const float control = pid.GetValue(delta.Y, dt);
		// const float inertia = 600;
		// const float M0      = 100;
		// const float M = M0 * control;
		// std::cout << M << std::endl;
		
		// pendulum->AddTorque(FVector(0, M, 0), eParent);
	}

	virtual void SetupInput(EventBinder* binder)
	{
		Super::SetupInput(binder);
		binder->BindAxis("Bvd", this, &Pendulum::Cam_1);
		binder->BindAxis("Fvd", this, &Pendulum::Cam_2);
		binder->BindAxis("R1", this, &Pendulum::MoveTarget);
	}

protected:

	void Cam_1(float value)
	{
		if (value && cam)
		{
			float delta = 40 * value * dt;
			cam->AddComponentRotation(FQuat(0, 0, delta), eParent);
		}
	}

	void Cam_2(float value)
	{
		if (value && cam)
		{
			float delta = 40 * value * dt;
			cam->AddComponentRotation(FQuat(delta, 0, 0), eParent);
		}
	}

	void MoveTarget(float value)
	{
		if (value && target)
		{
			float delta = 40 * value * dt;
			target->AddComponentRotation(FQuat(0,    delta, 0), eParent);
			target->AddComponentRotation(FQuat(0, -2*delta, 0), eParent);
		}
	}

protected:


protected:

	BoxColision*	 base		= nullptr;
	BoxColision*	 floor		= nullptr;
	BoxColision*	 pendulum	= nullptr;
	BoxColision*	 target		= nullptr;
	JointComponent*	 joint		= nullptr;
	CameraComponent* cam		= nullptr;

	float dt = 0;
	float w  = 0;

	PID pid;
};

// convare