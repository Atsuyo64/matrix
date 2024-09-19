#version 330
in vec2 vPos;
in vec2 wPos;//window pos
out vec2 pos;

void main()
{
    gl_Position = vec4(vPos,0,1);
    pos = wPos;
}
