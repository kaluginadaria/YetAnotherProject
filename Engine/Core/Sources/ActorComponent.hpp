#ifndef ACTOR_COMPONENT_HPP
#define ACTOR_COMPONENT_HPP
#pragma once

#include <string>
#include <vector>

#include "Object.hpp"
#include "Interfaces/IFacade.hpp"
#include "Interfaces/IRigidBody.hpp"

class Actor;
class World;
class PlayerController;
struct IRigidBody;

/** All object components in the world makes a backet tree (NODE: Actor is a kind of wrapper on components)
 *	Each Component have:
 *	. realtive transform 
 *	. absolute transform
 *	
 *	. subcomponent	- child nodes probably dependesce from the one
 *	. parent		- a parent node
 *	. owner			- an objects associated with the component
 *	. world			- a world where the component is placed
 */
class ActorComponent : public Object
{
	GENERATED_BODY(ActorComponent, Object)
public:

	ActorComponent();

public: //~~~~~~~~~~~~~~| Physics

	void AddForce          (const FVector& force,   ESpaceType space);
	void AddTorque         (const FVector& torque,  ESpaceType space);
	void AddImpulce        (const FVector& impulce, ESpaceType space);
	void AddKineticMomement(const FVector& moment,  ESpaceType space);

public: //~~~~~~~~~~~~~~| Position
	/** NOTE:
	 * @param bExcludePhysics - if true child dynamic object won't be updated
	 * @param bUpdateBody     - if true - update a rigid body with
	 */

	/// transform

	void SetComponentTransform(FTransform newTransform, bool bExcludePhysics = false, bool bUpdateBody = true);
	void SetRelativeTransform (FTransform newTransform, bool bExcludePhysics = false, bool bUpdateBody = true);
	FTransform GetComponentTransform() const { return worldTransform;    }
	FTransform GetRelativeTransform () const { return relativeTarnsform; }

	/// location

	void SetComponentLocation(FVector newLocation, bool bExcludePhysics = false, bool bUpdateBody = true);
	void SetRelativeLocation (FVector newLocation, bool bExcludePhysics = false, bool bUpdateBody = true);
	FVector  GetComponentLocation() const { return worldTransform   .Location; }
	FVector  GetRelativeLocation () const { return relativeTarnsform.Location; }

	/// rotation

	void SetComponentRotation(FQuat newRotation, bool bExcludePhysics = false, bool bUpdateBody = true);
	void SetRelativeRotation (FQuat newRotation, bool bExcludePhysics = false, bool bUpdateBody = true);
	FQuat GetComponentRotation() const { return worldTransform   .Rotation; }
	FQuat GetRelativeRotation () const { return relativeTarnsform.Rotation; }

	/// add

	void AddTransform		 (FTransform delta, ESpaceType space = ESpaceType::eWorld, bool bExcludePhysics = false, bool bUpdateBody = true);
	void AddComponentLocation(FVector	 delta, ESpaceType space = ESpaceType::eWorld, bool bExcludePhysics = false, bool bUpdateBody = true);
	void AddComponentRotation(FQuat      delta, ESpaceType space = ESpaceType::eWorld, bool bExcludePhysics = false, bool bUpdateBody = true);

public: //~~~~~~~~~~~~~~| Chain

	/// owner

	const Actor* GetOwner() const	{ return owner; }
		  Actor* GetOwner()			{ return owner; }
	void SetOwner(Actor* newOwner)	{ owner = newOwner; }

	/// if owner is Avatar

	const PlayerController* GetPlayerController() const;
		  PlayerController* GetPlayerController();
	
	void AttachTo(ActorComponent* newParent);
	void Detach();

	/// facade

          IFacade* GetFacade()		 { return facade.get(); }
	const IFacade* GetFacade() const { return facade.get(); }

	/// rigid body

		  IRigidBody* GetRigidBody()       { return rigidBody.get(); }
	const IRigidBody* GetRigidBody() const { return rigidBody.get(); }
	
	bool IsDynamic() const;
		  
	/// parent

	      ActorComponent* GetParent()			{ return parent; }
	const ActorComponent* GetParent() const		{ return parent; }

	/// components

	      std::vector<ActorComponent*>& GetSubcomponents();
	const std::vector<ActorComponent*>& GetSubcomponents() const;

public: //~~~~~~~~~~~~~~| Misc

	FVector SpaceToWorld(const FVector& v, ESpaceType space) const;
	FQuat   SpaceToWorld(const FQuat&   v, ESpaceType space) const;
	
protected:
	/** NOTE:
	* @param bExcludePhysics - if true child dynamic object won't be updated
	* @param bUpdateBody     - if true - update a rigid body with
	*/

	void AddSubcomponent   (ActorComponent* child);
	void RemoveSubcomponent(ActorComponent* child);

	void Internal_GetSubcomponents(std::vector<		 ActorComponent*>& components);
	void Internal_GetSubcomponents(std::vector<const ActorComponent*>& components) const;

	void UpdateFacade();
	void UpdateBody();

	void UpdateWoldTransform    (bool bExcludePhysics, bool bUpdateBody);
	void UpdateRelativeTransform(bool bExcludePhysics, bool bUpdateBody);
	void UpdateChainTransforms  (bool bExcludePhysics, bool bUpdateBody);

	FTransform GetParentTransform() const;

protected:

	virtual void OnSubcomponentAttached(ActorComponent* child ) {}
	virtual void OnSubcomponentDetached(ActorComponent* child ) {}
	virtual void OnComponentAttached   (ActorComponent* parent) {}
	virtual void OnComponentDetached   (ActorComponent* parent) {}
	virtual void onSubcomponentMoved   (ActorComponent* child, bool bUpdateBody) {}
	virtual void onComponentMoved      (bool bUpdateBody);   

protected:

	/// >> common 
	Actor*	owner;
	/// << 

	/// << modules
	UNIQUE(IFacade)		facade;
	UNIQUE(IRigidBody)	rigidBody;
	///

	/// >> position
	FTransform relativeTarnsform;
	FTransform worldTransform;
	/// <<

	/// >> tree
	ActorComponent* parent;
	std::vector<ActorComponent*> subcomponents;
	/// <<
};

#endif // !ACTOR_COMPONENT_HPP