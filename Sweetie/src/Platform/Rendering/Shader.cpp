 #include "pch.h"
#include "Shader.h"
#include "Platform/OpenGl/OpenGlShader.h"
namespace Sweetie
{
	Shader* Shader::Create(const std::string& ShaderFile)
	{
		return new OpenGlShader(ShaderFile);
	}
}
