#pragma once

#include <vector>
#include <memory>
#include "core/commands/base_command.h"

namespace plb
{
	class CommandSystem
	{
	public:
		CommandSystem() = default;
		~CommandSystem() = default;

		void push(std::unique_ptr<ICommand> cmd);
		void commit();
	private:
		std::vector<std::unique_ptr<ICommand>> m_CommandBuffer;
	};
}