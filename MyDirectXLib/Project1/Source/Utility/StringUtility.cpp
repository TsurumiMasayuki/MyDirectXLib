#include "StringUtility.h"
#include <sstream>
#include <codecvt>

void StringUtility::split(const std::string & source, const char split, std::vector<std::string>& result)
{
	std::string buffer;
	std::stringstream stream(source);

	while (std::getline(stream, buffer, split))
	{
		result.emplace_back(buffer);
	}
}

std::wstring StringUtility::toWString(const std::string & source)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	return converter.from_bytes(source);
}

std::string StringUtility::toString(const std::wstring & source)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	return converter.to_bytes(source);
}
