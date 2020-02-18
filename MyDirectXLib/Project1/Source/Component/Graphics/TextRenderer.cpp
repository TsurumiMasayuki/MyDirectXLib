#include "TextRenderer.h"
#include <d2d1.h>
#include <dwrite.h>
#include "Def\Screen.h"
#include "Device\GameDevice.h"
#include "Device\Renderer.h"
#include "Device\Resource\FontManager.h"
#include "Utility\Color.h"

TextRenderer::TextRenderer(GameObject * pUser, int drawOrder)
	: AbstractComponent(pUser),
	m_pTextFormat(nullptr),
	m_pTextLayout(nullptr),
	m_pBrush(nullptr),
	m_DrawOrder(drawOrder)
{
	GameDevice::getRenderer()->addText(this);
}

TextRenderer::~TextRenderer()
{
	GameDevice::getRenderer()->removeText(this);
	if (m_pTextFormat != nullptr)
		m_pTextFormat->Release();

	if (m_pTextLayout != nullptr)
		m_pTextLayout->Release();

	if (m_pBrush != nullptr)
		m_pBrush->Release();
}

void TextRenderer::onStart()
{
}

void TextRenderer::onUpdate()
{
}

void TextRenderer::draw(ID2D1RenderTarget * pRenderTarget)
{
	if (!m_Enabled) return;
	if (m_pTextFormat == nullptr) return;
	if (m_pTextLayout == nullptr) return;

	D2D1_POINT_2F d2dPoint = { getPosition().x + Screen::getWindowWidth() / 2, -getPosition().y + Screen::getWindowHeight() / 2 };
	pRenderTarget->DrawTextLayout(d2dPoint, m_pTextLayout, m_pBrush);
}

void TextRenderer::setFont(std::wstring fontName, FONT_WEIGHT fontWeight, FONT_STYLE fontStyle)
{
	//前までのTextFormatを解放
	if (m_pTextFormat != nullptr)
		m_pTextFormat->Release();

	m_FontName = fontName;
	//TextFormat作成
	m_pTextFormat = GameDevice::getFontManager()->createFont(fontName, fontWeight, fontStyle);
}

std::wstring TextRenderer::getFont() const
{
	return m_FontName;
}

void TextRenderer::setText(std::wstring text)
{
	m_Text = text;

	if (m_pTextFormat == nullptr) return;

	//文字列が更新された場合はTextLayoutを作り直す
	if (m_pTextLayout != nullptr)
		m_pTextLayout->Release();

	m_pTextLayout = GameDevice::getFontManager()->createLayout(m_pTextFormat, m_Text, m_TextSize);

	//サイズを再設定
	DWRITE_TEXT_RANGE textRange = { 0,  m_Text.size() };
	m_pTextLayout->SetFontSize(m_TextSize, textRange);
}

std::wstring TextRenderer::getText() const
{
	return m_Text;
}

void TextRenderer::setColor(const Color & color)
{
	if (m_pBrush == nullptr)
	{
		//ブラシの作成
		ID2D1RenderTarget* d2dRT = GameDevice::getRenderer()->getD2DRenderTarget();
		d2dRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush);
	}

	//Color型をD2D1_COLOR_Fに変換する
	D2D1_COLOR_F d2dColor = { color.r, color.g, color.b, color.a };

	//ブラシの色設定を変更
	m_pBrush->SetColor(d2dColor);
}

const Color & TextRenderer::getColor() const
{
	D2D1_COLOR_F d2dColor = m_pBrush->GetColor();

	//Color型に変換して返す
	return { d2dColor.r, d2dColor.g, d2dColor.b, d2dColor.a };
}

void TextRenderer::setTextSize(float size)
{
	m_TextSize = size;

	//TextLayoutが作られていないなら作成
	if (m_pTextLayout == nullptr)
	{
		m_pTextLayout = GameDevice::getFontManager()->createLayout(m_pTextFormat, m_Text, m_TextSize);
	}

	DWRITE_TEXT_RANGE textRange = { 0,  m_Text.size() };
	m_pTextLayout->SetFontSize(m_TextSize, textRange);
}

float TextRenderer::getTextSize()
{
	return m_TextSize;
}
