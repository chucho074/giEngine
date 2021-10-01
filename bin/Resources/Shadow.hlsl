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

struct PS_INPUT {
  float4 Position       : SV_POSITION;
  float  DepthPosition  : TEXCOORD0;
};

PS_INPUT vs_Shadow( VS_INPUT Input ) {
  PS_INPUT Output;
  
  matrix WorldView = mul(World, View);
  Output.DepthPosition = mul(float4(Input.Position.xyz, 1.0f), WorldView).z;
  
  matrix clip = mul(WorldView, Projection); 
  Output.Position = mul(float4(Input.Position.xyz, 1.0f), clip);
  
  return Output;
}

float4 ps_Shadow( PS_INPUT Input ) : SV_TARGET {
  return float4(Input.DepthPosition, Input.DepthPosition, Input.DepthPosition, 1.0f);
}