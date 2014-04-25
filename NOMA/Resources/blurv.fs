#version 120

uniform sampler2D Texture;
uniform int Width;
uniform float odh;

void main()
{
	vec4 Color = vec4(0.0);
	int wp1 = Width + 1;
	float Sum = wp1 * wp1;
	
	for(int y = -Width; y <= Width; y++)
	{
		float width = (wp1 - abs(float(y)));
		Color += texture2D(Texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y + odh * y)) * width/Sum;
	}
	
	gl_FragColor = Color;
}
