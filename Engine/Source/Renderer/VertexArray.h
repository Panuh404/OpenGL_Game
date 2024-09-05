#pragma once
#include <cstdint>
#include <memory>

#include "Buffer.h"

namespace Quiet
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		const uint32_t GetID() const { return m_RendererID; }

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer);
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer);

	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;

		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}
