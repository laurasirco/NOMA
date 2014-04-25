#version 120

uniform sampler2D Texture;
uniform sampler2D/*Shadow*/ ShadowMap;
uniform sampler2D NormalsMap;
uniform int CustomNormal;

varying vec4 ShadowMapTexCoord;
varying vec3 Normal, LightDirection;
varying float fogFactor;
varying vec3 sunDir;

void main()
{

    vec4 ambient = vec4(0.25, 0.25, 0.25, 1.0);
    vec4 diffuse = vec4(0.75, 0.75, 0.75, 1.0);
    float linearAttenuation = 0.0;
    float quadraticAttenuation = 0.0;
    float constantAttenuation = 1.0;
    vec4 finalColor = gl_Color;

    float LightDistance2 = dot(LightDirection, LightDirection);
    float LightDistance = sqrt(LightDistance2);

    //vec3 bump = texture2D(NormalsMap, gl_TexCoord[0].st);

    //Normal.xyz = bump.rgb * 2.0 - 1.0;
    
    float NdotLD = max(dot(normalize(Normal), LightDirection / LightDistance), 0.0);
    
    float Attenuation = gl_LightSource[0].constantAttenuation;
    Attenuation += gl_LightSource[0].linearAttenuation * LightDistance;
    Attenuation += gl_LightSource[0].quadraticAttenuation * LightDistance2;
    
    //NdotLD *= ∑(ShadowMap, ShadowMapTexCoord).r;
    
    /*if(ShadowMapTexCoord.w > 0.0)
    {
        vec3 ShadowMapTexCoordProj = ShadowMapTexCoord.xyz / ShadowMapTexCoord.w;
        
        if(ShadowMapTexCoordProj.x >= 0.0 && ShadowMapTexCoordProj.x < 1.0 &&
           ShadowMapTexCoordProj.y >= 0.0 && ShadowMapTexCoordProj.y < 1.0 &&
           ShadowMapTexCoordProj.z >= 0.0 && ShadowMapTexCoordProj.z < 1.0)
        {            
            if(texture2D(ShadowMap, ShadowMapTexCoordProj.xy).r <= ShadowMapTexCoordProj.z)
            {
                NdotLD = 0.0;
                gl_FragColor = vec4(0.0,0.0,1.0,1.0);

            }
        }

        else{
            gl_FragColor = vec4(0.0,1.0,0.0,1.0);
        }
    }*/

    float density = 0.0004;
    const float LOG2 = 1.442696;
    vec4 fog_color = vec4(0.5, 0.6, 0.7, 0.0);

    float z = gl_FragCoord.z / gl_FragCoord.w;
    float fogFactor = exp2(-density * density * z * z * LOG2);
    fogFactor = clamp(fogFactor, 0.0, 1.0);

    /*vec3 camDir = gl_FragCoord.xyz;
    //float sunAmount = max(dot(camDir, sunDir), 0.0);

    vec4  fogColor  = mix( vec3(0.5,0.6,0.7,0.0), // bluish
                           vec3(1.0,0.9,0.7,0.0), // yellowish
                           0.5 );*/
    
    finalColor *= texture2D(Texture, gl_TexCoord[0].st);
    finalColor.rgb *= (gl_LightSource[0].ambient.rgb + gl_LightSource[0].diffuse.rgb * NdotLD) / Attenuation;
    gl_FragColor = mix(fog_color, finalColor, fogFactor);
    gl_FragColor.a = 1.0;
}