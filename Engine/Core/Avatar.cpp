#include "Avatar.hpp"
#include "PlayerController.hpp"

Avatar::Avatar()
{
	controller = static_cast<PlayerController*>(ThreadContext::TopInitialiser()->controller);
}
