#pragma once

#include "core/base_window.h"
#include "core/layers/base_layer.h"
#include "core/layers/layer_stack.h"
#include "core/events/event_system.h"

namespace plb
{
	struct AppSpecs
	{
		WinSpecs winSpecs;
	};

	class Application
	{
	public:
		Application(AppSpecs&& specs);
		~Application() = default;

		LayerID pushLayer(std::unique_ptr<ILayer> layer);
		LayerID pushOverlay(std::unique_ptr<ILayer> layer);

		void run();
	private:
		std::unique_ptr<IWindow> m_RootWindow;

		LayerStack m_LayerStack;
		EventSystem m_EventSystem;
		//CommandSystem m_CommandSystem;
		//Renderer m_Renderer;
	};
}