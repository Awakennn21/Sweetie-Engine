#include "pch.h"
#include "OpenGlShader.h"
#include "Sweetie_c/Log.h"

#include <glad/glad.h>

namespace Sweetie
{

    #define GLCall(x) GlClearErrors();\
                      x;\
                      SW_CORE_ASSERT(GlLogCall()," ");


    void OpenGlShader::GlClearErrors()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    bool OpenGlShader::GlLogCall()
    {
        if (GLenum error = glGetError())
        {
            SW_CORE_ERROR("[OPEN_GL_ERROR] (", error, ")");
            return false;
        }
        return true;
    }


	VFShaders OpenGlShader::ParseShaders(const std::string& FilePath)
	{
        std::ifstream File(FilePath);
        SW_CORE_ASSERT(File.is_open(), "Failed to open a file");
        enum class ShaderType
        {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::string Line;
        std::stringstream ss[2];
        ShaderType Type = ShaderType::NONE;

        while (std::getline(File, Line))
        {
            if (Line.find("#shader") != std::string::npos)
            {
                if (Line.find("vertex") != std::string::npos)
                {
                    Type = ShaderType::VERTEX;
                }
                else if (Line.find("fragment") != std::string::npos)
                {
                    Type = ShaderType::FRAGMENT;
                }
            }
            else
            {
                if (Type != ShaderType::NONE)
                {
                    ss[(int)Type] << Line << '\n';
                }
            }
        }

        return { ss[0].str(),ss[1].str() };
	}
	unsigned int OpenGlShader::CompileShader(unsigned int ShaderType, const std::string& SourceCode)
	{
        unsigned int id = glCreateShader(ShaderType);
        const char* Src = SourceCode.c_str();
        GLCall(glShaderSource(id, 1, &Src, NULL));
        GLCall(glCompileShader(id));

        int CompilationResault;
        GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &CompilationResault));
        if (CompilationResault == GL_FALSE)
        {
            int ErrorMessageLength;
            GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &ErrorMessageLength));
            char* ErrorMessage = (char*)_malloca(ErrorMessageLength * sizeof(char));
            GLCall(glGetShaderInfoLog(id, ErrorMessageLength, &ErrorMessageLength, ErrorMessage));

            std::cout << ErrorMessage << std::endl;
            GLCall(glDeleteShader(id));
            return 0;
        }
        return id;
	}
	unsigned int OpenGlShader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
	{
		return 0;
	}
	OpenGlShader::OpenGlShader(const std::string& ShaderFile)
	{
        VFShaders Shaders = ParseShaders(ShaderFile);
        ProgramID = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, Shaders.Vertex);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, Shaders.Fragment);

        GLCall(glAttachShader(ProgramID, vs));
        GLCall(glAttachShader(ProgramID, fs));
        GLCall(glLinkProgram(ProgramID));
        GLCall(glValidateProgram(ProgramID));

        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));
	}

	OpenGlShader::~OpenGlShader()
	{
        GLCall(glDeleteProgram(ProgramID));
	}

	void OpenGlShader::Bind()
	{
        GLCall(glUseProgram(ProgramID));
	}
}
