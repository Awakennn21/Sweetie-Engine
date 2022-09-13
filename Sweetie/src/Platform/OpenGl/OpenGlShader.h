#pragma once
#include "Sweetie_c/Core.h"
#include <string>
namespace Sweetie
{
	struct VFShaders
	{
		std::string Vertex;
		std::string Fragment;
	};

	class OpenGlShader
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

		void Bind();
	};
}

