#version 120

uniform mat4x4 ShadowMatrix;
uniform mat4x4 ModelViewInverse;
uniform vec3 SunPosition;

varying vec4 ShadowMapTexCoord;
varying vec3 Normal, LightDirection;
varying vec3 sunDir;

varying float fogFactor;

void main()
{
	
    vec4 Position = gl_ModelViewMatrix * gl_Vertex;
    
    ShadowMapTexCoord = ShadowMatrix * gl_Vertex;

    Normal = gl_NormalMatrix * gl_Normal;

    LightDirection = gl_LightSource[0].position.xyz - Position.xyz;
    gl_FrontColor = gl_Color;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = gl_ProjectionMatrix * Position;

    //vec3 Sun = SunPosition * ftransform();
    //sunDir = normalize(SunPosition * ftransform());

}
