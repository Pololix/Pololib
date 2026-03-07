#include "core/commands/command_system.h"

namespace plb
{
	void CommandSystem::push(std::unique_ptr<ICommand> cmd)
	{
		m_CommandBuffer.push_back(std::move(cmd));
	}

	void CommandSystem::commit()
	{
		for (auto& cmd : m_CommandBuffer)
		{
			cmd->m_Execute();
		}
	}
}