
#version 450 core

in vec4 frag_color;
out vec4 color;

void main()
{
    //color = vec4(1.0, 0.0, 0.0, 1.0);
		color = frag_color;
}
