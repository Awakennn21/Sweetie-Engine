#include "pch.h"
#include "VertexArray.h"
#include "Platform/OpenGl/OpenGlVertexArray.h"

namespace Sweetie
{
	VertexArray* VertexArray::Create()
	{
		return new OpenGlVertexArray();
	}
}
