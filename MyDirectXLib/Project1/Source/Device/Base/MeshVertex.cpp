#include "MeshVertex.h"
#include <d3d11.h>

void MeshVertex::getInputDesc(D3D11_INPUT_ELEMENT_DESC layoutArray[2])
{
	layoutArray[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	layoutArray[1] = { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
}
