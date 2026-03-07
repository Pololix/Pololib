#include "core/base_window.h"

namespace plb
{
	void IWindow::setEventCallback(std::function<void(std::unique_ptr<IEvent>)> fn)
	{
		m_PushEvent = fn;
	}
}