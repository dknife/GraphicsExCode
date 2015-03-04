uniform int mode;
uniform int imgW;
uniform int imgH;

// brightness
float brightness = 1.5;

uniform sampler2D texture;
varying vec2 coord;

// kernel data
const int MAXKERNELSIZE = 25;
int kernelSize;
vec2 offset[MAXKERNELSIZE];
float filter[MAXKERNELSIZE];

void ApplyKernel(int kSize) {
    vec4 col = vec4(0.0);
    for (int i=0; i<kSize; i++) {
        col += texture2D(texture, coord+offset[i])*filter[i];
    }
    gl_FragColor = col;
}

void prepare5X5OffsetMatrix(void) {
    kernelSize = 25;
    float S = 1.0/float(imgW);
    float T = 1.0/float(imgH);
    offset[0]  = vec2(-2.0*S,-2.0*T); offset[1]  = vec2(-S,-2.0*T); offset[2]  = vec2(0,-2.0*T); offset[3]  = vec2(S,-2.0*T); offset[4]  = vec2(S,-2.0*T);
    offset[5]  = vec2(-2.0*S,    -T); offset[6]  = vec2(-S,    -T); offset[7]  = vec2(0,    -T); offset[8]  = vec2(S,    -T); offset[9]  = vec2(S,    -T);
    offset[10] = vec2(-2.0*S,     0); offset[11] = vec2(-S,     0); offset[12] = vec2(0,     0); offset[13] = vec2(S,     0); offset[14] = vec2(S,     0);
    offset[15] = vec2(-2.0*S,     T); offset[16] = vec2(-S,     T); offset[17] = vec2(0,     T); offset[18] = vec2(S,     T); offset[19] = vec2(S,     T);
    offset[20] = vec2(-2.0*S, 2.0*T); offset[21] = vec2(-S, 2.0*T); offset[22] = vec2(0, 2.0*T); offset[23] = vec2(S, 2.0*T); offset[24] = vec2(S, 2.0*T);
}

void prepare3x3OffsetMatrix(void) {
    kernelSize = 9;
    float S = 1.0/float(imgW);
    float T = 1.0/float(imgH);
    offset[0] = vec2(-S,-T);offset[1] = vec2(0,-T);offset[2] = vec2(S,-T);
    offset[3] = vec2(-S, 0);offset[4] = vec2(0, 0);offset[5] = vec2(S, 0);
    offset[6] = vec2(-S, T);offset[7] = vec2(0, T);offset[8] = vec2(S, T);
}


void main()
{
    
    
    gl_FragColor = texture2D(texture, coord);
    if(mode==1) { // brighten
        gl_FragColor = gl_FragColor * brightness;
    }
    if (mode==2) { // contrast enhancement
        gl_FragColor = mix(vec4(0.5, 0.5, 0.5, 1.0), gl_FragColor, 1.5);
    }
    if (mode==3) { // saturation
        vec4 lumCoeff = vec4(0.2125, 0.7154, 0.0721, 0.0);
        vec4 intensity = vec4(dot(gl_FragColor, lumCoeff));
        gl_FragColor = mix(intensity, gl_FragColor, 2.0);
    }
    if (mode==4) { // smoothing
        kernelSize = 9;
        prepare3x3OffsetMatrix();
        for (int i=0; i<kernelSize; i++) {
            filter[i] = 1.0 / 9.0;
        }
        ApplyKernel(9);
    }
    if (mode==5) { // noise reduction
        prepare5X5OffsetMatrix();
        
        filter[0]  = 1.0; filter[1]  =  4.0; filter[2]  =  7.0; filter[3]  =  4.0; filter[4]  = 1.0;
        filter[5]  = 4.0; filter[6]  = 16.0; filter[7]  = 26.0; filter[8]  = 16.0; filter[9]  = 4.0;
        filter[10] = 7.0; filter[11] = 26.0; filter[12] = 41.0; filter[13] = 26.0; filter[14] = 7.0;
        filter[15] = 4.0; filter[16] = 16.0; filter[17] = 26.0; filter[18] = 16.0; filter[19] = 4.0;
        filter[20] = 1.0; filter[21] =  4.0; filter[22] =  7.0; filter[23] =  4.0; filter[24] = 1.0;
        for (int i=0; i<kernelSize; i++) {
            filter[i] /= 273.0;
        }
        ApplyKernel(kernelSize);
    }
    if (mode==6) { // Laplacian - edge detection
        prepare3x3OffsetMatrix();
        
        filter[0] =  0.0; filter[1] =  1.0; filter[2] =  0.0;
        filter[3] =  1.0; filter[4] = -4.0; filter[5] =  1.0;
        filter[6] =  0.0; filter[7] =  1.0; filter[8] =  0.0;
        
        ApplyKernel(kernelSize);
    }
    if (mode==7) { // Negative Laplacian - edge detection
        prepare3x3OffsetMatrix();
        
        filter[0] =  0.0; filter[1] = -1.0; filter[2] =  0.0;
        filter[3] = -1.0; filter[4] =  4.0; filter[5] = -1.0;
        filter[6] =  0.0; filter[7] = -1.0; filter[8] =  0.0;
        
        ApplyKernel(kernelSize);
    }
    if (mode==8) { // Negative Laplacian - edge detection
        prepare3x3OffsetMatrix();
        
        filter[0] =  0.0; filter[1] = -1.0; filter[2] =  0.0; 
        filter[3] = -1.0; filter[4] =  4.0; filter[5] = -1.0; 
        filter[6] =  0.0; filter[7] = -1.0; filter[8] =  0.0;  
        
        ApplyKernel(kernelSize);
        gl_FragColor = gl_FragColor * 0.5 + texture2D(texture, coord);
    }
}