#version 120

// Used for shadow lookup
varying vec4 ShadowCoord;

varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec2 texture_coordinate;

void main()
{
     	ShadowCoord = gl_TextureMatrix[7] * gl_Vertex;
  
		gl_Position = ftransform();

		gl_FrontColor = gl_Color;
		
		normal = gl_NormalMatrix * gl_Normal;
		
		vec4 vertex_in_modelview_space = gl_ModelViewMatrix * gl_Vertex;
		
		vertex_to_light_vector = vec3(gl_LightSource[0].position -vertex_in_modelview_space);
		
		texture_coordinate = vec2(gl_MultiTexCoord0);
}

