#version 120

uniform vec2 resolution;
uniform sampler2D texture;

void main(void)
{
	float 	centerBuffer 		= 0.15,
			vignetteStrength 	= 0.9,
			aberrationStrength 	= 1.55;
	
	float 	chrDist,
			vigDist;
	
	vec2 uv = gl_FragCoord.xy / resolution.xy;
		
	
	//calculate how far each pixel is from the center of the screen
	vec2 vecDist = uv - ( 0.5 , 0.5 );
	chrDist = vigDist = length( vecDist );
	
	//modify the distance from the center, so that only the edges are affected
	chrDist	-= centerBuffer;
	if( chrDist < 0.0 ) chrDist = 0.0;
	
	//distort the UVs
	vec2 uvR = uv * ( 1.0 + chrDist * 0.02 * aberrationStrength ),
		 uvB = uv * ( 1.0 - chrDist * 0.02 * aberrationStrength );
	
	//get the individual channels using the modified UVs
	vec4 c;
	
	c.x = texture2D( texture , uvR ).x; 
	c.y = texture2D( texture , uv ).y; 
	c.z = texture2D( texture , uvB ).z;

	//apply vignette
	c *= 1.0 - vigDist* vignetteStrength;
	c.w = texture2D( texture , uv ).w; 

	gl_FragColor = c;

    //gl_FragColor.a = 1.0;
}