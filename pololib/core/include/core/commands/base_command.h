#pragma once

#include <functional>

namespace plb
{
	class ICommand
	{
	public:
		bool m_Executed = false;
		std::function<void()> m_Execute;
	};
}