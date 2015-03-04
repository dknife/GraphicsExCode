varying vec2 coord;
void main()
{
    coord = gl_MultiTexCoord0.xy;
    gl_Position = ftransform();
    
}