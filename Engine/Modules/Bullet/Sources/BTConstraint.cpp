#include "BTConstraint.hpp"
#include "BTPhysicsScene.hpp"

Constraint::Constraint(ActorComponent* owner)
	: FConstraint(owner)
{}

btTransform Constraint::GetTransform() const
{
	if (owner)
	{
		FTransform transform = owner->GetComponentTransform();
		btTransform newTransform = btTransform() << transform;
		return newTransform;
	}
	return btTransform();
}

void Constraint::AddChild(IRigidBody* ibody)
{
	auto* body = dynamic_cast<RigidBody*>(ibody);

	if (auto joint = MakeConstraint(parent, body))
	{
		childConstraints.emplace(body, std::move(joint));

		if (auto* scene = GetPhysicsScene<PhysicsScene>())
		{
			scene->SetConstraint(GetConstraint(body));
		}
	}
}

void Constraint::SetParent(IRigidBody* ibody)
{
	if (auto* newParent = dynamic_cast<RigidBody*>(ibody))
	{
		parent = newParent;
		UpdateConstraint();
	}
}

void Constraint::RemoveChild(IRigidBody* ibody)
{
	if (auto* body = dynamic_cast<RigidBody*>(ibody))
	{
		if (auto* scene = GetPhysicsScene<PhysicsScene>())
		{
			scene->RemoveConstraint(GetConstraint(body));
		}
		childConstraints.erase(body);
	}
}

void Constraint::RemoveParent(IRigidBody* ibody)
{
	for (auto& pair : childConstraints)
	{
		if (auto& joint = pair.second)
		{
			if (auto* scene = GetPhysicsScene<PhysicsScene>())
			{
				scene->RemoveConstraint(joint.get());
			}
		}
	}
	parent = nullptr;
}

void Constraint::UpdateConstraint()
{
	for (auto& pair : childConstraints)
	{
		UpdateChild(pair.first);
	}
}

void Constraint::UpdateChild(IRigidBody* ibody)
{
	if (auto* body  = dynamic_cast<RigidBody*>(ibody))
	if (auto& joint = childConstraints[body])
	{
		if (auto* scene = GetPhysicsScene<PhysicsScene>())
		{
			scene->RemoveConstraint(joint.get());
		}
		joint = MakeConstraint(parent, body);
		if (auto* scene = GetPhysicsScene<PhysicsScene>())
		{
			scene->SetConstraint(joint.get());
		}
	}
}

void Constraint::SetContraints(FConstraintType& newConstraints)
{
	constraint = newConstraints;

	for (auto& pair : childConstraints)
	{
		auto* joint = pair.second.get();
		if (joint)
		{
			UpdateConstraint(*joint);
		}
	}
}

void Constraint::UpdateConstraint(btPoint2PointConstraint& target)
{
	//for (int axis = 0; axis < 3; ++axis) // movement
	//{
	//	auto tmp = constraint.movement[axis];
	//	if (!tmp.bAcive) { // make disabled
	//		target.setLimit(axis, 10, -10);
	//	} else {
	//		target.setLimit(axis, tmp.min, tmp.max);
	//	}
	//}
	//for (int axis = 0; axis < 3; ++axis) // rotation
	//{
	//	auto tmp = constraint.rotation[axis];
	//	if (!tmp.bAcive) { // make disabled
	//		target.setLimit(3 + axis, 10, -10);
	//	} else {
	//		target.setLimit(3 + axis, tmp.min, tmp.max);
	//	}
	//}

}

btPoint2PointConstraint* Constraint::GetConstraint(RigidBody* child)
{
	return childConstraints[child].get();
}

UNIQUE(btPoint2PointConstraint) Constraint::MakeConstraint(RigidBody* parent, RigidBody* child)
{
	if (parent && parent->IsValid() && child && child->IsValid())
	{
		auto* joint = new btPoint2PointConstraint (
			 *parent->rigidBody.get()
			,*child ->rigidBody.get()
			, this ->GetTransform().getOrigin()
			, child->GetTransform().inverse().getOrigin()
			);

		UpdateConstraint(*joint);
		return UNIQUE(btPoint2PointConstraint)(joint);
	}
	return UNIQUE(btPoint2PointConstraint)();
}
