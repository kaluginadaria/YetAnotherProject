#pragma once
#ifndef ICONSTRAINT_HPP
#define ICONSTRAINT_HPP

#include "Common.hpp"


struct IConstraint
{
public:
	virtual ~IConstraint() {}

public:
	virtual FConstraintType GetConstraints() const          = 0;
	virtual void SetContraints(FConstraint& newConstraints) = 0;
};


#endif // !ICONSTRAINT_HPP
