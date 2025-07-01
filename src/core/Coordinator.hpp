#pragma once

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "EventManager.hpp"
#include "SystemManager.hpp"
#include "Types.hpp"
#include <memory>


class Coordinator
{
public:
	void Init()
	{
		mComponentManager = std::make_unique<ComponentManager>();
		mEntityManager = std::make_unique<EntityManager>();
		mEventManager = std::make_unique<EventManager>();
		mSystemManager = std::make_unique<SystemManager>();
	}


	// Entity methods
	[[nodiscard]] Entity CreateEntity() const
	{
		return mEntityManager->CreateEntity();
	}

	void DestroyEntity(const Entity entity) const
	{
		mEntityManager->DestroyEntity(entity);

		mComponentManager->EntityDestroyed(entity);

		mSystemManager->EntityDestroyed(entity);
	}


	// Component methods
	template<typename T>
	void RegisterComponent() const
	{
		mComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(const Entity entity, T component)
	{
		mComponentManager->AddComponent<T>(entity, component);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), true);

		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);

	}

	template<typename T>
	void RemoveComponent(const Entity entity) const
	{
		mComponentManager->RemoveComponent<T>(entity);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), false);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(const Entity entity)
	{
		return mComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	[[nodiscard]] ComponentType GetComponentType() const
	{
		return mComponentManager->GetComponentType<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return mSystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(const Signature signature) const
	{
		mSystemManager->SetSignature<T>(signature);
	}


	// Event methods
	void AddEventListener(const EventId eventId, std::function<void(Event&)> const& listener) const
	{
		mEventManager->AddListener(eventId, listener);
	}

	void SendEvent(Event& event) const
	{
		mEventManager->SendEvent(event);
	}

	void SendEvent(const EventId eventId) const
	{
		mEventManager->SendEvent(eventId);
	}

private:
	std::unique_ptr<ComponentManager> mComponentManager;
	std::unique_ptr<EntityManager> mEntityManager;
	std::unique_ptr<EventManager> mEventManager;
	std::unique_ptr<SystemManager> mSystemManager;
};
