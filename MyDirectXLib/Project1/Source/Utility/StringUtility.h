#pragma once
#include <vector>
#include <string>

namespace StringUtility
{
	void split(const std::string& source, const char split, std::vector<std::string>& result);
	std::wstring toWString(const std::string& source);
	std::string toString(const std::wstring& source);
}