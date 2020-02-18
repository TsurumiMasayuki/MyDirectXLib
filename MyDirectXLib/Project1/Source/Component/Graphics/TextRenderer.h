#pragma once
#include <string>
#include "Component\AbstractComponent.h"
#include "Device\Resource\FontOption.h"

struct ID2D1RenderTarget;
struct ID2D1SolidColorBrush;
struct IDWriteTextFormat;
struct IDWriteTextLayout;

struct Color;

class TextRenderer
	: public AbstractComponent
{
public:
	TextRenderer(GameObject* pUser, int drawOrder = 100);
	~TextRenderer();

	virtual void onStart() override;
	virtual void onUpdate() override;

	int getDrawOrder() { return m_DrawOrder; }
	void draw(ID2D1RenderTarget* pRenderTarget);

	void setFont(std::wstring fontName, FONT_WEIGHT fontWeight, FONT_STYLE fontStyle);	//フォント名の設定
	std::wstring getFont() const;		//フォント名の取得

	void setText(std::wstring text);	//文字列の設定
	std::wstring getText() const;		//文字列の取得

	void setColor(const Color& color);	//文字色の設定
	const Color& getColor() const;		//文字色の取得

	void setTextSize(float size);		//文字サイズの設定
	float getTextSize();				//文字サイズの取得

private:
	IDWriteTextFormat* m_pTextFormat;
	IDWriteTextLayout* m_pTextLayout;
	ID2D1SolidColorBrush* m_pBrush;

	std::wstring m_FontName;
	std::wstring m_Text;
	float m_TextSize;
	int m_DrawOrder;
};