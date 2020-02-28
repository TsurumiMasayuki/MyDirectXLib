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

//文字列描画用コンポーネント
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

	//フォント名の設定
	void setFont(std::wstring fontName, FONT_WEIGHT fontWeight, FONT_STYLE fontStyle);
	//フォント名の取得
	std::wstring getFont() const;

	//文字列の設定
	void setText(std::wstring text);
	//文字列の取得
	std::wstring getText() const;

	//文字色の設定
	void setColor(const Color& color);
	//文字色の取得
	const Color& getColor() const;

	//文字サイズの設定
	void setTextSize(float size);
	//文字サイズの取得
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