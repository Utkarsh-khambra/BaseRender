#shader vertex
#version 330 core

layout(location = 0)in vec3 position;
// in vec3 normal;

layout(std140) uniform Matrices
{
    mat4 Camera;
};
// uniform    mat4 Camera;
// uniform mat4 Model;
// uniform vec3 LightPos;
// uniform vec3 EyeDir;
// uniform float Ka;
// uniform float Kd;
// uniform float Ks;
// uniform float IntensitySource;
// uniform float IntensityAmbient;
// uniform float N;

// out float factor;

void main()
{
    gl_Position = Camera*vec4(position, 1);
    // vec3 lightDir = normalize(LightPos - position);
    // vec3 halfWayVector = normalize(lightDir+EyeDir);
    // float cosTheta = clamp(dot(normal,lightDir),0.0,1.0);
    // float cosAlpha = clamp(dot(normal,halfWayVector),0.0,1.0);
    // factor = Ka*IntensityAmbient + Kd*IntensitySource*cosTheta + Ks*IntensitySource*pow(cosAlpha,N);
}

#shader fragment
#version 330 core

// in float factor;
out vec3 outColor;

void main()
{
    outColor = vec3(1,1,1);/*vec3(1,1,1)*factor*vec3(1,0.2,0.4);*/
}
