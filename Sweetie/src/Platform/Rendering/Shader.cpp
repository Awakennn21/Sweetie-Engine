 #include "pch.h"
#include "Shader.h"
#include "Platform/OpenGl/OpenGlShader.h"
namespace Sweetie
{
	Shader* Shader::Create(const std::string& ShaderFile)
	{
#ifdef OPENGL_RENDERING_API
		return new OpenGlShader(ShaderFile);
#else
		_Static_assert(false);
		return nullptr;
#endif // OPENGL_RENDERING_API
	}
}
