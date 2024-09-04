#pragma once
#include <cstdint>

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

	private:
		uint32_t m_RendererID;
	};
}
