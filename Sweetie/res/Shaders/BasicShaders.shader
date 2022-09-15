#shader vertex
#version 410 core

layout(location = 0) in vec2 position;
out vec2 v_Position;
void main()
{
   v_Position = position;
   gl_Position = vec4(position,1.0,1.0); 
};

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;
in vec2 v_Position;

void main()
{
	color = vec4(v_Position * 0.5 + 0.5, v_Position.y,1.0);
};
