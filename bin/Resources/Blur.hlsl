Texture2D InputImage : register (t0);

SamplerState SamplState  : register (s0);

cbuffer BlurBuffer : register(b0)
{
    float2 fViewportDimensions;
    float gamma = 1.0f;
};

struct VS_INPUT
{
  float2 TexCoord : TEXCOORD0;
};


struct PS_INPUT
{
  float2 TexCoord : TEXCOORD0;
};

PS_INPUT vs_blur(VS_INPUT inVS) {
  PS_INPUT output;
  output.TexCoord = inVS.TexCoord.xy;
  return output;
}

float4 ps_gaussian_blurH(PS_INPUT input) : SV_TARGET
{
  float offset[3] = {0.0, 1.3846153846, 3.2307692308};
  float weight[3] = {0.2270270270, 0.3162162162, 0.0702702703};
	
  float4 FragmentColor = pow(InputImage.Sample(SamplState, input.TexCoord), gamma) * weight[0];
	
  for(int i = 1; i < 3; i++)
  {
    FragmentColor += pow(InputImage.Sample(SamplState, input.TexCoord + (float2(offset[i], 0.0f) / fViewportDimensions)), gamma) * weight[i];
    FragmentColor += pow(InputImage.Sample(SamplState, input.TexCoord - (float2(offset[i], 0.0f) / fViewportDimensions)), gamma) * weight[i];
  }
  return pow(FragmentColor, 1.0f/gamma);
}

float4 ps_gaussian_blurV(PS_INPUT input) : SV_TARGET
{
  float offset[3] = {0.0, 1.3846153846, 3.2307692308}; 
  float weight[3] = {0.2270270270, 0.3162162162, 0.0702702703};
	
  float4 FragmentColor = pow(InputImage.Sample(SamplState, input.TexCoord), gamma) * weight[0];
	
  for(int i = 1; i < 3; i++)
  {
    FragmentColor += pow(InputImage.Sample(SamplState, input.TexCoord + (float2(0.0f, offset[i]) / fViewportDimensions)), gamma) * weight[i];
    FragmentColor += pow(InputImage.Sample(SamplState, input.TexCoord - (float2(0.0f, offset[i]) / fViewportDimensions)), gamma) * weight[i];
  }
  return pow(FragmentColor, 1.0f/gamma);
}