#pragma once
#include <vector>
#include <string>

class CSVReader
{
public:
	CSVReader();
	~CSVReader();

	//Œ»İ“Ç‚İ‚Ü‚ê‚Ä‚¢‚éCSV‚ğ”jŠü‚µ‚ÄV‚µ‚­“Ç‚İ‚Ş
	void open(std::string filePath, bool isExcelCSV = true);

	unsigned int getColumnCount(unsigned int row);
	unsigned int getRowCount();

	std::string getData(unsigned int column, unsigned int row);

private:
	std::vector<std::vector<std::string>> m_DataList;
};