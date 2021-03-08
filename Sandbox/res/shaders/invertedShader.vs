#version 410

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 f_texCoord;
uniform mat4 transform;

void main(){
	gl_Position = transform * vec4(position, 1.0);
	f_texCoord = texCoord;
}