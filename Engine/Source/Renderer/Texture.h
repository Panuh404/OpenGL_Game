#pragma once
#include <string>

#include "glad/glad.h"

namespace Quiet
{
	class Texture2D
	{
	public:
		Texture2D(const std::string& path);
		~Texture2D();

		uint32_t GetWidth() const		{ return m_Width;		}
		uint32_t GetHeight() const		{ return m_Height;		}
		uint32_t GetRendererID() const	{ return m_RendererID;	}

		void SetData(void* data, uint32_t size);
		void Bind(uint32_t slot = 0) const;

	private:
		uint32_t m_RendererID;
		std::string m_Path;

		uint32_t m_Width;
		uint32_t m_Height;
		GLenum m_InternalFormat;
		GLenum m_DataFormat;
	};
}
