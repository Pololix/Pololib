#pragma once

namespace plb
{
	enum class EventType
	{
		None = 0, //PLB_TODO: populate
	};

	//use bitmask
	enum class EventCategory
	{
		None = 0, //PLB_TODO: populate
	};

	class IEvent
	{
	public:
		bool m_Handled = false;

 		virtual ~IEvent() = 0;

		virtual EventType getType() = 0;
		virtual int getCategories() = 0;

		bool isInCategory(EventCategory cat);
	};
}