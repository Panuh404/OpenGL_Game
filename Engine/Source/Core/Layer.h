#pragma once
#include "Timestep.h"
#include "Event/Event.h"

namespace Quiet
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep dt) {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
