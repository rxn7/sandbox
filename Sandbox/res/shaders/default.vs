#version 410

#define CHUNK_SIZE 16

const float FOG_DENSITY = 0.015;
const float FOG_GRADIENT = 1.5;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 f_texCoord;
out float f_visibility;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform int coordX;
uniform int coordZ;

void main(){
	vec4 realPos = vec4(position.x + (coordX * CHUNK_SIZE), position.y, position.z + (coordZ * CHUNK_SIZE), 1.0);
	
	gl_Position = projectionMatrix * viewMatrix * realPos;
	f_texCoord = texCoord;
	
	vec4 positionRelativeToCam = viewMatrix * realPos;
	
	float distanceToCamera = length(positionRelativeToCam.xyz);
	f_visibility = exp(-pow((distanceToCamera*FOG_DENSITY), FOG_GRADIENT));
	f_visibility = clamp(f_visibility, 0.0, 1.0);
}