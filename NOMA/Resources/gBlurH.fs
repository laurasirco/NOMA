uniform sampler2D RTScene; // the texture with the scene you want to blur
varying vec2 vTexCoord;
 
const float blurSize = 1.0/300.0; // I've chosen this size because this will result in that every step will be one pixel wide if the RTScene texture is of size 512x512
 
void main(void)
{
   vec4 sum = vec4(0.0);
 
   sum += texture2D(RTScene, vec2(vTexCoord.x - 7.0*blurSize, vTexCoord.y)) * 0.005;
   sum += texture2D(RTScene, vec2(vTexCoord.x - 6.0*blurSize, vTexCoord.y)) * 0.01;
   sum += texture2D(RTScene, vec2(vTexCoord.x - 5.0*blurSize, vTexCoord.y)) * 0.02;
   sum += texture2D(RTScene, vec2(vTexCoord.x - 4.0*blurSize, vTexCoord.y)) * 0.05;
   sum += texture2D(RTScene, vec2(vTexCoord.x - 3.0*blurSize, vTexCoord.y)) * 0.09;
   sum += texture2D(RTScene, vec2(vTexCoord.x - 2.0*blurSize, vTexCoord.y)) * 0.12;
   sum += texture2D(RTScene, vec2(vTexCoord.x - blurSize, vTexCoord.y)) * 0.15;
   sum += texture2D(RTScene, vec2(vTexCoord.x, vTexCoord.y)) * 0.16;
   sum += texture2D(RTScene, vec2(vTexCoord.x + blurSize, vTexCoord.y)) * 0.15;
   sum += texture2D(RTScene, vec2(vTexCoord.x + 2.0*blurSize, vTexCoord.y)) * 0.12;
   sum += texture2D(RTScene, vec2(vTexCoord.x + 3.0*blurSize, vTexCoord.y)) * 0.09;
   sum += texture2D(RTScene, vec2(vTexCoord.x + 4.0*blurSize, vTexCoord.y)) * 0.05;
   sum += texture2D(RTScene, vec2(vTexCoord.x + 5.0*blurSize, vTexCoord.y)) * 0.02;
   sum += texture2D(RTScene, vec2(vTexCoord.x + 6.0*blurSize, vTexCoord.y)) * 0.01;
   sum += texture2D(RTScene, vec2(vTexCoord.x + 7.0*blurSize, vTexCoord.y)) * 0.005;
 
   gl_FragColor = sum;
}