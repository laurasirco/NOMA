// Atmospheric scattering fragment shader
// Author: Sean O'Neil
// Copyright (c) 2004 Sean O'Neil

#version 120

#define M_PI 3.1415926535897932384626433832795

uniform vec3 v3LightPos;
uniform float g;
uniform float g2;
uniform vec2 resolution;
uniform float globalTime;
uniform float cameraRotation;

varying vec3 v3Direction;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void main (void)
{
	float fCos = dot(v3LightPos, v3Direction) / length(v3Direction);
	float fRayleighPhase = 1.0 + fCos * fCos;
	float fMiePhase = (1.0 - g2) / (2.0 + g2) * (1.0 + fCos * fCos) / pow(1.0 + g2 - 2.0 * g * fCos, 1.5);

	float size = 30.0;
	float prob = 0.99;
	
	vec2 pos = floor(1.0 / size * gl_FragCoord.xy);
	
	float color = 0.0;
	float starValue = rand(pos);

	float min = -0.15;
	float max = 0.15;

	float mixValue = ((v3LightPos.y - min) * (1.0 - 0.0)) / ((max - min) + 0.0);
	mixValue = clamp(mixValue, 0, 1);

	if (starValue > prob) //Big star
	{
		vec2 center = size * pos + vec2(size, size) * 0.5;
		
		float t = 0.9 + 0.2 * sin(globalTime + (starValue - prob) / (1.0 - prob) * 45.0);
				
		color = 1.0 - distance(gl_FragCoord.xy, center) / (0.5 * size);
		color = color * t / (abs(gl_FragCoord.y - center.y)) * t / (abs(gl_FragCoord.x - center.x));
	}
	else if (rand(gl_FragCoord.xy / resolution.xy) > 0.998) //Small star
	{
		float r = rand(gl_FragCoord.xy);
		color = r * (0.25 * sin(globalTime * (r * 5.0) + 720.0 * r) + 0.75);
	}

	vec4 nightColor = vec4(vec3(color), 1.0);
	vec4 dayColor = vec4(1.0 - exp(-1.5 * (fRayleighPhase * gl_Color.rgb + fMiePhase * gl_SecondaryColor.rgb)), 1.0);

	//MIX BOTH COLORS

	gl_FragColor = mix(nightColor, dayColor, mixValue);

}