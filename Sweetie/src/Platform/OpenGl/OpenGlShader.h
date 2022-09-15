#pragma once
#include "Platform/Rendering/Shader.h"
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
		unsigned int ProgramID;
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
	};
}

