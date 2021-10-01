Texture2D AlbedTexture : register (t0);
Texture2D NormaTexture : register (t1);
Texture2D MetalTexture : register (t2);
Texture2D RoughTexture : register (t3);

SamplerState SamplState : register (s0);

cbuffer CameraBuffer : register(b0)
{
  matrix View;
  matrix Projection;
};

cbuffer cbChangesEveryFrame : register(b1)
{
  matrix World;
  float4 vMeshColor;
};

struct VS_INPUT
{
  float3 Position  : POSITION0;
  float2 TexCoord  : TEXCOORD0;
  float3 Normal    : NORMAL0;
  float3 Tangent   : TANGENT0;
  float3 BiNormal  : BINORMAL0;
};

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

PS_INPUT VS_GBUFFER(VS_INPUT inVS) 
{
  PS_INPUT output;
  matrix WorldView = mul(World, View);
  
  //Position View
  float4 posView = mul(float4(inVS.Position.xyz, 1.0f), WorldView);
  output.PosView = posView;
  
  //Position
  output.Position = mul(posView, Projection);
  
  //Normal
  float3 normal = normalize(mul(float4(inVS.Normal.xyz, 0.0f), WorldView).xyz);
  
  //BiNormal
  float3 binormal = normalize(mul(float4(inVS.BiNormal.xyz, 0.0f), WorldView).xyz);
  
  //Tangent
  float3 tangent = normalize(mul(float4(inVS.Tangent.xyz, 0.0f), WorldView).xyz);

  //TexCoord
  output.TexCoord = inVS.TexCoord;
  output.TBN = float3x3(tangent.xyz, binormal.xyz, normal.xyz);
  
  return output;
}


PS_OUTPUT PS_GBUFFER(PS_INPUT inPS)
{
  PS_OUTPUT output = (PS_OUTPUT)0;
  
  //Positions
  output.Position = float4(inPS.PosView.xyz, 1.0f);
  
  //Normals & Roughness
  float3 normal = NormaTexture.Sample(SamplState, inPS.TexCoord).xyz;
  normal = (normal * 2.0f) - 1.0f;
  normal = normalize(mul(normal, inPS.TBN).xyz);
  output.Normal.xyz = normal;
  output.Normal.w = RoughTexture.Sample(SamplState, inPS.TexCoord).x;
  //output.Normal.w = 1;
  
  //Albedo & Metalic
  float3 albedo = AlbedTexture.Sample(SamplState, inPS.TexCoord).xyz;
  output.Albedo.xyz = albedo;
  output.Albedo.w = MetalTexture.Sample(SamplState, inPS.TexCoord).x;
  
  return output;
}