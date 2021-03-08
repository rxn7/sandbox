#version 410

uniform sampler2D diffuse;

in vec2 f_texCoord;

void main(){
	vec4 texColor = texture2D(diffuse, f_texCoord);
	gl_FragColor = vec4(texColor.r, texColor.g, texColor.b, 0.75);
}