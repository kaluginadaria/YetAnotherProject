#include "BTPhysicsScene.hpp"

#include "BTRigidBody.hpp"

PhysicsScene::PhysicsScene()
{
	collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
	collisionDispatcher    = std::make_unique<btCollisionDispatcher> 
		(
		collisionConfiguration.get()
		);
	overlappingPairCache   = std::make_unique<btDbvtBroadphase>();
	constreintSolver       = std::make_unique<btSequentialImpulseConstraintSolver>();
	dynamicsWorld		   = std::make_unique<btDiscreteDynamicsWorld>
		(
		collisionDispatcher .get(), 
		overlappingPairCache.get(), 
		constreintSolver    .get(), 
		collisionConfiguration.get()
		);
	dynamicsWorld->setGravity(btVector3(0, 0, -30));
}

PhysicsScene::~PhysicsScene()
{
	if (dynamicsWorld)
	{
		for (int i = dynamicsWorld->getNumCollisionObjects(); i >= 0; --i)
		{
			btCollisionObject* object = dynamicsWorld->getCollisionObjectArray()[i];
			dynamicsWorld->removeCollisionObject(object);
		}
	}
}

void PhysicsScene::Update(float deltaTime)
{
	dynamicsWorld->synchronizeMotionStates();
	dynamicsWorld->stepSimulation(deltaTime, /*maxSubSteps=*/10);

	for (auto body : rigidBodies)
	{
		if (body)
		{
			body->Sync();
		}
	}
}

void PhysicsScene::RegisterBody(IRigidBody* ibody)
{
	if (RigidBody* body = dynamic_cast<RigidBody*>(ibody))
	{
		if (body->rigidBody)
		{
			dynamicsWorld->addRigidBody(body->rigidBody.get());
		}
		rigidBodies.emplace(body);
	}
}

void PhysicsScene::UnregisterBody(IRigidBody* ibody)
{
	if (RigidBody* body = dynamic_cast<RigidBody*>(ibody))
	{
		if (body->rigidBody)
		{
			dynamicsWorld->removeRigidBody(body->rigidBody.get());
		}
		rigidBodies.erase(body);
	}
}

void PhysicsScene::RegisterConstraint(IConstraint * constraint)
{

}

void PhysicsScene::UnregisterConstraint(IConstraint * constraint)
{

}

void PhysicsScene::SyncBody(RigidBody* body)
{
	if (body && body->rigidBody)
	{
		auto* rigidBody = body->rigidBody.get();

		if (!rigidBodies.count(body))
		{
			rigidBodies.insert(body);
		}
		else
		{
			dynamicsWorld->removeRigidBody(rigidBody);
		}

		dynamicsWorld->addRigidBody(rigidBody);
	}
}

void PhysicsScene::SetConstraint(btPoint2PointConstraint* constraint)
{
	if (dynamicsWorld && constraint)
	{
		dynamicsWorld->addConstraint(constraint);
	}
}

void PhysicsScene::RemoveConstraint(btPoint2PointConstraint* constraint)
{
	if (dynamicsWorld && constraint)
	{
		dynamicsWorld->removeConstraint(constraint);
	}
}
