#ifndef BTCONVERSION_HPP
#define BTCONVERSION_HPP
#pragma once

#include "btBulletDynamicsCommon.h"
#include "Common.hpp"


btVector3&    operator<<(btVector3   & l, const FVector     & r);
btQuaternion& operator<<(btQuaternion& l, const FQuat       & r);
btTransform&  operator<<(btTransform & l, const FTransform  & r);
FVector&      operator<<(FVector     & l, const btVector3   & r);
FQuat&        operator<<(FQuat       & l, const btQuaternion& r);
FTransform&   operator<<(FTransform  & l, const btTransform & r);


#endif // !BTCONVERSION_HPP
