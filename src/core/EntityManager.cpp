#include "EntityManager.hpp"

namespace MarMyte
{
	EntityManager::EntityManager()
	{
		// Initialize the queue with all possible unsigned int IDs
		//for example 0 to 4999...
		for (unsigned int entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			mAvailableEntities.push(entity);
		}
	}

	unsigned int EntityManager::CreateEntity()
	{
		assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

		// Take an ID from the front of the queue
		const unsigned int id = mAvailableEntities.front();

		//remove that id from the pool of available ids
		mAvailableEntities.pop();

		//increase count of living
		++mLivingEntityCount;

		return id;
	}

	void EntityManager::DestroyEntity(const unsigned int entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Invalidate the destroyed entity's signature
		mSignatures[entity].reset();

		// Put the destroyed ID at the back of the queue
		mAvailableEntities.push(entity);
		--mLivingEntityCount;
	}

	void EntityManager::SetSignature(const unsigned int entity, const Signature signature)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Put this entity's signature into the array
		mSignatures[entity] = signature;
	}

	Signature EntityManager::GetSignature(const unsigned int entity) const
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Get this entity's signature from the array
		return mSignatures[entity];
	}
}
