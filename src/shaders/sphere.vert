#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;

out vec3 crntPos;
out vec3 normal;    
out vec3 color;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

void main()
{
    crntPos = vec3(modelMatrix * vec4(aPos, 1.0));
    normal = vec3(normalMatrix * vec4(aNormal, 1.0));
    color = aColor;

    // Outputs the positions/coordinates of all vertices
    gl_Position = camMatrix * vec4(crntPos, 1.0);

}