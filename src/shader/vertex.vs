#version 330
in vec2 vPos;
in vec2 truePos;
//out vec3 color;
out vec2 pos;
//uniform float time;

void main()
{
	gl_Position = vec4(vPos,1.); //vec4(vPos*(pow(2.,time*.2)-1.),0.,1.);
	pos = truePos;
    //color = vCol;
}
