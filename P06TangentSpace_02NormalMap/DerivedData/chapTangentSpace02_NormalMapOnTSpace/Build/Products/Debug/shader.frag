uniform vec3 lightDir;
uniform sampler2D ColorMap, NormalMap;
varying vec2 coord;
varying vec3 T, B, N;

void main(){
    vec3 nMap = 2.0*texture2D(NormalMap, 2.0*coord.xy).xyz-1.0;
    
    vec3 light;
    light.x = dot(T, lightDir);
    light.y = dot(B, lightDir);
    light.z = dot(N, lightDir);
    float NdotL = max(dot(nMap, normalize(light)), 0.0);
    vec4 diffuse = texture2D(ColorMap, 2.0*coord.xy);
    gl_FragColor = diffuse*NdotL;
}