#shader vertex
#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
out vec3 v_Position;
out vec3 v_Color;

uniform mat4 m_MVP;

void main()
{
   v_Position = position;
   v_Color = color;
   gl_Position = m_MVP * vec4(position, 1.0);
};

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;
in vec3 v_Color;
in vec3 v_Position;

void main()
{
	color = vec4(v_Color, 1.0);
};
