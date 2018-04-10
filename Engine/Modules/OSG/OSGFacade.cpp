#include "OSGFacade.hpp"
#include "ActorComponent.hpp"


Facade::Facade(ActorComponent* owner)
	: IFacade(owner)
	, rootOffset(new osg::PositionAttitudeTransform)
	, mesh		(new osg::Geode)
	, bHiden	(false)
{
	rootOffset->addChild(mesh);
}

bool Facade::AttachTo(IFacade* parent)
{
	Facade* fparent = static_cast<Facade*>(parent);
	if (fparent)
	{
		fparent->rootOffset->addChild(rootOffset);
		return true;
	}
	return false;
}

bool Facade::Detach()
{
	if (rootOffset && rootOffset->getParent(0))
	{
		rootOffset->getParent(0)->removeChild(rootOffset);
		return true;
	}
	return false;
}

inline void Facade::Update()
{
	if (!owner) return;
	Transform offset = owner->GetRelativeTransform();
	Vector3f newVec = offset.getOrigin();

	osg::Vec3 newPos = osg::Vec3(newVec.x, newVec.y, newVec.z);
	GetRoot()->setPosition(newPos);

	Quatf newQuat = offset.getRotation();
	osg::Quat newRot = osg::Quat(
		newQuat.v.x, 
		newQuat.v.y, 
		newQuat.v.z, 
		newQuat.w );
	GetRoot()->setAttitude(newRot);
}

osg::ref_ptr<osg::PositionAttitudeTransform> Facade::GetRoot()
{
	return rootOffset;
}
