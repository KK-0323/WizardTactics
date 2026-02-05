#pragma once
#include <string>
#include <vector>

class CsvReader
{
public:
	CsvReader(std::string filename);
	~CsvReader();
	int GetLines(); // 行数
	int GetColumns(int line); // 列の数
	std::string GetString(int line, int col); // データを返す
	int GetInt(int line, int col); // データをintで返す
	float GetFloat(int line, int col); // データをfloatで返す
private:
	std::vector<std::vector<std::string>> record;
};