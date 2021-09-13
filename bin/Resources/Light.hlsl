Texture2D PosTexture  : register (t0);
Texture2D NormTexture : register (t1);
Texture2D DiffTexture : register (t2);
Texture2D AOTexture   : register (t3);
//Texture2D EmisTexture : register (t4);

SamplerState SamplState  : register (s0);

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

cbuffer LightBuffer : register(b2)
{
  float3 LightPos0;
  float LightIntensity0;
  //float EmissiveIntensitivy0;
};

struct VS_INPUT 
{
  float4 Position : POSITION0;
  float2 TexCoord : TEXCOORD0;
};

struct PS_INPUT 
{
   float4 Position : POSITION0;
   float2 TexCoord : TEXCOORD0;
};

PS_INPUT vs_main( VS_INPUT Input )
{
  PS_INPUT Output;
  
  Output.Position = Input.Position;
  Output.TexCoord = Input.TexCoord;
  
  return Output;
}


float4 ps_main(PS_INPUT Input) : SV_TARGET
{
   float gamma = 2.2f;
   float4 posWorld = PosTexture.Sample(SamplState, Input.TexCoord);
   float4 normal = NormTexture.Sample(SamplState, Input.TexCoord);
   float4 diffuse = pow(DiffTexture.Sample(SamplState, Input.TexCoord), gamma);
   //float4 emissive = pow(EmisTexture.Sample(SamplState, Input.TexCoord), gamma);
   float ao = AOTexture.Sample(SamplState, Input.TexCoord).r;

   float3 LightDir = normalize(LightPos0 - posWorld.xyz);

   float DiffuseLightIntensity = max(0.0f, dot(LightDir, normal.xyz)) * LightIntensity0;

   //return float4(pow(diffuse.xyz * DiffuseLightIntensity + (emissive.xyz * EmissiveIntensitivy0), 1.0f/gamma), 1) * ao;
   //return float4(pow(diffuse.xyz * DiffuseLightIntensity, 1.0f/gamma), 1) * ao;
   return float4(diffuse.xyz, 1);

}