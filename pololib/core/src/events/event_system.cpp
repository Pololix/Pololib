#include "core/events/event_system.h"

namespace plb
{
	void EventSystem::push(std::unique_ptr<IEvent> e)
	{
		m_EventBuffer.push_back(std::move(e));
	}

	void EventSystem::flush(LayerStack& stack)
	{
		for (auto& e : m_EventBuffer)
		{
			stack.propagateEvent(*e);
		}
		m_EventBuffer.clear();
	}
}