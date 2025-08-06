#pragma once
#include <string>
#include <vector>

class FileIO
{
public:
	static std::vector<std::string> LoadFileLines(const std::string& filepath);

	static void PrintLines(const std::vector<std::string>& lines);
};