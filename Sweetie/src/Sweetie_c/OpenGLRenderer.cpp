#include "pch.h"
#include "OpenGLRenderer.h"
#include "Sweetie_c/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Sweetie
{

    //---------------------------OpenGL Error Handling------------

    #define GLCall(x) GlClearErrors();\
                      x;\
                      SW_CORE_ASSERT(GlLogCall()," ");


    void OpenGLRenderer::GlClearErrors()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    bool OpenGLRenderer::GlLogCall()
    {
        if (GLenum error = glGetError())
        {
            SW_CORE_ERROR("[OPEN_GL_ERROR] (", error, ")");
            return false;
        }
        return true;
    }

    //------------------------------------------------------------


    OpenGLRenderer::OpenGLRenderer()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    OpenGLRenderer::~OpenGLRenderer()
    {
    }

    //----------------------------Drawing Shapes------------------

    unsigned int OpenGLRenderer::CreateBufferWithData(float* Vertecies, unsigned int VerteciesCount)
    {
        unsigned int DrawBuffer;
        GLCall(glGenBuffers(1, &DrawBuffer));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, DrawBuffer));
        GLCall(glBufferData(GL_ARRAY_BUFFER, VerteciesCount * 2 * sizeof(float), Vertecies, GL_STATIC_DRAW));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), 0);
        return DrawBuffer;
    }

    unsigned int OpenGLRenderer::CreateIndexBuffer(RendererShapes Shape, float* Vertecies)
    {
        int* Buffer;
        switch (Shape)
        {
        case RendererShapes::RS_Triangle:
            Buffer = new int[3];
            Buffer[0] = 0;
            Buffer[1] = 1;
            Buffer[2] = 2;
            break;
        case RendererShapes::RS_Rectangle:
            Buffer = new int[6];
            DeduceQuadragonIndecies(Buffer, Vertecies);
            break;
        default:
            SW_ERROR("This shape is not supported");
            return 0;
            break;
        }
        unsigned int IndexBuffer;
        GLCall(glGenBuffers(1, &IndexBuffer));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * 2 * (int)Shape * sizeof(int), Buffer, GL_STATIC_DRAW));
        delete [] Buffer;
        return IndexBuffer;

    }
    //exeption TODO: does Not work when the Quadragon is concaved
    void OpenGLRenderer::DeduceQuadragonIndecies(int* Buffer, float* Vertecies)
    {
        int MinX = -1, MinY = -1, MaxX = -1, MaxY = -1;
        float MinXv = 100.f, MinYv = 100.f, MaxXv = -100.f, MaxYv = -100.f;
        bool VerteciesTaken[4] = { false,false,false,false };

        for (int i = 0; i < 8; i+=2)
        {
            if (Vertecies[i] < MinXv && VerteciesTaken[i / 2] != true)
            {
                MinX = i / 2;
                MinXv = Vertecies[i];
            }
        }
        VerteciesTaken[MinX] = true;
        Buffer[0] = MinX;

        for (int i = 1; i < 8; i += 2)
        {
            if (Vertecies[i] < MinYv && VerteciesTaken[i / 2] != true)
            {
                MinY = i / 2;
                MinYv = Vertecies[i];
            }
        }
        VerteciesTaken[MinY] = true;
        Buffer[1] = MinY;


        for (int i = 0; i < 8; i += 2)
        {
            if (Vertecies[i] > MaxXv && VerteciesTaken[i / 2] != true)
            {
                MaxX = i / 2;
                MaxXv = Vertecies[i];
            }
        }
        VerteciesTaken[MaxX] = true;
        Buffer[2] = MaxX;

        int i;
        for ( i = 0; i < 4; i++)
        {
            if (VerteciesTaken[i] == false)
            {
                break;
            }
        }
        Buffer[3] = MaxX;
        Buffer[4] = i;
        Buffer[5] = MinX;
    }

    void OpenGLRenderer::Clear()
    {
        GLCall(glClearColor(0.9f, 0.9f, 0.9f, 1.f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    bool OpenGLRenderer::RenderShape(RendererShapes Shape, float* Vertecies, float R, float G, float B, float A, std::string ShaderFilePath)
    {
        VFShaders ShadersSource = ParseShaders(ShaderFilePath);
        unsigned int ShaderProgram = CreateShader(ShadersSource.Vertex, ShadersSource.Fragment);
        GLCall(glUseProgram(ShaderProgram));
        unsigned int UniformLocation = glGetUniformLocation(ShaderProgram, "u_Color");
        GLCall(glUniform4f(UniformLocation, R, G, B, A));

        switch (Shape)
        {
        case RendererShapes::RS_Triangle:
        {
            unsigned int DrawBuffer = CreateBufferWithData(Vertecies, 3);
            unsigned int IndexBuffer = CreateIndexBuffer(Shape, Vertecies);
            GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
            break;
        }
        case RendererShapes::RS_Rectangle:
        {
            unsigned int DrawBuffer = CreateBufferWithData(Vertecies, 4);
            unsigned int IndexBuffer = CreateIndexBuffer(Shape, Vertecies);
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            break;
        }
        default:
            SW_ERROR("This shape is not supported");
            return false;
            break;
        }

        return true;
    }

    //------------------------------------------------------------


    //--------------------------Shaders Managment-----------------
    
    VFShaders OpenGLRenderer::ParseShaders(const std::string& FilePath)
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

    unsigned int OpenGLRenderer::CompileShader(unsigned int ShaderType, const std::string& SourceCode)
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

    unsigned int OpenGLRenderer::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
    {
        unsigned int Program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

        GLCall(glAttachShader(Program, vs));
        GLCall(glAttachShader(Program, fs));
        GLCall(glLinkProgram(Program));
        GLCall(glValidateProgram(Program));

        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));

        return Program;
    }
    //------------------------------------------------------------
}
