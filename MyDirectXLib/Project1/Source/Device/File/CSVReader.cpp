#include "CSVReader.h"

#include <fstream>
#include "Utility\StringUtility.h"

CSVReader::CSVReader()
{
}

CSVReader::~CSVReader()
{
}

void CSVReader::open(std::string filePath, bool isExcelCSV)
{
	//データをクリア
	m_DataList.clear();

	//読み込み用ストリームを作成
	std::ifstream reader(filePath);

	std::string line;
	while (!reader.eof())
	{
		std::getline(reader, line);
		std::vector<std::string> lineData;

		StringUtility::split(line, ',', lineData);

		m_DataList.push_back(lineData);
	}

	//読み込み終わったのでストリームを閉じる
	reader.close();

	//Excelで保存した場合無駄な一行が末尾に追加されるのでpop
	if (isExcelCSV)
		m_DataList.pop_back();
}

unsigned int CSVReader::getColumnCount(unsigned int row)
{
	return m_DataList.at(row).size();
}

unsigned int CSVReader::getRowCount()
{
	return m_DataList.size();
}

std::string CSVReader::getData(unsigned int column, unsigned int row)
{
	return m_DataList.at(row).at(column);
}
