#include "lxpch.h"
#include "LayerStack.h"

namespace Lux
{
	Lux::LayerStack::LayerStack()
	{
		m_InsertLayer = m_Layers.begin();
	}

	Lux::LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void Lux::LayerStack::PushLayer(Layer* layer)
	{
		m_InsertLayer = m_Layers.emplace(m_InsertLayer, layer);
	}

	void Lux::LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void Lux::LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_InsertLayer--;
		}
	}

	void Lux::LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}
}