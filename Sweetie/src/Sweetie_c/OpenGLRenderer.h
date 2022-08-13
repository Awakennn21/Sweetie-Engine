#pragma once
#include "Core.h"

namespace Sweetie
{
	enum class RendererShapes
	{
		RS_Triangle = 1,
		RS_Rectangle
	};

	struct VFShaders
	{
		std::string Vertex;
		std::string Fragment;
	};

	class SW_API OpenGLRenderer
	{
	private:
		static void GlClearErrors();
		static bool GlLogCall();
		unsigned int CreateBufferWithData(float* Vertecies, unsigned int VerteciesCount);
		unsigned int CreateIndexBuffer(RendererShapes Shape, float* Vertecies);
		void DeduceQuadragonIndecies(int* Buffer, float* Vertecies);

		VFShaders ParseShaders(const std::string& FilePath);
		unsigned int CompileShader(unsigned int ShaderType, const std::string& SourceCode);
		unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);

	public:
		OpenGLRenderer();
		~OpenGLRenderer();

		void Clear();
		bool RenderShape(RendererShapes Shape, float* Vertecies, float R = 1.0f, float G = 1.0f, float B = 1.0f, float A = 1.0f, std::string ShaderFilePath = "../Sweetie/res/Shaders/BasicShaders.shader");


	};
}

