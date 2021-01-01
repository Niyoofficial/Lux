#version 330
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec3 v_Position;

void main()
{
	v_Color = a_Color;
	v_Position = vec3(u_ViewProjection * vec4(a_Position, 1.f));
	gl_Position = u_ViewProjection * vec4(a_Position, 1.f);
}
