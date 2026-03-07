#include "core/layers/layer_stack.h"

#include <algorithm>
#include "core/events/base_event.h"
#include "core/layers/base_layer.h"
#include "core/debug/log_macros.h"

namespace plb
{
	LayerID LayerStack::attachLayer(std::unique_ptr<ILayer> layer, bool overlay)
	{
		layer->m_ID = m_FreeID++;
		layer->m_Overlay = overlay;
		layer->onAttach(*this);

		if (overlay)
		{
			m_LayerBuffer.push_back(std::move(layer));
		}
		else
		{
			m_LayerBuffer.insert(m_LayerBuffer.begin() + m_OverlayIndex, std::move(layer));
			m_OverlayIndex++;
		}

		return m_FreeID;
	}

	void LayerStack::suspendLayer(LayerID ID)
	{
		unsigned int pos = getPos(ID);

		if (pos == 0)
		{
			PLB_LOG_WARN("LayerStack", "Tried to access a destroyed layer");
			return;
		}

		if (m_LayerBuffer.at(pos)->m_Suspended)
		{
			PLB_LOG_WARN("LayerStack", "Tried to suspend a suspended layer");
			return;
		}

		m_LayerBuffer.at(pos)->onSuspend(*this);
		m_LayerBuffer.at(pos)->m_Suspended = true;
	}

	void LayerStack::includeLayer(LayerID ID)
	{
		unsigned int pos = getPos(ID);

		if (pos == 0)
		{
			PLB_LOG_WARN("LayerStack", "Tried to access a destroyed layer");
			return;
		}

		if (!m_LayerBuffer.at(pos)->m_Suspended)
		{
			PLB_LOG_WARN("LayerStack", "Tried to include an active layer");
			return;
		}

		m_LayerBuffer.at(pos)->onInclude(*this);
		m_LayerBuffer.at(pos)->m_Suspended = false;
	}

	void LayerStack::detachLayer(LayerID ID)
	{
		unsigned int pos = getPos(ID);

		if (pos == 0)
		{
			PLB_LOG_WARN("LayerStack", "Tried to access a destroyed layer");
			return;
		}

		m_LayerBuffer.at(pos)->onDetach(*this);
		m_OverlayIndex -= m_LayerBuffer.at(pos)->m_Overlay ? 0 : 1;
		m_LayerBuffer.erase(m_LayerBuffer.begin() + pos);
	}

	void LayerStack::propagateEvent(IEvent& e) const
	{
		for (auto layer = m_LayerBuffer.rbegin(); layer != m_LayerBuffer.rend(); layer++)
		{
			(*layer)->onEvent(e);
			if (e.m_Handled) break;
		}
	}

	void LayerStack::update(float deltaTime) const
	{
		for (auto layer = m_LayerBuffer.rbegin(); layer != m_LayerBuffer.rend(); layer++)
		{
			(*layer)->onUpdate(deltaTime);
		}
	}

	void LayerStack::render() const
	{
		for (auto layer = m_LayerBuffer.begin(); layer != m_LayerBuffer.end(); layer++)
		{
			(*layer)->onRender();
		}
	}

	unsigned int LayerStack::getPos(LayerID ID) const
	{
		auto target = std::find_if(m_LayerBuffer.begin(), m_LayerBuffer.end(), [ID](const std::unique_ptr<ILayer>& layer)
		{
			return layer->m_ID = ID;
		});

		if (target != m_LayerBuffer.end())
		{
			return std::distance(m_LayerBuffer.begin(), target);
		}
		else
		{
			return 0;
		}
	}
}