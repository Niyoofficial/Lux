#include "lxpch.h"
#include "LayerStack.h"

namespace Lux
{
	Lux::LayerStack::LayerStack()
	{
	}

	Lux::LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void Lux::LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_InsertLayerIndex, layer);
		m_InsertLayerIndex++;
		layer->OnAttach();
	}

	void Lux::LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void Lux::LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_InsertLayerIndex--;
			layer->OnDetach();
		}
	}

	void Lux::LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			overlay->OnDetach();
		}
	}
}