struct ModelViewProjection
{
    matrix MVP;
};

struct VertexPosColorIn
{
    float3 Position : POSITION;
    float3 Color    : COLOR;
};

ConstantBuffer<ModelViewProjection> ModelViewProjectionCB : register(b0);


struct VertexShaderOutput
{
    float4 Color    : COLOR;
    float4 Position : SV_Position;
};

VertexShaderOutput main(VertexPosColorIn IN)
{
    VertexShaderOutput OUT;

    OUT.Position = mul(ModelViewProjectionCB.MVP, float4(IN.Position, 1.0f));
    OUT.Color = float4(IN.Color, 1.0f);

    return OUT;
}