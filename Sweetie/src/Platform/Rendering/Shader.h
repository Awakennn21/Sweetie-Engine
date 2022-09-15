#pragma once
#include "pch.h"
#include "Sweetie_c/Core.h"

namespace Sweetie
{
	class Shader
	{
	public:
		virtual ~Shader() {};
		virtual void Bind() const = 0;

		static Shader* Create(const std::string& ShaderFile);
	};
}

