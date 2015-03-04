attribute vec3 Tangent;
attribute vec3 Binormal;

varying vec3 T, B, N;
varying vec2 coord;
void main()
{
    N = gl_Normal;
    T = Tangent;
    B = Binormal;
    
    coord = gl_MultiTexCoord0.xy;
    
    gl_Position = ftransform();
    
}