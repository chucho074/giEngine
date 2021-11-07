RWTexture2D<float4> Blur : register(u0);

Texture2D<float4> InputImage : register (t0);

SamplerState SamplState  : register (s0);

cbuffer 
BlurBuffer : register(b0) {
  float2 fViewportDimensions;
  float gamma = 1.0f;
  float kk = 1.0f;
  float2 TextureSize;
};

struct CS_INPUT {
  uint3 localThreadID  : SV_GroupThreadID;
  uint3 groupID        : SV_GroupID;
  uint3 globalThreadID : SV_DispatchThreadID;
  uint  threadIndex    : SV_GroupID;
};

[numthreads(32, 32, 1)]
void
cs_gaussian_blurH(CS_INPUT input) {
  uint2 index = input.globalThreadID.xy;

  float4 tmpBlur = Blur[index];

  float2 TexCoord = index / TextureSize; //psPos/size

  float offset[3] = {0.0, 1.3846153846, 3.2307692308};
  float weight[3] = {0.2270270270, 0.3162162162, 0.0702702703};
	
  tmpBlur = pow(InputImage.SampleLevel(SamplState, TexCoord, 0), gamma) * weight[0];
	
  for(int i = 1; i < 3; i++) {
    tmpBlur += pow(InputImage.SampleLevel(SamplState, TexCoord + (float2(offset[i], 0.0f) / fViewportDimensions), 0), gamma) * weight[i];
    tmpBlur += pow(InputImage.SampleLevel(SamplState, TexCoord - (float2(offset[i], 0.0f) / fViewportDimensions), 0), gamma) * weight[i];
  }
  tmpBlur = pow(tmpBlur, 1.0f/gamma);
  Blur[index] = tmpBlur;
}

[numthreads(32, 32, 1)]
void 
cs_gaussian_blurV(CS_INPUT input) {
  uint2 index = input.globalThreadID.xy;
  
  float4 tmpBlur = Blur[index];

  float2 TexCoord = index / TextureSize; //psPos/size

  float offset[3] = {0.0, 1.3846153846, 3.2307692308}; 
  float weight[3] = {0.2270270270, 0.3162162162, 0.0702702703};
	
  tmpBlur = pow(InputImage.SampleLevel(SamplState, TexCoord, 0), gamma) * weight[0];
	
  for(int i = 1; i < 3; i++) {
    tmpBlur = tmpBlur + pow(InputImage.SampleLevel(SamplState, TexCoord + (float2(0.0f, offset[i]) / fViewportDimensions), 0), gamma) * weight[i];
    tmpBlur = tmpBlur + pow(InputImage.SampleLevel(SamplState, TexCoord - (float2(0.0f, offset[i]) / fViewportDimensions), 0), gamma) * weight[i];
  }
  tmpBlur = pow(tmpBlur, 1.0f/gamma);
}