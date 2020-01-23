#include "ConstantBuffer.h"
#include <d3d11.h>

ConstantBuffer::ConstantBuffer()
{
	m_pBuffer = nullptr;
}

ConstantBuffer::~ConstantBuffer()
{
	m_pBuffer->Release();
}

void ConstantBuffer::init(ID3D11Device * pDevice, unsigned int size, void * pInitData)
{
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = size;
	cb.CPUAccessFlags = 0;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = pInitData;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	pDevice->CreateBuffer(&cb, &initData, &m_pBuffer);
}

ID3D11Buffer * ConstantBuffer::getBuffer() const
{
	return m_pBuffer;
}
