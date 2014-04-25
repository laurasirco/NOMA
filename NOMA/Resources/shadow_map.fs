#version 400

// Declare any uniforms needed for the Phong shading model
uniform sampler2DShadow ShadowMap;
in vec3 Position;
in vec3 Normal;
in vec4 ShadowCoord;
layout (location = 0) out vec4 FragColor;

vec3 phongModelDiffAndSpec(){
	
}

subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;
subroutine (RenderPassType)

void shadeWithShadow()
{
  vec3 ambient = ...;// compute ambient component here
  vec3 diffAndSpec = phongModelDiffAndSpec();
   
  // Do the shadow-map look-up
  float shadow = textureProj(ShadowMap, ShadowCoord);
  
  // If the fragment is in shadow, use ambient light only.
  FragColor = vec4(diffAndSpec * shadow + ambient, 1.0);
}

subroutine (RenderPassType)

void recordDepth()
{
	// Do nothing, depth will be written automatically
}
void main() {
	// This will call either shadeWithShadow or recordDepth
	RenderPass();
}