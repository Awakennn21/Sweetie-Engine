#shader vertex
#version 410 core

layout(location = 0) in vec3 position;
out vec3 v_Position;
void main()
{
   v_Position = position;
   gl_Position = vec4(position,1.0); 
};

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;
in vec3 v_Position;

void main()
{
	color = vec4(v_Position * 0.5 + 0.5,1.0);
};
