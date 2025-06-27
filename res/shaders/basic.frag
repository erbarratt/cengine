#version 410 core

layout (location = 0) out vec4 color;

in vec2 v_textCoord;
uniform sampler2D u_texture;

void main()
{
    vec4 textColor = texture(u_texture, v_textCoord);
    color = textColor;
}