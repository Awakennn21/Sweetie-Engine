#pragma once
#include "Platform/Rendering/Shader.h"
#include <glm/glm.hpp>
namespace Sweetie
{
	struct VFShaders
	{
		std::string Vertex;
		std::string Fragment;
	};

	class OpenGlShader : public Shader
	{
	private:
		unsigned int m_ProgramID;
	private:
		static void GlClearErrors();
		static bool GlLogCall();

		VFShaders ParseShaders(const std::string& FilePath);
		unsigned int CompileShader(unsigned int ShaderType, const std::string& SourceCode);
		unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
	public:
		OpenGlShader(const std::string& ShaderFile);
		~OpenGlShader();

		virtual void Bind() const override;
		virtual void SendData1F(const char* uniformName, glm::vec1 data)	const override;
		virtual void SendData2F(const char* uniformName, glm::vec2 data)	const override;
		virtual void SendData3F(const char* uniformName, glm::vec3 data)	const override;
		virtual void SendData4F(const char* uniformName, glm::vec4 data)	const override;
		virtual void SendDataMat4f(const char* uniformName, glm::mat4 data) const override;
	};
}

