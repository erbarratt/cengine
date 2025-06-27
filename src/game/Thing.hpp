#ifndef THING_HPP
#define THING_HPP
#include <vector>

#include "Component.hpp"
#include "GLEW/glew.h"

namespace MarMyte
{

	struct ThingPosition
	{
		GLfloat x;
		GLfloat y;
		GLfloat z;
	};

	struct ThingRotation
	{
		GLfloat x;
		GLfloat y;
		GLfloat z;
	};

	struct ThingScale
	{
		GLfloat x;
		GLfloat y;
		GLfloat z;
	};

	class Thing {
	public:
		ThingPosition position;
		ThingRotation rotation;
		ThingScale scale;
		Thing(ThingPosition pos, ThingRotation rot, ThingScale scl);
		void addComponent(Component component);
	private:
		std::vector<Component> components;
	};

}

#endif //THING_HPP
