#version 330
in vec2 pos;
uniform float time;

out vec4 color;

void main()
{
    float dst = length(pos);
    float threshold = pow(2.,time)-1.;
    //color = vec4(dst,0*threshold,0,1);
    //return;
    if(dst>threshold)
        discard;//color = vec4(1,0,0,.1);
    else if(threshold-dst<3.)
        color = vec4(0,1,1,.5);
    else
        color = vec4(0,0,0,1);
}
