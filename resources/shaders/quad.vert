#version 430 core

void main()
{
	//Defining vertices on the GPU because we are in 2D
	vec2 vertices[6] =
	{
		vec2(-0.5, -0.5),
		vec2( 0.5,  0.5),
		vec2(-0.5,  0.5),
		vec2(-0.5, -0.5),
		vec2( 0.5, -0.5),
		vec2( 0.5,  0.5),
	};

	gl_Position = vec4(vertices[gl_VertexID], 1.0, 1.0);
}