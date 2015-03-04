uniform sampler2D ColorMap;
uniform vec3 lightDir;

varying vec2 coord;
varying vec3 norm;

void main(){
    float NdotL = max(dot(norm, normalize(lightDir)), 0.0);
    vec4 diffuse = texture2D(ColorMap, coord.xy);
    
    gl_FragColor = diffuse*NdotL;
}