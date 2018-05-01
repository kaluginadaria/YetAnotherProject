#include "BoxColision.hpp"


BoxColision::BoxColision()
	: extends(1, 1, 1)
{}

void BoxColision::SetExtends(FVector newExtends)
{
	extends = newExtends;
}
