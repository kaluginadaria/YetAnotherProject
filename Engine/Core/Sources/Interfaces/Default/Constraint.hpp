#pragma once
#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

#include "../IConstraint.hpp"


struct FConstraint : public IConstraint
{
	FConstraint(FConstraintType type);

	virtual FConstraintType GetConstraints() const override;

protected:
	FConstraintType constraint;
};



#endif //!CONSTRAINT_HPP