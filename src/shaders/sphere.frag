#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 normal;
// Imports the color from the Vertex Shader
in vec3 color;


// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;
// Gets the alpha value of the cube from the main function
uniform float alpha;


void main()
{
	// outputs final color
	FragColor = vec4(1.0f);
}