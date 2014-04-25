#version 120

uniform sampler2D Texture;
uniform int Width;
uniform float odw;

void main()
{
	vec4 Color = vec4(0.0);
	int wp1 = Width + 1;
	float Sum = wp1 * wp1;
	
	for(int x = -Width; x <= Width; x++)
	{
		float width = (wp1 - abs(float(x)));
		Color += texture2D(Texture, vec2(gl_TexCoord[0].x + odw * x, gl_TexCoord[0].y)) * width/Sum;
	}
	
	gl_FragColor = Color;
}
