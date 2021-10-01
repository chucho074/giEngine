Texture2D PosTexture  : register (t0);
Texture2D NormTexture : register (t1);
Texture2D DiffTexture : register (t2);
Texture2D AOTexture   : register (t3);
Texture2D ShadTexture : register (t4);

SamplerState SamplState  : register (s0);

cbuffer CameraBuffer : register(b0)
{
  matrix View;
  matrix Projection;
};

cbuffer ShadowCameraBuffer : register(b1)
{
  matrix ViewShadow;
  matrix ProjectionShadow;
};

cbuffer cbChangesEveryFrame : register(b2)
{
  matrix World;
  float4 vMeshColor;
};

cbuffer LightBuffer : register(b3)
{
  float3 LightPos0;
  float  LightIntensity0;
  float4 ViewPos;			//For View direction of the main camera
  matrix InverseView;
  //float EmissiveIntensitivy0;
};

struct VS_INPUT 
{
  float4 Position : SV_POSITION;
  float2 TexCoord : TEXCOORD0;
};

struct PS_INPUT 
{
   float4 Position : SV_POSITION;
   float2 TexCoord : TEXCOORD0;
};

float3 fresnelSchlick(float3 F0, float cosTheta)
{
  return F0 + (1.0f - F0) * pow(1.0f - cosTheta, 5.0f);
}

float ndf_GGX(float NdH, float roughness)
{
  float alpha = roughness * roughness;
  float alphaSqr = alpha * alpha;

  float denom = (NdH * NdH) * (alphaSqr - 1.0f) + 1.0f;
  return alphaSqr / (3.14159265359 * denom * denom);
}

float ga_SchlickG1(float cosTheta, float k)
{
  return cosTheta / (cosTheta * (1.0f - k) + k);
}

float ga_SchlickGGX(float cosLi, float cosLo, float roughness)
{
  float r = roughness + 1.0f;
  float k = (r * r) / 8.0f;
  return ga_SchlickG1(cosLi, k) * ga_SchlickG1(cosLo, k);
}


PS_INPUT vs_main( VS_INPUT Input )
{
  PS_INPUT Output;
  
  Output.Position = float4(Input.Position.xyz, 1.0f);
  Output.TexCoord = (Input.Position.xy + 1.0f) * 0.5f;
  Output.TexCoord.y = 1.0f - Output.TexCoord.y;
  
  return Output;
}


float4 ps_main(PS_INPUT Input) : SV_TARGET0
{
   float gamma = 2.2f;
   //Positions
   float4 posWorld = float4(PosTexture.Sample(SamplState, Input.TexCoord).xyz, 1);
   //Normals
   float4 normal = NormTexture.Sample(SamplState, Input.TexCoord);
   float roughness = normal.w;
   normal.w = 0.0f;
   float4 diffuse = DiffTexture.Sample(SamplState, Input.TexCoord);
   diffuse.xyz = pow(diffuse.xyz,  gamma);
   float metalic = diffuse.w;
   diffuse.w = 1.0f;
   //float4 emissive = pow(EmisTexture.Sample(SamplState, Input.TexCoord), gamma);
   //Ambient Occlusion
   float ao = AOTexture.Sample(SamplState, Input.TexCoord).r;
   //Specular
   float3 specular = lerp(0.04f, diffuse.xyz, metalic);
   //Light Dir
   float4 viewLightDir = mul(float4(LightPos0, 1.0f), posWorld);
   float3 viewViewDir = mul(ViewPos, posWorld);

   float3 LightDir = normalize(viewLightDir.xyz - posWorld.xyz);
   float3 viewDir = normalize(viewViewDir.xyz - posWorld.xyz);
   //Diffuse Light 
   //float DiffuseLightIntensity = max(0.0f, dot(LightDir, normal.xyz)) * LightIntensity0;
   float NdL = max(0.0f, dot(normal.xyz, LightDir));
   float NdV = max(0.001f, dot(normal.xyz, viewDir));
   
   float3 H = normalize(viewDir + LightDir);
   float E = 0.001f; 
   float NdH = max(E, dot(normal, H));
   float HdL = saturate(dot(H, LightDir));
   float HdV = saturate(dot(H, viewDir));
	
   float3 Reflect = normalize(reflect(-viewDir, normal));
   
   float D = ndf_GGX(NdH, roughness);
   float3 F = fresnelSchlick(specular, HdL);
   float G = ga_SchlickGGX(NdL, NdV, roughness);
	
   float3 specu = (D * F * G) / max(0.00001, (NdL * NdV * 4.0f));
	
   //Shadows
   float shadow = 1.0f;
   float4 shadowPosition = mul(posWorld, InverseView);
   float4 shadow_W = mul(float4(shadowPosition.xyz, 1.0f), ViewShadow);
   float4 shadowPosClip = mul(shadow_W, ProjectionShadow);
   shadowPosClip /= shadowPosClip.w;
   
   float2 shadowTexCoord = shadowPosClip.xy;
   
   shadowTexCoord.y = 1 - shadowTexCoord.y;
	
   float depth = ShadTexture.Sample(SamplState, shadowTexCoord).x;
   
   //return float4();
   //return float4(pow(diffuse.xyz * DiffuseLightIntensity + (emissive.xyz * EmissiveIntensitivy0), 1.0f/gamma), 1) * ao;
   //return float4(pow(((diffuse.xyz * NdL * LightIntensity0) + (specu)) /** ao*/, 1.0f/gamma), 1);
   //return float4(pow(((diffuse.xyz * NdL * LightIntensity0) + (specu)), 1.0f/gamma), 1);
   return float4(pow((((1-shadow) * (diffuse.xyz * NdL * LightIntensity0)) + (specu)) * ao, 1.0f/gamma), 1);
   //return float4(diffuse.xyz, 1);

}