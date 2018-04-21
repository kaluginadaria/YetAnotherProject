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
	virtual void Update(float deltaTime);
	virtual void RegisterBody  (IRigidBody* ibody);
	virtual void UnregisterBody(IRigidBody* ibody);

public:
	void SyncBody(struct RigidBody* body);

protected:
	UNIQUE(btDefaultCollisionConfiguration)		collisionConfiguration;
	UNIQUE(btCollisionDispatcher)				collisionDispatcher;
	UNIQUE(btDbvtBroadphase)					overlappingPairCache;
	UNIQUE(btSequentialImpulseConstraintSolver) constreintSolver;
	UNIQUE(btDiscreteDynamicsWorld)				dynamicsWorld;

	std::set<RigidBody*> rigidBodies;
};



#endif // !BTSCENE_HPP
