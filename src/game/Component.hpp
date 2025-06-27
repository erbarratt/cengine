#pragma once

namespace MarMyte
{

	enum ComponentType
	{
		NONE = 0,
		MESH = 1,
		RIGIDBODY = 2,
	};

	class Component
	{
	public:
		virtual ~Component() = default;

		bool isEnabled = false;
		unsigned int componentType;

		explicit Component(unsigned int type, bool enable = false);

		void enable();
		void disable();

		virtual void update() = 0;
		virtual void fixedUpdate() = 0;
	};
}
