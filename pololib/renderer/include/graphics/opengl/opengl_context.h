#pragma once

#include "core/base_graphics_context.h"

namespace plb
{
	class PLB_OpenGLGraphicsContext : public IGraphicsContext
	{
	public:
		PLB_OpenGLGraphicsContext() = default;
		~PLB_OpenGLGraphicsContext() = default;

		void init() override;
	};
}