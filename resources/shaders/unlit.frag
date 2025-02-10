#version 430 core

//Inputs
layout(location=0) in vec2 i_textureCoordinates;

//Output
layout(location=0) out vec4 o_fragColor;

//Bindings
layout(location=0) uniform sampler2D u_textureAtlas;

void main()
{
	vec4 textureColor = texelFetch(u_textureAtlas, ivec2(i_textureCoordinates), 0);
	if(textureColor.a == 0.0) discard;

	o_fragColor = textureColor;
}