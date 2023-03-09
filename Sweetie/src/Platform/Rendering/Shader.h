#pragma once
#include "pch.h"
#include "Sweetie_c/Core.h"
#include <glm/glm.hpp>

namespace Sweetie
{
	class Shader
	{
	public:
		virtual ~Shader() {};
		virtual void Bind() const = 0;

		static Shader* Create(const std::string& ShaderFile);

		virtual void SendData1F(const char* uniformName, glm::vec1 data)	const = 0;
		virtual void SendData2F(const char* uniformName, glm::vec2 data)	const = 0;
		virtual void SendData3F(const char* uniformName, glm::vec3 data)	const = 0;
		virtual void SendData4F(const char* uniformName, glm::vec4 data)	const = 0;
		virtual void SendDataMat4f(const char* uniformName, glm::mat4 data) const = 0;
	};
}

