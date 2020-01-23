#include "VertexBuffer.h"
#include <d3d11.h>

VertexBuffer::VertexBuffer()
{
	m_pBuffer = nullptr;
}

VertexBuffer::~VertexBuffer()
{
	m_pBuffer->Release();
}

void VertexBuffer::init(ID3D11Device * pDevice, unsigned int size, void * pInitData)
{
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = size;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = pInitData;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	pDevice->CreateBuffer(&desc, &data, &m_pBuffer);
}

ID3D11Buffer * VertexBuffer::getBuffer() const
{
	return m_pBuffer;
}
