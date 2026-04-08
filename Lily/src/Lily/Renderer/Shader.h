#pragma once

#include <string>

namespace Lily {

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind();
		void Unbind();

	private:
		unsigned int m_RendererID;
	};
}