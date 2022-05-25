RWTexture2D<float4> Frame : register(u0);

RWBuffer<int> r : register(u1);
RWBuffer<int> g : register(u2);
RWBuffer<int> b : register(u3);


Texture2D FrameSampler : register(t0);

SamplerState SamplState : register(s0);

cbuffer HistogramBuffer : register(b0) {
  float2 Resolution;
};

struct CS_INPUT {
  uint3 localThreadID  : SV_GroupThreadID;
  uint3 groupID        : SV_GroupID;
  uint3 globalThreadID : SV_DispatchThreadID;
  uint  threadIndex    : SV_GroupID;
};

// RGB to luminance
float
RGBToLuminance(float3 inRGB) {
  return dot(float3(0.2126f, 0.7152f, 0.0722f), inRGB);
}

void
mainHistogramRGB(uint2 index) {

  int pIndex = int(floor((index.x * float(Resolution.x))));

  float3 freq = FrameSampler[uint2(pIndex, 0)];

  float val = index.y * float(2000.0);

  float3 result = step(val, freq);

  //Frame[index] = float4(1, 0, 0, 1.0).xyzw;
  Frame[index] = float4(result, 1.0).xyzw;
}


[numthreads(32, 32, 1)]
void main(CS_INPUT input) {
  uint2 index = input.globalThreadID.xy;
  int ColorSize = mul(Resolution.x, Resolution.y);
  if (((index.x) >= ColorSize) && ((index.y) >= ColorSize)) {
    return;
  }

  float3 texel = FrameSampler.Load(int3((index.xy), 1)).xyz;
  int3 color = mul(texel, 256);
  if(color.x < 256) {
    InterlockedAdd(r[color.x], 1);
  }
  if(color.y < 256) {
    InterlockedAdd(g[color.y], 1);
  }
  if(color.z < 256) {
    InterlockedAdd(b[color.z], 1);
  }


  GroupMemoryBarrierWithGroupSync();
  mainHistogramRGB(index);
}
