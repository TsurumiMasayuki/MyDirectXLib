#pragma once
#include <string>
#include "Component\AbstractComponent.h"
#include "Component\Graphics\IRenderer2D.h"

class VertexShader;
class PixelShader;

class CustomRenderer2D
	: public AbstractComponent, public IRenderer2D
{
public:
	CustomRenderer2D(GameObject* pUser, int drawOrder = 100);
	~CustomRenderer2D();

	virtual void onStart() override;
	virtual void onUpdate() override;

	virtual int getDrawOrder() const override;
	virtual GraphicsLayer getGraphicsLayer() const override;
	virtual void draw() override;

	//���_�V�F�[�_�[�ݒ�
	void setVertexShader(const std::string& shaderName);
	//�s�N�Z���V�F�[�_�[�ݒ�
	void setPixelShader(const std::string& shaderName);

	//���C���[�ݒ�
	void setGraphicsLayer(GraphicsLayer graphicsLayer) { m_GraphicsLayer = graphicsLayer; }

private:
	int m_DrawOrder;
	GraphicsLayer m_GraphicsLayer;

	VertexShader* m_pVertexShader;
	PixelShader* m_pPixelShader;


};
