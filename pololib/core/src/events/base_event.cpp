#include "core/events/base_event.h"

namespace plb
{
	bool IEvent::isInCategory(EventCategory cat)
	{
		return getCategories() & static_cast<int>(cat);
	}
}