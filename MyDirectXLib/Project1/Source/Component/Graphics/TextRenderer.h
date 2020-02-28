#pragma once
#include <string>
#include "Component\AbstractComponent.h"
#include "Component\Graphics\IRenderer2D.h"
#include "Device\Resource\FontOption.h"

struct ID2D1RenderTarget;
struct ID2D1SolidColorBrush;
struct IDWriteTextFormat;
struct IDWriteTextLayout;

struct Color;

//������`��p�R���|�[�l���g
class TextRenderer
	: public AbstractComponent, public IRenderer2D
{
public:
	TextRenderer(GameObject* pUser, int drawOrder = 100);
	~TextRenderer();

	virtual void onStart() override;
	virtual void onUpdate() override;

	virtual int getDrawOrder() const override { return m_DrawOrder; }
	virtual void draw() override;

	//�t�H���g���̐ݒ�
	void setFont(std::wstring fontName, FONT_WEIGHT fontWeight, FONT_STYLE fontStyle);
	//�t�H���g���̎擾
	std::wstring getFont() const;

	//������̐ݒ�
	void setText(std::wstring text);
	//������̎擾
	std::wstring getText() const;

	//�����F�̐ݒ�
	void setColor(const Color& color);
	//�����F�̎擾
	const Color& getColor() const;

	//�����T�C�Y�̐ݒ�
	void setTextSize(float size);
	//�����T�C�Y�̎擾
	float getTextSize();

private:
	IDWriteTextFormat* m_pTextFormat;
	IDWriteTextLayout* m_pTextLayout;
	ID2D1SolidColorBrush* m_pBrush;

	std::wstring m_FontName;
	std::wstring m_Text;
	float m_TextSize;
	int m_DrawOrder;
};