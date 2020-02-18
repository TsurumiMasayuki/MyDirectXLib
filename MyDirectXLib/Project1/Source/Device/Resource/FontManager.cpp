#include "FontManager.h"
#include "Utility\StringUtility.h"
#include <dwrite.h>

FontManager::FontManager()
{
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
}

FontManager::~FontManager()
{
	m_pDWriteFactory->Release();
}

IDWriteTextFormat * FontManager::createFont(std::wstring fontName, FONT_WEIGHT fontWeight, FONT_STYLE fontStyle)
{
	IDWriteTextFormat* pTextFormat = nullptr;

	DWRITE_FONT_STYLE style;
	switch (fontStyle)
	{
	case FONT_STYLE_NORMAL:
		style = DWRITE_FONT_STYLE_NORMAL;
		break;
	case FONT_STYLE_OBLIQUE:
		style = DWRITE_FONT_STYLE_OBLIQUE;
		break;
	case FONT_STYLE_ITALIC:
		style = DWRITE_FONT_STYLE_ITALIC;
		break;
	}

	m_pDWriteFactory->CreateTextFormat(
		fontName.c_str(),				//フォント名
		NULL,
		(DWRITE_FONT_WEIGHT)fontWeight,	//文字の太さ
		style,							//斜体等の指定
		DWRITE_FONT_STRETCH_NORMAL,
		16.0f,
		L"ja_jp",
		&pTextFormat
	);

	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	return pTextFormat;
}

IDWriteTextLayout * FontManager::createLayout(IDWriteTextFormat * pFont, std::wstring text, float fontSize)
{
	IDWriteTextLayout* pLayout;
	m_pDWriteFactory->CreateTextLayout(
		text.c_str(),			//wstringからWCHARの配列を取得
		text.size(),			//文字列の長さ
		pFont,					//使用するTextLayout
		fontSize * text.size(),	//幅を一文字分のサイズ * 文字列の長さにする
		fontSize,				//高さを一文字分のサイズにする
		&pLayout				//TextLayout(結果)
	);
	return pLayout;
}
