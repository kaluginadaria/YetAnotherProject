#include "BaseCollision.hpp"
#include "Modules/ModuleManager.hpp"

BaseCollision::BaseCollision(EShapeType shape)
	: extends(1, 1, 1)
{
	rigidBody.reset(
		ModuleManager::MakeBody(FShape(shape, extends), this, 10)
		);
}

FVector BaseCollision::GetExtends() const
{
	return extends;
}

void BaseCollision::SetExtends(FVector newExtends)
{
	extends = newExtends;
	if (rigidBody)
	{
		rigidBody->SetExtents(extends);
	}
}
