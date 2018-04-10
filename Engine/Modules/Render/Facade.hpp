#pragma once

#include <memory>

#include "../Misc.hpp"


#include <osg/ref_ptr>
#include <osg/Switch>
#include <osg/Geode>
#include <osg/Math>
#include <osg/Matrixd>
#include <osg/MatrixTransform>
#include <osg/Vec3d>
#include <osg/PositionAttitudeTransform>



/** Facade - is abstract visualisation component
 *	generateing a 
 */
class Facade
{
public:

	Facade();
	virtual ~Facade();

public:

	void AttachTo(Facade& parent);
	void Detach();

	void Update()
	{/*
		Vector3f newVec = relativeTarnsform.getOrigin();

		osg::Vec3 newPos = osg::Vec3(
			static_cast<float>(newVec.x),
			static_cast<float>(newVec.y),
			static_cast<float>(newVec.z)
		);

		facade.GetRoot()->setPosition(newPos);

		Quatf newQuat = relativeTarnsform.getRotation();

		osg::Quat newRot = osg::Quat(
			static_cast<float>(newQuat.v.x),
			static_cast<float>(newQuat.v.y),
			static_cast<float>(newQuat.v.z),
			static_cast<float>(newQuat.w)
		);

		facade.GetRoot()->setAttitude(newRot);*/
	}

public:

	osg::ref_ptr<osg::PositionAttitudeTransform> GetRoot();

public:

	/// >>
	osg::ref_ptr<osg::PositionAttitudeTransform> rootOffset;
	osg::ref_ptr<osg::Geode					   > mesh;

	bool bHiden;
	/// <<
};