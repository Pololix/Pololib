#pragma once

#include <vector>
#include <memory>
#include "core/events/base_event.h"
#include "core/layers/layer_stack.h"

namespace plb
{
	class EventSystem
	{
	public:
		EventSystem() = default;
		~EventSystem() = default;

		void push(std::unique_ptr<IEvent> e);
		void flush(LayerStack& stack);
	private:
		std::vector<std::unique_ptr<IEvent>> m_EventBuffer;
	};
}