#include "Gosha.hpp"
#include "Coin.hpp"

Gosha::Gosha()
{
	body = CreateSubcomponent<BoxColision>("Body");
	body->SetExtends(FVector(1, 2, 0.6f));
	body->GetRigidBody()->SetMass(10);
	
	movement = CreateSubModule<MovementComponent>("Movement");
	
	movement->states.movementMode = EMovementMode::Jumping;
	movement->states.CurrentMode().ImpactType = EMovementImpactType::Impulce;
	movement->states.CurrentMode().Impulce = FVector(0, 200);
	movement->SetTrackingComponent(body);

	movement->states.movementMode = EMovementMode::Walk;
	movement->states.CurrentMode().ImpactType = EMovementImpactType::Acceleration;
	movement->states.CurrentMode().Acceleration = FVector(30);
	movement->SetTrackingComponent(body);

	camera = CreateSubcomponent<CameraComponent>("Camera");
	camera->AddComponentLocation(FVector(0, 0, 80), eParent);
	camera->AddComponentRotation(FQuat  (0, 90, 0), eLocal );
	camera->SetAutoregister(true);
}

void Gosha::OnBeginPlay()
{
	if (body)
	{
		body->OnCollisionEnter.Bind(this, [&](Actor* other, ActorComponent*, FHit)
		{
			if (auto* coin = dynamic_cast<Coin*>(other))
			{
				coin->AttachTo(this);
				coin->GetRootComponent()->SetMass(0);
				coin->SetRelativeLocation(FVector(2));
			}
		});
	}
}

void Gosha::SetupInput(EventBinder* binder)
{
	Super::SetupInput(binder);
	binder->BindAxis("Fwd", this, &Gosha::Move);
	binder->BindAction("Jump", BA_Pressed, this, &Gosha::Jump);
}

void Gosha::Move(float value)
{
	if (movement && value)
	{
		movement->AddLenearInput(FVector(value));
	}
}

void Gosha::Jump(EKeyAction)
{
	if (movement)
	{
		movement->states.extraMode = EMovementMode::Jumping;
		movement->AddLenearInput(FVector(0, 1));
	}
}
