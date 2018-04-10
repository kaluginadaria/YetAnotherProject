#pragma once

#include "Avatar.hpp"
#include "BoxColision.hpp"
#include "CameraComponent.hpp"
#include "Control/EventBinder.hpp"
#include "PID.hpp"


class Pendulum : public Avatar
{
	GENERATED_BODY(Pendulum, Avatar);
public:

	Pendulum()
		: pid(4, 0, 20)
	{
		base = CreateSubComponent<BoxColision>("Base");
		base->SetExtends({0.6f, 0.6f, 0.6f});
		
		pendulum = CreateSubComponent<BoxColision>("Pendulum");
		pendulum->AddComponentLocation({2, 0, 0}, eParent);
		pendulum->SetExtends({2, 0.2f, 0.2f});
		
		target = CreateSubComponent<BoxColision>("Target");
		target->AddComponentLocation({5, 0 , 0}, eParent);
		target->AddComponentRotation({0 ,90, 0}, eParent);
		target->SetExtends({0.5f, 0.1f, 0.1f});

		cam = CreateSubComponent<CameraComponent>("Camera");
		cam->AddComponentLocation({-30, 0, 0}, eParent);
		cam->AddComponentRotation({ 0, 0 ,90}, eParent);
		cam->SetAutoregister(true);
	}

	virtual void Tick(float DeltaTime, ETickType type)
	{
		dt = DeltaTime;

		if (!DeltaTime) return;

		auto tr = target  ->GetComponentRotation();
		auto cr = pendulum->GetComponentRotation();
		auto delta = ~cr * tr;

		const float control = pid.GetValue(delta.v.y, dt);
		const float inertia = 600;
		const float M0      = 100;

		const float M  = M0 * control;
		const float dw = (float)RAD2DEG(M / inertia * dt);
		w += dw;

		pendulum->AddComponentRotation({0, w * dt, 0}, eParent);
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
			cam->AddComponentRotation({0, 0, delta}, eParent);
		}
	}

	void Cam_2(float value)
	{
		if (value && cam)
		{
			float delta = 40 * value * dt;
			cam->AddComponentRotation({delta, 0, 0}, eParent);
		}
	}

	void MoveTarget(float value)
	{
		if (value && target)
		{
			float delta = 40 * value * dt;
			target->AddComponentRotation({0, delta, 0}, eParent);
		}
	}

protected:


protected:

	BoxColision* base		= nullptr;
	BoxColision* pendulum	= nullptr;
	BoxColision* target		= nullptr;
	CameraComponent* cam	= nullptr;

	float dt = 0;
	float w  = 0;

	PID pid;
};