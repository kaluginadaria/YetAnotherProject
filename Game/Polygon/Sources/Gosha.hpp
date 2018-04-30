#pragma once
#ifndef GOSHA_HPP
#define GOSHA_HPP

#include "Avatar.hpp"
#include "BoxColision.hpp"
#include "CameraComponent.hpp"
#include "MovementComponent.hpp"
#include "PlayerController.hpp"


class Gosha : public Avatar
{
	GENERATED_BODY(Gosha, Avatar);

public:
	Gosha();

	virtual void OnBeginPlay() override;

	void SetupInput(EventBinder* binder);

protected:
	void Move(float value);
	void Jump(EKeyAction);

protected:
	BoxColision* body;
	CameraComponent* camera;
	MovementComponent* movement;

};


#endif // !GOSHA_HPP
