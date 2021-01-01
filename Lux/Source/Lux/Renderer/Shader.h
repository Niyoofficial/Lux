#pragma once

#include <D:\Documents\VisualStudio\Projects\Lux\Lux\Vendor\glm\glm\glm.hpp>
#include <D:\Documents\VisualStudio\Projects\Lux\Lux\Vendor\glm\glm\gtc\type_ptr.hpp>
#include <string>

namespace Lux
{
	class Shader
	{
	public:
		Shader(std::string fragmentFilepath, std::string vertexFilepath);
		virtual ~Shader();

		void Bind();
		void Unbind();

		void UploadViewProjectionMatrix(const glm::mat4& vp);

	protected:
		bool AddShader(const std::string& filepath, unsigned int type);
		void CompileShader();

	private:
		uint32_t m_RendererID, m_VertexShaderID, m_FragmentShaderID;
	};
}
