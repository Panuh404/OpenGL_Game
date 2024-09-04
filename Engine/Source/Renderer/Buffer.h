#pragma once
#include <cstdint>

namespace Quiet {
	class VertexBuffer {
	public:
		VertexBuffer(float* vertices, uint32_t size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		const uint32_t GetID() const { return m_RendererID; }

	private:
		uint32_t m_RendererID;

	};

	class IndexBuffer {
	public:
		IndexBuffer(uint32_t* indices, uint32_t count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		const uint32_t GetID() const { return m_RendererID; }

	private:
		uint32_t m_RendererID;
	};
}
