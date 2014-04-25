#version 120

uniform vec2 resolution;
uniform sampler2D texture;
uniform sampler2D depth;

const float blurclamp = 2.0;  // max blur amount
const float bias = 0.003; //aperture - bigger values for shallower depth of field
const float focus = 0.01;  // this value comes from ReadDepth script.

float LinearizeDepth(vec2 uv)
{
  float n = 1.0; // camera z near
  float f = 2000.0; // camera z far
  float z = texture2D(depth, uv).x;
  return (2.0 * n) / (f + n - z * (f - n));	
}

void main(void)
{

	vec2 uv = gl_FragCoord.xy / resolution.xy;
		
	float d = LinearizeDepth(uv);

	float aspectratio = resolution.x/resolution.y;
    vec2 aspectcorrect = vec2(1.0,aspectratio);
       
    float factor = ( d - focus );
         
    vec2 dofblur = vec2 (clamp( factor * bias, -blurclamp, blurclamp ));

	vec4 col = vec4(0.0);
       
    col += texture2D(texture, uv);
    col += texture2D(texture, uv + (vec2( 0.0,0.4 )*aspectcorrect) * dofblur);
    col += texture2D(texture, uv + (vec2( 0.15,0.37 )*aspectcorrect) * dofblur);
    col += texture2D(texture, uv + (vec2( 0.29,0.29 )*aspectcorrect) * dofblur);
    col += texture2D(texture, uv + (vec2( -0.37,0.15 )*aspectcorrect) * dofblur);       
    col += texture2D(texture, uv + (vec2( 0.4,0.0 )*aspectcorrect) * dofblur);   
    col += texture2D(texture, uv + (vec2( 0.37,-0.15 )*aspectcorrect) * dofblur);       
    col += texture2D(texture, uv + (vec2( 0.29,-0.29 )*aspectcorrect) * dofblur);       
    col += texture2D(texture, uv + (vec2( -0.15,-0.37 )*aspectcorrect) * dofblur);
    col += texture2D(texture, uv + (vec2( 0.0,-0.4 )*aspectcorrect) * dofblur); 
    col += texture2D(texture, uv + (vec2( -0.15,0.37 )*aspectcorrect) * dofblur);
    col += texture2D(texture, uv + (vec2( -0.29,0.29 )*aspectcorrect) * dofblur);
    col += texture2D(texture, uv + (vec2( 0.37,0.15 )*aspectcorrect) * dofblur); 
    col += texture2D(texture, uv + (vec2( -0.4,0.0 )*aspectcorrect) * dofblur); 
    col += texture2D(texture, uv + (vec2( -0.37,-0.15 )*aspectcorrect) * dofblur);       
    col += texture2D(texture, uv + (vec2( -0.29,-0.29 )*aspectcorrect) * dofblur);       
    col += texture2D(texture, uv + (vec2( 0.15,-0.37 )*aspectcorrect) * dofblur);
   
    /*col += texture2D(texture, uv + (vec2( 0.15,0.37 )*aspectcorrect) * dofblur*0.9);
    col += texture2D(texture, uv + (vec2( -0.37,0.15 )*aspectcorrect) * dofblur*0.9);           
    col += texture2D(texture, uv + (vec2( 0.37,-0.15 )*aspectcorrect) * dofblur*0.9);           
    col += texture2D(texture, uv + (vec2( -0.15,-0.37 )*aspectcorrect) * dofblur*0.9);
    col += texture2D(texture, uv + (vec2( -0.15,0.37 )*aspectcorrect) * dofblur*0.9);
    col += texture2D(texture, uv + (vec2( 0.37,0.15 )*aspectcorrect) * dofblur*0.9);            
    col += texture2D(texture, uv + (vec2( -0.37,-0.15 )*aspectcorrect) * dofblur*0.9);   
    col += texture2D(texture, uv + (vec2( 0.15,-0.37 )*aspectcorrect) * dofblur*0.9);   
   
    col += texture2D(texture, uv + (vec2( 0.29,0.29 )*aspectcorrect) * dofblur*0.7);
    col += texture2D(texture, uv + (vec2( 0.4,0.0 )*aspectcorrect) * dofblur*0.7);       
    col += texture2D(texture, uv + (vec2( 0.29,-0.29 )*aspectcorrect) * dofblur*0.7);   
    col += texture2D(texture, uv + (vec2( 0.0,-0.4 )*aspectcorrect) * dofblur*0.7);     
    col += texture2D(texture, uv + (vec2( -0.29,0.29 )*aspectcorrect) * dofblur*0.7);
    col += texture2D(texture, uv + (vec2( -0.4,0.0 )*aspectcorrect) * dofblur*0.7);     
    col += texture2D(texture, uv + (vec2( -0.29,-0.29 )*aspectcorrect) * dofblur*0.7);   
    col += texture2D(texture, uv + (vec2( 0.0,0.4 )*aspectcorrect) * dofblur*0.7);
                     
    col += texture2D(texture, uv + (vec2( 0.29,0.29 )*aspectcorrect) * dofblur*0.4);
    col += texture2D(texture, uv + (vec2( 0.4,0.0 )*aspectcorrect) * dofblur*0.4);       
    col += texture2D(texture, uv + (vec2( 0.29,-0.29 )*aspectcorrect) * dofblur*0.4);   
    col += texture2D(texture, uv + (vec2( 0.0,-0.4 )*aspectcorrect) * dofblur*0.4);     
    col += texture2D(texture, uv + (vec2( -0.29,0.29 )*aspectcorrect) * dofblur*0.4);
    col += texture2D(texture, uv + (vec2( -0.4,0.0 )*aspectcorrect) * dofblur*0.4);     
    col += texture2D(texture, uv + (vec2( -0.29,-0.29 )*aspectcorrect) * dofblur*0.4);   
    col += texture2D(texture, uv + (vec2( 0.0,0.4 )*aspectcorrect) * dofblur*0.4);*/       

    gl_FragColor = col/16.0;

}