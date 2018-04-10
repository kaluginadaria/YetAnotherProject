#include "BoxColision.hpp"


BoxColision::BoxColision()
	: extends(1, 1, 1)
{}

void BoxColision::SetExtends(Vector3f newExtends)
{
	extends = newExtends;
}
