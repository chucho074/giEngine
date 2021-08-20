Texture2D PositionSampler : register(t0);
Texture2D NormalSampler : register(t1);

SamplerState SamplState : register(s0);

cbuffer SSAO : register(b0)
{
  float SampleRadius;
  float Intensity;
  float Scale;
  float Bias;
};

struct VS_INPUT
{
  float3 msPos : POSITION0;
  float2 TexCoord : TEXCOORD0;
};

struct VS_OUTPUT {
  float4 psPos    : SV_POSITION;
  float2 TexCoord : TEXCOORD0;
};

struct PS_INPUT {
   float4 psPos    : SV_POSITION;
   float2 TexCoord : TEXCOORD0;
};

struct PS_OUTPUT {
  float4 Color: SV_TARGET0;
};

float4 GetPosition(in float2 uv) {
  return PositionSampler.Sample(SamplState, uv);
}

float3 GetNormal(in float2 uv) {
  return normalize(NormalSampler.Sample(SamplState, uv).xyz);
}

float2 GetRandom(in float2 uv) {
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

VS_OUTPUT VS_SSAO(VS_INPUT inVS) {
  VS_OUTPUT output;
  output.psPos = float4(inVS.msPos.xyz, 1.0f);
  output.TexCoord = inVS.TexCoord.xy;
  return output;
}

PS_OUTPUT PS_SSAO(PS_INPUT input) {
  PS_OUTPUT Output;
  Output.Color = float4(1, 1, 1, 1);
  const float2 vec[4] = {
    float2(1, 0), float2(-1, 0), float2(0, 1), float2(0, -1),
  };
  
  float4 p = GetPosition(input.TexCoord);
  
  //clip(p.w < 1.0f ? -1 : 1);
  
  float3 n = GetNormal(input.TexCoord);
  float2 rand = GetRandom(input.TexCoord);
  
  float ao = 0.0f;
  float rad = SampleRadius / p.z;
  
  int iterations = 4;
  for (int j = 0; j < iterations; ++j) {
    float2 coord1 = reflect(vec[j], rand) * rad;
    float2 coord2 = float2(coord1.x * 0.707 - coord1.y * 0.707,
                           coord1.x * 0.707 + coord1.y * 0.707);
    
    ao += DoAmbientOcclusion(input.TexCoord, coord1 * 0.25, p.xyz, n);
    ao += DoAmbientOcclusion(input.TexCoord, coord2 * 0.5,  p.xyz, n);
    ao += DoAmbientOcclusion(input.TexCoord, coord2 * 0.75, p.xyz, n);
    ao += DoAmbientOcclusion(input.TexCoord, coord2,        p.xyz, n);
  }
  
  ao /= (iterations * 4);
  Output.Color.rgb = 1 - ao.xxx;
  return Output;
}