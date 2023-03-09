#include "pch.h"
#include "OpenGlShader.h"
#include "Sweetie_c/Log.h"

#include <glad/glad.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

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
            SW_CORE_ERROR("[OPEN_GL_ERROR] {0}", error);
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
        m_ProgramID = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, Shaders.Vertex);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, Shaders.Fragment);

        GLCall(glAttachShader(m_ProgramID, vs));
        GLCall(glAttachShader(m_ProgramID, fs));
        GLCall(glLinkProgram(m_ProgramID));
        GLCall(glValidateProgram(m_ProgramID));

        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));
	}

	OpenGlShader::~OpenGlShader()
	{
        GLCall(glDeleteProgram(m_ProgramID));
	}

	void OpenGlShader::Bind() const 
	{
        GLCall(glUseProgram(m_ProgramID));
	}
    void OpenGlShader::SendData1F(const char* uniformName, glm::vec1 data) const
    {
        glUniform1f(glGetUniformLocation(m_ProgramID, uniformName), data.x);
    }
    void OpenGlShader::SendData2F(const char* uniformName,glm::vec2 data) const
    {
        glUniform2f(glGetUniformLocation(m_ProgramID, uniformName), data.x, data.y);
    }
    void OpenGlShader::SendData3F(const char* uniformName, glm::vec3 data) const
    {
        glUniform3f(glGetUniformLocation(m_ProgramID, uniformName), data.x, data.y, data.z);
    }
    void OpenGlShader::SendData4F(const char* uniformName, glm::vec4 data) const
    {
        glUniform4f(glGetUniformLocation(m_ProgramID, uniformName), data.x, data.y, data.z, data.w);
    }
    void OpenGlShader::SendDataMat4f(const char* uniformName,glm::mat4 data) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, uniformName), 1, GL_FALSE, glm::value_ptr(data));
    }
}
