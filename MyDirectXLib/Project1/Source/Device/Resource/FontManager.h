#pragma once
#include <string>
#include "FontOption.h"

struct IDWriteFactory;
struct IDWriteTextFormat;
struct IDWriteTextLayout;

class FontManager
{
public:
	FontManager();
	~FontManager();

	IDWriteTextFormat* createFont(std::wstring fontName, FONT_WEIGHT fontWeight, FONT_STYLE fontStyle);
	IDWriteTextLayout* createLayout(IDWriteTextFormat* pFont, std::wstring text, float fontSize);

private:
	IDWriteFactory* m_pDWriteFactory;
};