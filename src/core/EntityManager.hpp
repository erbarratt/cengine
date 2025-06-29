#pragma once
#include <array>
#include <queue>

#include "ecs.h"

namespace MarMyte
{
	class EntityManager
	{
	public:
		EntityManager();
		unsigned int CreateEntity();
		void DestroyEntity(unsigned int entity);
		void SetSignature(unsigned int entity, Signature signature);
		[[nodiscard]] Signature GetSignature(unsigned int entity) const;

	private:
		// Queue of UNUSED unsigned int IDs
		std::queue<unsigned int> mAvailableEntities{};

		// Array of signatures where the index corresponds to the unsigned int ID
		std::array<Signature, MAX_ENTITIES> mSignatures{};

		// Total living entities - used to keep limits on how many exist
		unsigned int mLivingEntityCount{};
	};
}
