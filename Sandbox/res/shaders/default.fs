#version 410

uniform sampler2D diffuse;

in vec2 f_texCoord;
in float f_visibility;

const vec3 SKY_COLOR = vec3(0.5, 0.5, 0.5);

void main(){
	gl_FragColor = vec4(texture2D(diffuse, f_texCoord));
	gl_FragColor = mix(vec4(SKY_COLOR, 1.0), gl_FragColor, f_visibility);
}