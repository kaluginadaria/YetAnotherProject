#include "ActorComponent.hpp"

#include "Avatar.hpp"
#include "Modules/ModuleManager.hpp"

ActorComponent::ActorComponent()
	: owner(ThreadContext::TopInitialiser()->owner)
	, parent(nullptr)

	, relativeTarnsform(Transform::getIdentity())
	, worldTransform   (Transform::getIdentity())
	
	, facade(ModuleManager::MakeFacade(this))
{}

void ActorComponent::AddForce(const Vector3f& force, ESpaceType space)
{
	//TODO:
}

void ActorComponent::AddTorque(const Vector3f& torue, ESpaceType space)
{
	//TODO:
}

void ActorComponent::SetComponentTransform(Transform newTransform)
{
	worldTransform = newTransform;
	UpdateRelativeTransform();
}

void ActorComponent::SetRelativeTransform(Transform newTransform)
{
	relativeTarnsform = newTransform;
	UpdateWoldTransform();
}

void ActorComponent::SetComponentLocation(Vector3f newLocation)
{
	worldTransform.origin = newLocation;
	UpdateRelativeTransform();
}

void ActorComponent::SetRelativeLocation(Vector3f newLocation)
{
	relativeTarnsform.origin = newLocation;
	UpdateWoldTransform();
}

void ActorComponent::SetComponentRotation(Quatf newRotation)
{
	worldTransform.rotation = newRotation;
	UpdateRelativeTransform();
}

void ActorComponent::SetRelativeRotation(Quatf newRotation)
{
	relativeTarnsform.rotation = newRotation;
	UpdateWoldTransform();
}

void ActorComponent::AddTransform(Transform delta, ESpaceType space)
{	
	if (space == ESpaceType::eLocal)
	{
		relativeTarnsform += delta;
		UpdateWoldTransform();
		return;
	}
	if (space == ESpaceType::eWorld)
	{
		worldTransform += delta;
		UpdateRelativeTransform();
		return;
	}
	if (space == ESpaceType::eParent)
	{
		relativeTarnsform = delta * relativeTarnsform;
		UpdateWoldTransform();
		return;
	}
	assert(false);
}

void ActorComponent::AddComponentLocation(Vector3f delta, ESpaceType space)
{
	AddTransform(Transform(delta), space);
}

void ActorComponent::AddComponentRotation(Quatf delta, ESpaceType space)
{
	AddTransform(Transform(delta), space);
}

const PlayerController* ActorComponent::GetPlayerController() const
{
	auto*  avatar = dynamic_cast<Avatar*>(owner);
	return avatar ? avatar->GetPlayerController() : nullptr;
}

PlayerController* ActorComponent::GetPlayerController()
{
	auto*  avatar = dynamic_cast<Avatar*>(owner);
	return avatar ? avatar->GetPlayerController() : nullptr;
}

void ActorComponent::AttachTo(ActorComponent* newParent)
{
	if (!world) return;

	if (!newParent) {
		newParent = world->GetSceneRoot();
	}
	Detach();

	parent = newParent;
	parent->subcomponents.emplace_back(this);

	facade->AttachTo(newParent->GetFacade());
}

void ActorComponent::Detach()
{
	if (parent)	
	{
		auto pos = parent->subcomponents.begin();
		auto end = parent->subcomponents.end();

		for (; pos != end; ++pos)
		{
			if (*pos == this)
			{
				parent->subcomponents.erase(pos);
				break;
			}
		}
		parent = world->GetSceneRoot(); //TODO

		facade->Detach();
	}
}

std::vector<ActorComponent*>& ActorComponent::GetSubcomponents()
{
	return subcomponents;
	// std::vector<ActorComponent*> components;
	// Internal_GetSubcomponents(components);
	// return components;
}

const std::vector<ActorComponent*>& ActorComponent::GetSubcomponents() const
{
	return subcomponents;
	// std::vector<const ActorComponent*> components;
	// Internal_GetSubcomponents(components);
	// return components;
}

void ActorComponent::Internal_GetSubcomponents(std::vector<ActorComponent*>& components)
{
	for (auto comp : subcomponents)
	{
		if (!IsValid(comp))			continue;
		if (comp->owner != owner)	continue;

		components.emplace_back(comp);

		comp->Internal_GetSubcomponents(components);
	}
}

void ActorComponent::Internal_GetSubcomponents(std::vector<const ActorComponent*>& components) const
{
	for (auto comp : subcomponents)
	{
		if (!IsValid(comp))			continue;
		if (comp->owner != owner)	continue;

		components.emplace_back(comp);

		comp->Internal_GetSubcomponents(components);
	}
}

void ActorComponent::UpdateFacade()
{
	if (facade)
	{
		facade->Update();
	}
}

void ActorComponent::UpdateWoldTransform()
{
	Transform P = GetParentTransform();
	Transform R = GetRelativeTransform();
	worldTransform = P * R;
	UpdateChainTransforms();
}

void ActorComponent::UpdateRelativeTransform()
{
	Transform P = GetParentTransform();
	Transform W = GetComponentTransform();
	relativeTarnsform = ~P * W;
	UpdateChainTransforms();
}

void ActorComponent::UpdateChainTransforms()
{
	UpdateFacade();
	
	for (auto child : subcomponents)
	{
		if (IsValid(child))
		{
			child->UpdateWoldTransform();
		}
	}
}

Transform ActorComponent::GetParentTransform() const
{
	return parent ? parent->GetComponentTransform() : Transform::getIdentity();
}
