#include "core/application.h"

#include "core/debug/assert_macros.h"

namespace plb
{
	extern std::unique_ptr<plb::IWindow> getWindow();

	Application::Application(AppSpecs&& specs)
		: m_RootWindow(getWindow())
	{
		m_RootWindow->setEventCallback([this](std::unique_ptr<IEvent> e) 
		{
			m_EventSystem.push(std::move(e));
		});

		m_RootWindow->build(std::move(specs.winSpecs));
	}

	LayerID Application::pushLayer(std::unique_ptr<ILayer> layer)
	{
		return m_LayerStack.attachLayer(std::move(layer), false);
	}

	LayerID Application::pushOverlay(std::unique_ptr<ILayer> layer)
	{
		return m_LayerStack.attachLayer(std::move(layer), true);
	}

	void Application::run()
	{
		float currentTime = 0, pastTime = 0, deltaTime = 0;

		while (true) //PLB_TODO: add smart termination on rootWindow's close event
		{
			currentTime = m_RootWindow->getTime();
			deltaTime = currentTime - pastTime;
			pastTime = currentTime;

			m_RootWindow->pollEvents();
			m_EventSystem.flush(m_LayerStack);

			m_LayerStack.update(deltaTime);
			//m_CommandSystem.commit();

			//m_Renderer.beginNewFrame(); //PLB_TODO: integrate imgui to the cycle
			m_LayerStack.render();
			//m_Renderer.commit();
			//m_Renderer.endFrame();

			m_RootWindow->swapBuffers();
		}
	}
}