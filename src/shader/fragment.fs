#version 330
in vec2 pos;
in float time;
//in vec3 pos;

out vec4 m_color;
void main()
{
    float dst = length(pos);
    float threshold = pow(2.,time*.02)-1.;
    //m_color = vec4(dst,dst,dst,1.);
    if(dst>threshold)
        m_color=vec4(1,0,0,1);//discard;
    if(threshold-dst<=.02)
        m_color = vec4(0.839,0.11,0.745,.5);
    else
        m_color = vec4(0,0,0,1);
    //m_color = vec4(color,1.);
}

