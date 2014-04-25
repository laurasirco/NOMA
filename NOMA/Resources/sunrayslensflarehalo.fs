#version 120

uniform sampler2D LowBlurredSunTexture, HighBlurredSunTexture, DirtTexture;

uniform float Dispersal, HaloWidth, Intensity;
uniform vec2 SunPosProj;
uniform vec3 Distortion;

vec3 texture2DDistorted(sampler2D Texture, vec2 TexCoord, vec2 Offset)
{
	return vec3(
		texture2D(Texture, TexCoord + Offset * Distortion.r).r,
		texture2D(Texture, TexCoord + Offset * Distortion.g).g,
		texture2D(Texture, TexCoord + Offset * Distortion.b).b
	);
}

void main()
{
	vec3 RadialBlur = vec3(0.0);
	vec2 TexCoord = gl_TexCoord[0].st;
	int RadialBlurSamples = 64;
	vec2 RadialBlurVector = (SunPosProj - TexCoord) / RadialBlurSamples;

	for(int i = 0; i < RadialBlurSamples; i++)
	{
		RadialBlur += texture2D(LowBlurredSunTexture, TexCoord).rgb;
		TexCoord += RadialBlurVector;
	}

	RadialBlur /= RadialBlurSamples;

	vec3 LensFlareHalo = vec3(0.0);
	TexCoord = 1.0 - gl_TexCoord[0].st;
	vec2 LensFlareVector = (vec2(0.5) - TexCoord) * Dispersal;
	vec2 LensFlareOffset = vec2(0.0);

	for(int i = 0; i < 5; i++)
	{
		LensFlareHalo += texture2DDistorted(HighBlurredSunTexture, TexCoord, LensFlareOffset).rgb;
		LensFlareOffset += LensFlareVector;
	}

	LensFlareHalo += texture2DDistorted(HighBlurredSunTexture, TexCoord, normalize(LensFlareVector) * HaloWidth);

	LensFlareHalo /= 6.0;

	vec4 color = vec4((texture2D(HighBlurredSunTexture, gl_TexCoord[0].st).rgb + (RadialBlur + LensFlareHalo) * texture2D(DirtTexture, gl_TexCoord[0].st).rgb) * Intensity, 1.0);

	gl_FragColor = color;

}
