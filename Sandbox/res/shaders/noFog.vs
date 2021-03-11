#version 410

#define CHUNK_SIZE 16

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 f_texCoord;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform int coordX;
uniform int coordZ;

void main(){
	vec4 realPos = vec4(position.x + (coordX * CHUNK_SIZE), position.y, position.z + (coordZ * CHUNK_SIZE), 1.0);
	
	gl_Position = projectionMatrix * viewMatrix * realPos;
	f_texCoord = texCoord;
}