#pragma once
#include "Component\AbstractComponent.h"

#include <string>

struct Mesh;
struct Color;
class VertexShader;
class PixelShader;

//メッシュ描画用コンポーネント
class MeshRenderer :
	public AbstractComponent
{
public:
	MeshRenderer(GameObject* pUser, int drawOrder = 100);
	~MeshRenderer();

	virtual void onStart() override;
	virtual void onUpdate() override;

	void setMesh(std::string meshName);

	int getDrawOrder();
	void draw();

	void setColor(const Color& color);
	const Color& getColor() const;

private:
	Mesh* m_pMesh;
	Color* m_pColor;
	int m_DrawOrder;

	VertexShader* m_pVertexShader;
	PixelShader* m_pPixelShader;
};