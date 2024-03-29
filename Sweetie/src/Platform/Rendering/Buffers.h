#pragma once
#include "pch.h"
#include "Sweetie_c/Core.h"
#include "Sweetie_c/Log.h"

namespace Sweetie
{
	enum class BufferElementType : uint8_t
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	static uint32_t BufferElementTypeSize(BufferElementType type)
	{
		switch (type)
		{
		case Sweetie::BufferElementType::None:
			return 0;
			break;
		case Sweetie::BufferElementType::Float:
			return 4;
			break;
		case Sweetie::BufferElementType::Float2:
			return 8;
			break;
		case Sweetie::BufferElementType::Float3:
			return 12;
			break;
		case Sweetie::BufferElementType::Float4:
			return 16;
			break;
		case Sweetie::BufferElementType::Int:
			return 4;
			break;
		case Sweetie::BufferElementType::Int2:
			return 8;
			break;
		case Sweetie::BufferElementType::Int3:
			return 12;
			break;
		case Sweetie::BufferElementType::Int4:
			return 16;
			break;
		case Sweetie::BufferElementType::Mat3:
			return 36;
			break;
		case Sweetie::BufferElementType::Mat4:
			return 64;
			break;
		case Sweetie::BufferElementType::Bool:
			return 1;
			break;
		}
		SW_CORE_ASSERT(false, "Wrong Data type provided");
		return 0;
	}

	struct BufferElement
	{
		std::string m_Name;
		BufferElementType m_Type;
		uint32_t m_Size;
		uint32_t m_Offset;
		bool mb_ToNormalize;

		BufferElement(BufferElementType type, const std::string& name, bool toNormalize = false)
			:m_Name(name), m_Type(type), m_Size(BufferElementTypeSize(type)), m_Offset(0), mb_ToNormalize(toNormalize)
		{

		}
		uint32_t GetComponentCount() const
		{
			switch (m_Type)
			{
			case Sweetie::BufferElementType::None:	return 0; 
			case Sweetie::BufferElementType::Float:	return 1;
			case Sweetie::BufferElementType::Float2:return 2;
			case Sweetie::BufferElementType::Float3:return 3;
			case Sweetie::BufferElementType::Float4:return 4;
			case Sweetie::BufferElementType::Int:	return 1;
			case Sweetie::BufferElementType::Int2:	return 2;
			case Sweetie::BufferElementType::Int3:	return 3;
			case Sweetie::BufferElementType::Int4:	return 4;
			case Sweetie::BufferElementType::Mat3:	return 9;
			case Sweetie::BufferElementType::Mat4:	return 16;
			case Sweetie::BufferElementType::Bool:	return 1;
			}
			SW_CORE_ASSERT(false, "Wrong Data type provided");
			return 0;
		}
	};

	class BufferLayout
	{
	private:
		std::vector<BufferElement> m_Layout;
		uint32_t m_Stride;
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& layout)
		: m_Layout(layout)	 
		{
			CalculateOffsetAndStride();
		}
		inline std::vector<BufferElement> GetLayout() const { return m_Layout; }
		inline uint32_t GetStride() const { return m_Stride; }
		std::vector<BufferElement>::iterator begin() { return m_Layout.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Layout.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Layout.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Layout.end(); }
	private:
		void CalculateOffsetAndStride()
		{
			uint32_t offset=0;
			m_Stride = 0;
			for (auto& element : m_Layout)
			{
				element.m_Offset = offset;
				offset += element.m_Size;
				m_Stride += element.m_Size;
			}

		}
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* Vertecies, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual uint32_t GetCount() const = 0;
		static IndexBuffer* Create(uint32_t* Indices, uint32_t count);
	};
}
