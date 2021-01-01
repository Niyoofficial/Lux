#version 330
layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec3 v_Position;

void main()
{
	color = vec4(v_Position * 0.5f + 0.5f, 1.f);
}
