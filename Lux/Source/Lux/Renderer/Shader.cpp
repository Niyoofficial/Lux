#include "lxpch.h"
#include "Shader.h"
#include <glad/glad.h>
#include <fstream>

namespace Lux
{
	Shader::Shader(std::string fragmentFilepath, std::string vertexFilepath)
	{
		m_RendererID = glCreateProgram();

		AddShader(vertexFilepath, GL_VERTEX_SHADER);
		AddShader(fragmentFilepath, GL_FRAGMENT_SHADER);

		CompileShader();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	bool Shader::AddShader(const std::string& filepath, unsigned int type)
	{
		std::ifstream ifs(filepath.c_str());
		if (!ifs.is_open())
		{
			std::cout << "Could not open file: " << filepath << std::endl;
			return false;
		}

		std::string line;
		std::string source;
		while (getline(ifs, line))
			source.append(line.append("\n"));
		ifs.close();

		uint32_t ID = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(ID, 1, &src, nullptr);
		glCompileShader(ID);

		int result;
		glGetShaderiv(ID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(ID, length, &length, message);
			LX_CORE_ERROR("Failed to compile {0} shader!", type == GL_VERTEX_SHADER ? "vertex" : "fragment");
			glDeleteShader(ID);
			LX_CORE_ASSERT(false, message);
			return false;
		}

		switch (type)
		{
		case GL_VERTEX_SHADER:
			glDeleteShader(m_VertexShaderID);
			m_VertexShaderID = ID;
			break;
		case GL_FRAGMENT_SHADER:
			glDeleteShader(m_FragmentShaderID);
			m_FragmentShaderID = ID;
			break;
		default:
			LX_CORE_ASSERT(false, "Not supported shader type!");
		}

		return true;
	}

	void Shader::CompileShader()
	{
		glAttachShader(m_RendererID, m_VertexShaderID);
		glAttachShader(m_RendererID, m_FragmentShaderID);

		glLinkProgram(m_RendererID);
		int linkingResult;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &linkingResult);
		if (linkingResult == GL_FALSE)
		{
			int length;
			glGetShaderiv(m_RendererID, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(m_RendererID, length, &length, message);
			LX_CORE_ERROR("Failed to link shader!");
			glDeleteProgram(m_RendererID);
			glDeleteShader(m_VertexShaderID);
			glDeleteShader(m_FragmentShaderID);
			LX_CORE_ASSERT(false, message);
		}

		glDetachShader(m_RendererID, m_VertexShaderID);
		glDetachShader(m_RendererID, m_FragmentShaderID);

		glValidateProgram(m_RendererID);

		glDeleteShader(m_VertexShaderID);
		glDeleteShader(m_FragmentShaderID);
	}

	void Shader::Bind()
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::UploadViewProjectionMatrix(const glm::mat4& vp)
	{
		int location = glGetUniformLocation(m_RendererID, "u_ViewProjection");
		if (location != -1)
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(vp));
	}
}
