#include "Constraint.hpp"

FConstraint::FConstraint(FConstraintType type)
	: constraint(type)
{}

FConstraintType FConstraint::GetConstraints() const
{
	return constraint;
}
