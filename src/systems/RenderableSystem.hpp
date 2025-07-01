#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "../core/System.hpp"

namespace MM {

	class RenderableSystem : System {
		public:
		void SetMesh(unsigned plane, const float * positions, const unsigned int * indices);
		void SetMaterial(unsigned plane, const char * str, const char * text);
	};

} // MM

#endif //RENDERABLE_HPP
