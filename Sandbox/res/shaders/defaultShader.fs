#version 410

uniform sampler2D diffuse;

in vec2 f_texCoord;

void main(){
	gl_FragColor = texture2D(diffuse, f_texCoord);
}