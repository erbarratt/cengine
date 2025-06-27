#include "Component.hpp"

namespace MarMyte
{

	Component::Component(unsigned int type, bool enable)
	{
		componentType = type;
		isEnabled = enable;
	}

	void Component::enable()
	{
		isEnabled = true;
	}

	void Component::disable()
	{
		isEnabled = false;
	}

}
