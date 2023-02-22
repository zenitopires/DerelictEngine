#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
out vec3 v_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
	v_Color = vec3(gl_Position);
}

#type fragment
#version 330 core

out vec4 color;
in vec3 u_Color;

void main()
{
	color = vec4(u_Color.r + 0.5, u_Color.g + 0.5, u_Color.b + 0.5, 1.0f);
}