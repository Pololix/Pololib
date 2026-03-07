#include <memory>
#include "core/base_window.h"
#include "platform/windows/wnd_window.h"

namespace plb
{
	std::unique_ptr<plb::IWindow> getWindow()
	{
#ifdef PLB_PLATFORM_WND
		return std::make_unique<plb::WndWindow>();
#endif
	}
}