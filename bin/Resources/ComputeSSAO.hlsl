RWTexture2D<float4> SSAO : register(u0);

Texture2D PositionSampler : register(t0);
Texture2D NormalSampler : register(t1);

SamplerState SamplState : register(s0);

cbuffer SSAOBuffer : register(b0) {
  float SampleRadius;
  float Intensity;
  float Scale;
  float Bias;
  float2 TextureSize;
};

struct CS_INPUT {
  uint3 localThreadID  : SV_GroupThreadID;
  uint3 groupID        : SV_GroupID;
  uint3 globalThreadID : SV_DispatchThreadID;
  uint  threadIndex    : SV_GroupID;
};

float4 GetPosition(in float2 uv) {
  return PositionSampler.Sample(SamplState, uv);
}

float3 GetNormal(in float2 uv) {
  return normalize(NormalSampler.Sample(SamplState, uv).xyz);
}

float3 GetRandom(in float2 uv) {
  float noiseX = (frac(sin(dot(uv, float2(15.8989f, 76.132f) * 1.0f)) * 46336.23745f));
  float noiseY = (frac(sin(dot(uv, float2(11.9899f, 62.223f) * 2.0f)) * 34748.34744f));
  float noiseZ = (frac(sin(dot(uv, float2(13.3238f, 63.122f) * 3.0f)) * 59998.47362f));
   
  return normalize(float3(noiseX, noiseY, noiseZ));
}

float DoAmbientOcclusion(in float2 tcoord, in float2 uv, in float3 p, in float3 cnorm) {
  float3 diff = GetPosition(tcoord + uv) - p;
  const float3 v = normalize(diff);
  const float d = length(diff) * Scale;
  return max(0.0f, dot(cnorm, v) - Bias) * (1.0 / (1.0 + d)) * Intensity;
}

[numthreads(32, 32, 1)]
void main(CS_INPUT input) {
  
  uint2 index = input.globalThreadID.xy;
  
  SSAO[index] = float4(1, 1, 1, 1);
  
  float2 TexCoord = index / TextureSize; //psPos/size
    
  const float2 vec[4] = {
    float2(1, 0), float2(-1, 0), float2(0, 1), float2(0, -1),
  };
  
  float4 p = GetPosition(TexCoord);
  
  float3 n = GetNormal(TexCoord);
  float3 rand = GetRandom(TexCoord);
  
  float ao = 0.0f;
  float rad = SampleRadius / p.z;
  
  int iterations = 4;
  
  for (int j = 0; j < iterations; ++j) {
    float2 coord1 = reflect(vec[j], rand) * rad;
    float2 coord2 = float2(coord1.x * 0.707 - coord1.y * 0.707,
                           coord1.x * 0.707 + coord1.y * 0.707);
    
    ao += DoAmbientOcclusion(TexCoord, coord1 * 0.25, p.xyz, n);
    ao += DoAmbientOcclusion(TexCoord, coord2 * 0.5,  p.xyz, n);
    ao += DoAmbientOcclusion(TexCoord, coord2 * 0.75, p.xyz, n);
    ao += DoAmbientOcclusion(TexCoord, coord2,        p.xyz, n);
  }
  
  ao /= (iterations * 4);
  SSAO[index] = float4( 1 - ao.xxx, 1);
  
}
//Y * pitch + X
//pitch = Long de fila * memoria