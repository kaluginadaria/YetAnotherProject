#include "ObjectBase.hpp"

ObjectBase::ObjectBase()
	: world( ThreadContext::TopInitialiser()->world)
	, name (*ThreadContext::TopInitialiser()->name )
	, ouid ( ThreadContext::TopInitialiser()->ouid )
	, type ( ThreadContext::TopInitialiser()->type )
{}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::OnConstructed()
{
}

void ObjectBase::OnBeginPlay()
{
}

void ObjectBase::OnEndPlay()
{
}

void ObjectBase::OnStartDestroy()
{
}


