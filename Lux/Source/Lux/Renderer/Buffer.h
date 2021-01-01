#pragma once

namespace Lux
{
	enum class ShaderDataType
	{
		None, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t GetShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case Lux::ShaderDataType::None:		return 0;
		case Lux::ShaderDataType::Float:	return 4;
		case Lux::ShaderDataType::Float2:	return 4 * 2;
		case Lux::ShaderDataType::Float3:	return 4 * 3;
		case Lux::ShaderDataType::Float4:	return 4 * 4;
		case Lux::ShaderDataType::Mat3:		return 4 * 3 * 3;
		case Lux::ShaderDataType::Mat4:		return 4 * 4 * 4;
		case Lux::ShaderDataType::Int:		return 4;
		case Lux::ShaderDataType::Int2:		return 4 * 2;
		case Lux::ShaderDataType::Int3:		return 4 * 3;
		case Lux::ShaderDataType::Int4:		return 4 * 4;
		case Lux::ShaderDataType::Bool:		return 1;
		default: LX_CORE_ASSERT(false, "Unknown data type!"); return 0;
		}
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;

		BufferElement(ShaderDataType type, const std::string& name)
			:Name(name), Type(type), Size(GetShaderDataTypeSize(type)), Offset(0) {}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case Lux::ShaderDataType::None:		return 0;
			case Lux::ShaderDataType::Float:	return 1;
			case Lux::ShaderDataType::Float2:	return 2;
			case Lux::ShaderDataType::Float3:	return 3;
			case Lux::ShaderDataType::Float4:	return 4;
			case Lux::ShaderDataType::Mat3:		return 3 * 3;
			case Lux::ShaderDataType::Mat4:		return 4 * 4;
			case Lux::ShaderDataType::Int:		return 1;
			case Lux::ShaderDataType::Int2:		return 2;
			case Lux::ShaderDataType::Int3:		return 3;
			case Lux::ShaderDataType::Int4:		return 4;
			case Lux::ShaderDataType::Bool:		return 1;
			default: LX_CORE_ASSERT(false, "Unknown data type!"); return 0;
			}
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:m_Elements(elements) 
		{
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = m_Stride;
				m_Stride += element.Size;
			}
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline const uint32_t& GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}
