#include "MeshVertex.h"
#include <d3d11.h>

void MeshVertex::getInputDesc(D3D11_INPUT_ELEMENT_DESC layoutArray[1])
{
	layoutArray[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
}
