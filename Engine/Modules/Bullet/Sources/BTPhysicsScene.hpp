#ifndef BTSCENE_HPP
#define BTSCENE_HPP
#pragma once

#include <set>
#include "Common.hpp"
#include "Interfaces/IPhysicsScene.hpp"

#include "btBulletDynamicsCommon.h"


class PhysicsScene : public IPhysicsScene
{
public:
	 PhysicsScene();
	~PhysicsScene();

public:
	virtual void Update(float deltaTime) override;
	virtual void RegisterBody  (IRigidBody* ibody) override;
	virtual void UnregisterBody(IRigidBody* ibody) override;
	virtual void RegisterConstraint  (IConstraint* constraint) override;
	virtual void UnregisterConstraint(IConstraint* constraint) override;

public:
	void SyncBody(struct RigidBody* body);
	void SetConstraint   (btPoint2PointConstraint* constraint);
	void RemoveConstraint(btPoint2PointConstraint* constraint);

protected:
	UNIQUE(btDefaultCollisionConfiguration)		collisionConfiguration;
	UNIQUE(btCollisionDispatcher)				collisionDispatcher;
	UNIQUE(btDbvtBroadphase)					overlappingPairCache;
	UNIQUE(btSequentialImpulseConstraintSolver) constreintSolver;
	UNIQUE(btDiscreteDynamicsWorld)				dynamicsWorld;

	std::set<RigidBody*> rigidBodies;
};



#endif // !BTSCENE_HPP
