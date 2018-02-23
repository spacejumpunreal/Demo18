#pragma pack_matrix(row_major)

cbuffer VSConstantBuffer : register(b0)
{
	float4x4 World;
	float4x4 WorldView;
	float4x4 WorldViewPerspective;
}

struct VSInput
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float2 Texcoord : TEXCOORD;

};

struct VSOutput
{
	float4 Position : SV_POSITION;
	float3 WorldPosition : POSITION;
	float3 WorldNormal : NORMAL;
	float2 Texcoord : TEXCOORD;
};

VSOutput VS(VSInput IN)
{
	VSOutput OUT;
	OUT.WorldPosition = IN.Position;
	OUT.WorldNormal = IN.Normal;
	OUT.Texcoord = IN.Texcoord;
	OUT.Position = mul(float4(IN.Position, 1.0), WorldViewPerspective);
	return OUT;
}

cbuffer PSConstantBuffer : register(b0)
{
	float3 Color;
}

Texture2D diffuseMap : register(t0);
SamplerState diffuseSampler;

float4 PSTmp(VSOutput IN) : SV_TARGET
{
	float4 sampled = diffuseMap.Sample(diffuseSampler, float2(IN.Texcoord.x, 1 - IN.Texcoord.y));
	return float4(sampled.xyz * Color, 1);
}

float4 PSFinal(VSOutput IN) : SV_TARGET
{
	float4 sampled = diffuseMap.Sample(diffuseSampler, float2(IN.Texcoord.x, IN.Texcoord.y));
	return float4(sampled.xyz, 1);
}