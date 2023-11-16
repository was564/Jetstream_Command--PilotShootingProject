////////////////////////////////////////////////////////////////////////////////
// Filename: skydome_vs.hlsl
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

//////////////
// TYPEDEFS //
//////////////

// This structure is used to send the information we need from the skymaps VS to the skymaps PS.
// We will only be needing the position and texture coordinates in our PS.
struct SKYMAP_VS_OUTPUT	// output structure for skymap vertex shader
{
	float4 Pos : SV_POSITION;
	float3 texCoord : TEXCOORD;
};

struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
// Here is our skymaps VS. As you can see, we are taking in normal values for each vertex still, 
// this is because we are going to be using the same input layout for all our geometry(so we don't
// have to do more code). However, we will not be using the normals. And in fact, we did not define
// texture coordinates for our vertices either. This is because the texture coordinates will be 
// defined by our vertices position. We can use our vertices position as a vector, describing the 
// texel in our texturecube	to color the pixel with. You can see how we do that with the line 
// output.texCoord = inPos;. Also, notice when we are defining the output position, we take the 
// values.xyww instead of.xyzw. This is because	w is equal to 1.0f. We want to make sure our 
// skymap is always the furthest object in our scene, so we	want to set our z value to 1.0f too, 
// which is what w is. Remember, 1.0f is the furthest value from the screen.
SKYMAP_VS_OUTPUT SKYMAP_VS(VertexInputType input)
{
	SKYMAP_VS_OUTPUT output = (SKYMAP_VS_OUTPUT)0;

	// Set Pos to xyww instead of xyzw, so that z will always be 1 (furthest from camera)
	output.Pos = mul(input.position, transpose(worldMatrix * viewMatrix * projectionMatrix)).
	xyww;

	output.texCoord = input.position;

	return output;
}