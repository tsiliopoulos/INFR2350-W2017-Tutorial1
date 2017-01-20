// This is the OLD way of doing shaders

#version 120

uniform vec4 u_lightPos;
uniform vec4 u_colour;

// Fragment Shader Inputs
varying	vec3 normal;
varying	vec2 texCoord;
varying	vec4 colour;
varying vec3 posEye;

void main()
{
	vec3 L = normalize(u_lightPos.xyz - posEye);
	vec3 N = normalize(normal);

	float diffuse = max(0.0, dot(N, L));
	gl_FragColor = vec4(vec3(0.5, 0.5, 0.5) * (diffuse * 0.8) + u_colour.rgb, 1.0);
}