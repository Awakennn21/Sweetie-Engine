#pragma once
#include "Sweetie_c/Core.h"
#include "Platform/Rendering/Buffers.h"



namespace Sweetie
{

	class OpenGlVertexBuffer : public VertexBuffer
	{
	private:
		unsigned int BufferId;
		BufferLayout m_Layout;
	public:
		OpenGlVertexBuffer(float* Vertecies, uint32_t size);
		~OpenGlVertexBuffer();

		virtual const BufferLayout& GetLayout() const override { return m_Layout; };
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };

		virtual void Bind() const override;
		virtual void UnBind() const override;

	};

	class OpenGlIndexBuffer : public IndexBuffer
	{
	private:
		unsigned int BufferId;
		uint32_t m_IndicesCount;
	public:
		OpenGlIndexBuffer(uint32_t* Indecies, uint32_t count);
		~OpenGlIndexBuffer();

		virtual uint32_t GetCount() const override { return m_IndicesCount; }
		virtual void Bind() const override;
		virtual void UnBind() const override;
	};
}