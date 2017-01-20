// This is the OLD way of doing shaders

#version 120

// Uniforms
// Constants throughout the entire pipeline
// These values are sent from C++ (glSendUniform*)
uniform mat4 u_mvp;
uniform mat4 u_mv;
uniform vec4 u_colour;

varying	vec3 normal;
varying	vec2 texCoord;
varying	vec4 colour;
varying vec3 posEye;

void main() 
{
	texCoord = gl_TexCoord[0].xy;
	colour = u_colour;
	normal = (u_mv * vec4(gl_Normal, 0.0)).xyz;
	posEye = (u_mv * gl_Vertex).xyz;

	gl_Position = u_mvp * gl_Vertex;
}