#pragma once

namespace plb
{
	class IGraphicsContext
	{
	public:
		virtual ~IGraphicsContext() = 0;

		virtual void init() = 0;
	};
}