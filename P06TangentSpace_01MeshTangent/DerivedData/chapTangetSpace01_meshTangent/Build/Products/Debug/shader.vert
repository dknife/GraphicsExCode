varying vec3 norm;
varying vec2 coord;
void main()
{
    norm  = gl_NormalMatrix * gl_Normal;
    coord = gl_MultiTexCoord0.xy;
    
    gl_Position = ftransform();
    
}