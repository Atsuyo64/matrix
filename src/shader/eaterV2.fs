#version 330
in vec2 pos;
uniform float time;
out vec4 color;

uint lowbias32(uint x)
{
    x ^= x >> 16;
    x *= 0x7feb352dU;
    x ^= x >> 15;
    x *= 0x846ca68bU;
    x ^= x >> 16;
    return x;
}

float random(inout uint rng)
{
    rng = lowbias32(rng);
    return rng/4294967295.0;
}

float gauss(inout uint rng)
{
    float theta = 2.0*3.1415926536*random(rng);
    float rho = sqrt(-2.0*log(random(rng)));
    return rho * cos(theta);
}

void main()
{
    float duration = 5.0;
    float slope = duration/1400.0;
    float maxOffset = 1.0;//slope*100.0;
    uint rng = uint(pos.x+1533.0+(pos.y+700.0)*3066.0);
    float threshold = slope*(700.0-pos.y) + maxOffset*gauss(rng)+5.0;//random(rng);
    rng+=uint(mod(time*10000000.0,100000.0));
    if(time<threshold) discard;
    if(time-threshold<maxOffset) color=vec4(0.5*random(rng),100*random(rng),0.5*random(rng),1);
    else color = vec4(0,0,0,1);
}
