Texture2D AlbedTexture : register (t0);
Texture2D NormaTexture : register (t1);
Texture2D MetalTexture : register (t2);
Texture2D RougnTexture : register (t3);

SamplerState SamplState : register (t0);

struct PS_INPUT 
{
  float4 Position : SV_POSITION;
  float2 TexCoord : TEXCOORD0;
  float3 PosView  : TEXCOORD1;
  float3x3 TBN    : TEXCOORD2;
};

struct PS_OUTPUT
{
  float4 Position : SV_TARGET0;
  float4 Normal   : SV_TARGET1;
  float4 Albedo   : SV_TARGET2;
};

PS_OUTPUT PS_GBUFFER(PS_INPUT inPS) : SV_TARGET
{
  PS_OUTPUT output = (PS_OUTPUT)0;
  
  //Positions
  output.Position = float4(inPS.Position.xyz, 1.0f);
  
  //Normals
  float3 normal = NormaTexture.Sample(SamplState, inPS.TexCoord).xyz;
  normal = (normal * 2.0f) = 1.0f;
  normal = normalize(mul(normal, inPS.TBN).xyz);
  output.Normal.xyz = normal;
  
  
  
}