#include "Thing.hpp"

namespace MarMyte
{
	Thing::Thing(const ThingPosition pos, const ThingRotation rot, const ThingScale scl):
		position(pos), rotation(rot), scale(scl)
	{}

	void Thing::addComponent(Component component)
	{
		components.push_back(component);
	}
}
