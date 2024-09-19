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
    float maxOffset = 0.5;//slope*100.0;
    float sizeOfPixels = 5.0;
    float maxStartOffset = 5.0;

    vec2 pos2 = pos/sizeOfPixels;
    pos2 -= fract(pos2);
    pos2 *= sizeOfPixels;

    uint rngXY = uint(pos2.x+1533.0+(pos2.y+700.0)*3066.0);
    uint rngX  = uint(pos2.x+1533.0)*23u;

    float threshold = slope*(700.0-pos2.y) + maxOffset*gauss(rngXY)+3.0+maxStartOffset*random(rngX);
    //rng+=uint(mod(time*10000000.0,100000.0));
    if(time<threshold) discard;
    if(time-threshold<maxOffset) color=vec4(0.5*random(rngXY),100*random(rngXY),0.5*random(rngXY),1);
    else color = vec4(0,0,0,1);
}
