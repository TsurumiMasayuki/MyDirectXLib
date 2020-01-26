#include "SpriteVertex.h"
#include <d3d11.h>;

void SpriteVertex::getInputDesc(D3D11_INPUT_ELEMENT_DESC layoutArray[2])
{
	layoutArray[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	layoutArray[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
}