#pragma once
#ifndef IVIEWER_HPP
#define IVIEWER_HPP

#include "Common.hpp"

class  PlayerController;


struct IViewer
{
	IViewer(PlayerController* controller)
		: controller(controller)
	{}
	virtual ~IViewer() = default;

public:
	virtual void Render() = 0;
	virtual void DrawShape(FShape shape, FTransform transform, FColor color) = 0;

protected:
	PlayerController* controller;
};


#endif // !IVIEWER_HPP
