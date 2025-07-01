#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "../core/Coordinator.hpp"
#include "../core/System.hpp"

extern Coordinator gCoordinator;

namespace MM {

	class RenderableSystem : public System {
		public:
		void SetMesh(unsigned plane, float * positions, unsigned int * indices);
		void SetMaterial(unsigned plane, const char * str, const char * text);
	};

} // MM

#endif //RENDERABLE_HPP
