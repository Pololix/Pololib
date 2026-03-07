#pragma once

#include <functional>
#include "core/events/base_event.h"

namespace plb
{
	using LayerID = unsigned int;

	class LayerStack;

	class ILayer
	{
	public:
		bool m_Suspended = false;
		bool m_Overlay;
		LayerID m_ID = 0;

		~ILayer() = default;

		void setCommandCallback(std::function<void(std::unique_ptr<ICommand>)> fn);

		virtual void onAttach(LayerStack& stack) {}
		virtual void onSuspend(LayerStack& stack) {}
		virtual void onInclude(LayerStack& stack) {}
		virtual void onDetach(LayerStack& stack) {}

		virtual void onUpdate(float deltaTime) {}
		virtual void onEvent(IEvent& event) {}
		virtual void onRender() {}
	protected:
		std::function<void(std::unique_ptr<IEvent>)> m_PushCommmand;
	};
}