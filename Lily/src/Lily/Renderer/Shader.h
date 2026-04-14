#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Lily {

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind();
		void Unbind();

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		unsigned int m_RendererID;
	};
}