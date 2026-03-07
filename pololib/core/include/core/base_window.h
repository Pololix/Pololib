#pragma once

#include <memory>
#include <functional>
#include "core/events/base_event.h"
#include "core/base_graphics_context.h"

namespace plb
{
	struct WinSpecs
	{
		unsigned int width = 1920;
		unsigned int height = 1080;
		const char* name = "";
		bool fullscreen = true;
	};

	class IWindow
	{
	public:
		virtual ~IWindow() = default;

		void setEventCallback(std::function<void(std::unique_ptr<IEvent>)> fn);
		virtual void build(WinSpecs&& specs) = 0;

		virtual void pollEvents() = 0;
		virtual void swapBuffers() = 0;
		virtual void makeContextCurrent() = 0;

		virtual float getTime() = 0;
	protected:
		std::function<void(std::unique_ptr<IEvent>)> m_PushEvent;
		std::unique_ptr<IGraphicsContext> m_Context;
	};
}