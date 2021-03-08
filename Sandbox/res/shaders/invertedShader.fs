#version 410

uniform sampler2D diffuse;

in vec2 f_texCoord;

void main(){
	vec4 texColor = texture2D(diffuse, f_texCoord);
	gl_FragColor = vec4(1.0 - texColor.r, 1.0 - texColor.g, 1.0 - texColor.b, 1.0);
}