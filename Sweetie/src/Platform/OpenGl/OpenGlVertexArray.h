#pragma once
#include "pch.h"
#include "Platform/Rendering/Buffers.h"
#include "Platform/Rendering/VertexArray.h"

namespace Sweetie
{

	class OpenGlVertexArray : public VertexArray
	{
	private:
		uint32_t m_VertexArrayId;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	public:
		std::vector<std::shared_ptr<VertexBuffer>>::iterator begin() { return m_VertexBuffers.begin(); }
		std::vector<std::shared_ptr<VertexBuffer>>::iterator end() { return m_VertexBuffers.end(); }
		std::vector<std::shared_ptr<VertexBuffer>>::const_iterator begin() const { return m_VertexBuffers.begin(); }
		std::vector<std::shared_ptr<VertexBuffer>>::const_iterator end() const { return m_VertexBuffers.end(); }

		inline std::shared_ptr<VertexBuffer> GetVertexBuffers(uint32_t index) const { return m_VertexBuffers[index]; }
		inline std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() { return m_VertexBuffers; }
		inline std::shared_ptr<IndexBuffer> GetIndexBuffer() { return m_IndexBuffer; }

		OpenGlVertexArray();
		~OpenGlVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer) override;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer) override;
	};

}