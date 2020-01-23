#include "StringUtility.h"
#include <sstream>

void StringUtility::split(const std::string & source, const char split, std::vector<std::string>& result)
{
	std::string buffer;
	std::stringstream stream(source);

	while (std::getline(stream, buffer, split))
	{
		result.emplace_back(buffer);
	}
}
