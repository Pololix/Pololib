#pragma once

#include <vector>
#include <memory>
#include "core/events/base_event.h"
#include "core/layers/base_layer.h"

namespace plb
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack() = default;

		LayerID attachLayer(std::unique_ptr<ILayer> layer, bool overlay);
		void detachLayer(LayerID ID);

		void suspendLayer(LayerID ID);
		void includeLayer(LayerID ID);

		void propagateEvent(IEvent& e) const;
		void update(float deltaTime) const;
		void render() const;
	private:
		std::vector<std::unique_ptr<ILayer>> m_LayerBuffer;
		unsigned int m_OverlayIndex = 0;
		LayerID m_FreeID = 0;

		unsigned int getPos(LayerID ID) const;
	};
}