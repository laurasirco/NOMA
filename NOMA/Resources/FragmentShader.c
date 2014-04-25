#version 120

uniform sampler2D ShadowMap;
uniform sampler2D Texture;

varying vec4 ShadowCoord;
varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec2 texture_coordinate;

uniform int Texturing;

void main()
{	
	const vec4 AmbientColor = vec4(0.7, 0.7, 0.7, 1.0);
	const vec4 DiffuseColor = vec4(0.5, 0.5, 0.5, 1.0);
	
	vec3 normalized_normal = normalize(normal);
	vec3 normalized_vertex_to_light_vector = normalize(vertex_to_light_vector);
	
	float DiffuseTerm = clamp(dot(normal, vertex_to_light_vector), 0.0, 1.0);

	
	vec4 shadowCoordinateWdivide = ShadowCoord / ShadowCoord.w ;
	
	// Used to lower moiré pattern and self-shadowing
	shadowCoordinateWdivide.z += 0.0005;

	float distanceFromLight = texture2D(ShadowMap,shadowCoordinateWdivide.st).z;
	
	
 	float shadow = 1.0;
 	if (ShadowCoord.w > 0.0)
 		shadow = distanceFromLight < shadowCoordinateWdivide.z ? 0.5 : 1.0 ;
		

	gl_FragColor = texture2D(Texture, texture_coordinate) * shadow * (AmbientColor + DiffuseColor * DiffuseTerm);
	gl_FragColor.a = 1.0;
	//if(Texturing == 1)
	//	gl_FragColor *= texture2D(Texture, texture_coordinate);

}

